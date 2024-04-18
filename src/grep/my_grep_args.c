#include "s21_grep_args.h"
#define REG_EMPTY 14

int classify_arg(const char *arg, int flag) {
    int code;

    if (flag == flag_e_pat) {
        code = arg_e_pat;
    } else if (flag == flag_f_pat) {
        code = arg_f_pat;
    } else if (arg[0] == '-') {
        code = arg_op;
    } else {
        code = arg_str;
    }

    return code;
}

int check_flag(int flag) {
    int res;

    if (flag == flag_e_pat) {
        fprintf(stderr, "grep: option requires an argument -- e\n");
        res = -1;
    } else if (flag == flag_f_pat) {
        fprintf(stderr, "grep: option requires an argument -- f\n");
        res = -1;
    } else {
        res = 0;
    }

    return res;
}

int set_options(const char *op, s_conf *conf, int *flag) {
    int res = -1;
    int stop = 0;

    for (int i = 1; op[i] && !stop; i++) {
        res = 0;
        switch (op[i]) {
            case 'c':
                conf->ops.c = 1;
                break;
            case 'e':
                process_e(op + i, conf, flag);
                stop = 1;
                break;
            case 'f':
                conf->ops.f = 1;
                process_f(op + i, conf, flag);
                stop = 1;
                break;
            case 'h':
                conf->ops.h = 1;
                break;
            case 'i':
                conf->ops.i = 1;
                break;
            case 'l':
                conf->ops.l = 1;
                break;
            case 'n':
                conf->ops.n = 1;
                break;
            case 'o':
                conf->ops.o = 1;
                break;
            case 's':
                conf->ops.s = 1;
                break;
            case 'v':
                conf->ops.v = 1;
                break;
            default:
                fprintf(stderr, "grep: invalid option -- %c\n", op[i]);
                res = -1;
                stop = 1;
        }
    }

    return res;
}

int process_e(const char *str, s_conf *conf, int *flag) {
    int res = 0;

    if (!str[1]) {
        *flag = flag_e_pat;
    } else {
        res = append_to_string_list(str + 1, &(conf->pats_lit));
    }

    return res;
}

int process_f(const char *str, s_conf *conf, int *flag) {
    int res = 0;

    if (!str[1]) {
        *flag = flag_f_pat;
    } else {
        res = read_file_with_patterns(str + 1, &(conf->pats_lit));
    }

    return res;
}

int append_to_string_list(const char *new_str, s_str_el **strs) {
    int res;

    while (*strs) {
        strs = &((*strs)->next);
    }

    res = insert_string(new_str, strs);

    return res;
}

int insert_string(const char *new_str, s_str_el **strs) {
    int res = -1;

    if (!*strs) {
        s_str_el *tmp = malloc(sizeof(*tmp));
        if (tmp) {
            int len = strlen(new_str);
            tmp->str = malloc((len + 1) * sizeof(*tmp->str));
            if (tmp->str) {
                strcpy(tmp->str, new_str);
                res = 0;
            }
            tmp->next = NULL;
            *strs = tmp;
        }
    }

    return res;
}

int read_file_with_patterns(const char *fname, s_str_el **strs) {
    int res = 0;
    FILE *f = fopen(fname, "r");

    if (f) {
        res = import_patterns(f, strs);
        fclose(f);
    } else {
        fprintf(stderr, "grep: %s: No such file or directory\n", fname);
        res = -1;
    }

    return res;
}

int import_patterns(FILE *f, s_str_el **strs) {
    int res = 0;
    char buff[BUFF_SIZE];
    size_t max_len = BUFF_SIZE;
    char *new_pat = calloc(max_len, sizeof(*new_pat));

    if (!new_pat) {
        res = -1;
    }

    while (fgets(buff, BUFF_SIZE, f) && !res) {
        if (max_len - strlen(new_pat) < BUFF_SIZE) {
            max_len *= 2;
            char *tmp = realloc(new_pat, max_len * sizeof(*tmp));
            if (tmp) {
                new_pat = tmp;
            } else {
                res = -1;
            }
        }
        if (res != -1) {
            strcat(new_pat, buff);
            if (strchr(buff, '\n')) {
                remove_newline(new_pat);
                res = append_to_string_list(new_pat, strs);
                new_pat[0] = '\0';
            }
        }
    }

    if (strlen(new_pat)) {
        res = append_to_string_list(new_pat, strs);
    }

    free(new_pat);

    return res;
}

void prepare_patterns(s_conf *conf) {
    if (!conf->pats_lit) {
        if (conf->ops.f || !conf->strs) {
            conf->mode = none;
        } else {
            conf->pats_lit = conf->strs;
            conf->strs = conf->strs->next;
            conf->pats_lit->next = NULL;
        }
    }
}

int compile_patterns(s_conf *conf) {
    int res = 0;
    int cflags = REG_NEWLINE;
    s_str_el *cur_pat_lit = conf->pats_lit;
    s_comp_el **cur_pat_comp = &(conf->pats_comp);
    s_comp_el *tmp;

    if (conf->ops.i) {
        cflags |= REG_ICASE;
    }

    while (cur_pat_lit && !res && conf->mode == selected) {
        tmp = malloc(sizeof(*tmp));
        if (tmp) {
            res = regcomp(&(tmp->pat), cur_pat_lit->str, cflags);
            if (res == REG_EMPTY) {
                conf->mode = (conf->ops.v ? none : all);
                res = 0;
            }
            tmp->next = NULL;
            *cur_pat_comp = tmp;
            cur_pat_comp = &((*cur_pat_comp)->next);
            cur_pat_lit = cur_pat_lit->next;
        } else {
            res = -1;
        }
    }

    if (res != 0) {
        res = -1;
    }

    return res;
}