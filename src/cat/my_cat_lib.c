#include "my_cat_lib.h"

int process_option(const char *op, s_ops *ops) {
    int res;

    if (op[0] == '-') {
        if (op[1] == '-') {
            res = process_long_option(op, ops);
        } else {
            res = process_short_option(op, ops);
        }
    } else {
        res = 1;
    }

    return res;
}

int process_long_option(const char *op, s_ops *ops) {
    int res = 0;

    if (!strcmp(op, "--number")) {
        ops->n = 1;
    } else if (!strcmp(op, "--number-nonblank")) {
        ops->b = 1;
    } else if (!strcmp(op, "--squeeze-blank")) {
        ops->s = 1;
    } else {
        fprintf(stderr, "cat: illegal option -- %s\n", op + 2);
        res = 1;
    }

    return res;
}

int process_short_option(const char *op, s_ops *ops) {
    int res = 0;

    for (int i = 1; op[i]; i++) {
        switch (op[i]) {
            case 'b':
                ops->b = 1;
                break;
            case 'e':
                ops->e = 1;
                ops->v = 1;
                break;
            case 'E':
                ops->e = 1;
                break;
            case 'n':
                ops->n = 1;
                break;
            case 's':
                ops->s = 1;
                break;
            case 't':
                ops->t = 1;
                ops->v = 1;
                break;
            case 'T':
                ops->t = 1;
                break;
            case 'v':
                ops->v = 1;
                break;
            default:
                fprintf(stderr, "cat: illegal option -- %c\n", op[i]);
                res = 1;
        }
    }

    return res;
}

int process_file(const char *fname, const s_ops *ops) {
    int res = 0;
    FILE *f = fopen(fname, "r");

    if (f) {
        read_and_print(f, ops);
        fclose(f);
    } else {
        res = 1;
        fprintf(stderr, "cat: %s: No such file or directory\n", fname);
    }

    return res;
}

void read_and_print(FILE *f, const s_ops *ops) {
    char c;
    int new_line = 1;
    int count = 0;
    int blank = 0;
    int prev_blank;

    while ((c = fgetc(f)) != EOF) {
        if (new_line) {
            prev_blank = blank;
            blank = (c == NEWLINE ? 1 : 0);
            if (ops->s && blank && prev_blank) {
                continue;
            }
            if ((ops->b && !blank) || (ops->n && !ops->b)) {
                printf("% 6d\t", ++count);
            }
            new_line = 0;
        }
        if (c == NEWLINE) {
            ops->e ? printf("$\n") : putchar(c);
            new_line = 1;
        } else if (c == TAB) {
            ops->t ? printf("^I") : putchar(c);
        } else {
            ops->v ? print_unprintable(c) : putchar(c);
        }
    }
}

void print_unprintable(int c) {
    if ((c >= 0 && c <= 8) || (c >= 11 && c <= 31) || c == 127) {
        print_control_char(c);
    } else if (c >= 32 && c <= 126) {
        putchar(c);
    } else {
        printf("M-");
        print_control_char(c & 127);
    }
}

void print_control_char(int c) {
    putchar('^');
    switch (c) {
        case 0:
            putchar('@');
            break;
        case 27:
            putchar('[');
            break;
        case 28:
            putchar('\\');
            break;
        case 29:
            putchar(']');
            break;
        case 30:
            putchar('^');
            break;
        case 31:
            putchar('_');
            break;
        case 127:
            putchar('?');
            break;
        default:
            putchar(c + 64);
    }
}