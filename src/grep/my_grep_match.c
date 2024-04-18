#include "s21_grep_match.h"

int read_files(s_conf *conf) {
    int res = 1;
    int matching = 1;
    s_str_el *file = conf->strs;

    while (file && matching != -1) {
        FILE *f = fopen(file->str, "r");
        if (f) {
            matching = process_file(f, conf, file->str);
            if (matching == -1) {
                res = -1;
            } else if (matching == 0 && res != -1) {
                res = 0;
            }
            fclose(f);
        } else {
            res = -1;
            if (!conf->ops.s) {
                fprintf(stderr, "grep: %s: No such file or directory\n", file->str);
            }
        }
        file = file->next;
    }

    return res;
}

int process_file(FILE *f, s_conf *conf, const char *fname) {
    int res = 1;
    int stop = 0;
    char buff[BUFF_SIZE];
    size_t max_len = BUFF_SIZE;
    s_fdata fdata;
    fdata.fname = fname;
    fdata.matched_count = 0;
    fdata.line_num = 0;
    fdata.line = calloc(max_len, sizeof(*fdata.line));

    if (!fdata.line) {
        res = -1;
    }

    while (fgets(buff, BUFF_SIZE, f) && !stop && res != -1) {
        if (max_len - strlen(fdata.line) < BUFF_SIZE) {
            max_len *= 2;
            char *tmp = realloc(fdata.line, max_len * sizeof(*tmp));
            if (tmp) {
                fdata.line = tmp;
            } else {
                res = -1;
            }
        }
        if (res != -1) {
            strcat(fdata.line, buff);
            if (strchr(buff, '\n')) {
                res = process_line(&fdata, conf, &stop);
                fdata.line[0] = '\0';
            }
        }
    }

    if (strlen(fdata.line)) {
        res = process_line(&fdata, conf, &stop);
    }

    free(fdata.line);

    if (res != -1) {
        if (conf->ops.c || conf->ops.l) {
            output_file(&fdata, conf);
        }
        if (fdata.matched_count) {
            res = 0;
        }
    }

    return res;
}

int process_line(s_fdata *fdata, s_conf *conf, int *stop) {
    int res = 1;
    fdata->line_num++;
    fdata->substrs = NULL;

    if (conf->mode == all) {
        res = 0;
    } else if (conf->mode == none) {
        res = 1;
    } else {
        res = match_line(fdata, conf);
    }

    if (!res) {
        fdata->matched_count++;
        if (conf->ops.l) {
            *stop = 1;
        } else if (!conf->ops.c && !conf->ops.l) {
            output_line(fdata, conf);
        }
    }

    free_strings_list(fdata->substrs);

    return res;
}

int match_line(s_fdata *fdata, s_conf *conf) {
    s_comp_el *pat_comp = conf->pats_comp;
    int active_o = conf->ops.o && !(conf->ops.c || conf->ops.l || conf->ops.v);
    int res = REG_NOMATCH;

    while (pat_comp && res == REG_NOMATCH) {
        if (!active_o) {
            res = regexec(&(pat_comp->pat), fdata->line, 0, NULL, 0);
        } else {
            res = get_all_substrs(&(pat_comp->pat), fdata);
        }
        pat_comp = pat_comp->next;
    }

    if (res != -1) {
        if (active_o && fdata->substrs) {
            res = 0;
        } else if (res == 0 && !conf->ops.v) {
            res = 0;
        } else if (res == REG_NOMATCH && conf->ops.v) {
            res = 0;
        } else {
            res = REG_NOMATCH;
        }
    }

    return res;
}

int get_all_substrs(const regex_t *preg, s_fdata *fdata) {
    size_t nmatch = 1;
    regmatch_t pmatch[nmatch];

    int res = regexec(preg, fdata->line, nmatch, pmatch, 0);

    if (!res) {
        int max_len = strlen(fdata->line);
        char buff[max_len];
        const char *s = fdata->line;
        do {
            s += pmatch[0].rm_so;
            int len = pmatch[0].rm_eo - pmatch[0].rm_so;
            strncpy(buff, s, len);
            buff[len] = '\0';
            res = append_to_string_list(buff, &(fdata->substrs));
            if (res != -1) {
                s += len;
                res = regexec(preg, s, nmatch, pmatch, 0);
            }
        } while ((s - fdata->line) <= max_len && !res);
        if (res != -1) {
            res = REG_NOMATCH;
        }
    }

    return res;
}