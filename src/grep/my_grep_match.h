#ifndef S21_GREP_MATCH
#define S21_GREP_MATCH

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep_args.h"
#include "s21_grep_auxiliary.h"
#include "s21_grep_free.h"
#include "s21_grep_output.h"
#include "s21_grep_types.h"

int read_files(s_conf *conf);
int process_file(FILE *f, s_conf *conf, const char *fname);
int process_line(s_fdata *fdata, s_conf *conf, int *stop);
int match_line(s_fdata *fdata, s_conf *conf);
int get_all_substrs(const regex_t *preg, s_fdata *fdata);

#endif