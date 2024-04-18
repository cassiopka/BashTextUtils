#include "s21_grep_output.h"

void output_line(const s_fdata *fdata, const s_conf *conf) {
    s_str_el *substr = fdata->substrs;

    if (!conf->ops.h && (conf->files_count > 1)) {
        printf("%s:", fdata->fname);
    }

    if (conf->ops.n) {
        printf("%d:", fdata->line_num);
    }

    if (!conf->ops.o || conf->ops.v || conf->mode == all) {
        printf("%s", fdata->line);
        if (!strchr(fdata->line, '\n')) {
            printf("\n");
        }
    } else {
        while (substr) {
            printf("%s\n", substr->str);
            substr = substr->next;
        }
    }
}

void output_file(const s_fdata *fdata, const s_conf *conf) {
    if (conf->ops.c) {
        if (conf->files_count > 1 && !conf->ops.h) {
            printf("%s:", fdata->fname);
        }
        printf("%d\n", fdata->matched_count);
    }

    if (conf->ops.l && fdata->matched_count) {
        printf("%s\n", fdata->fname);
    }
}