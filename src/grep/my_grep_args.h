#ifndef S21_GREP_ARGS
#define S21_GREP_ARGS

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep_auxiliary.h"
#include "s21_grep_types.h"

int classify_arg(const char *arg, int flag);
int check_flag(int flag);
int set_options(const char *op, s_conf *conf, int *flag);
int process_e(const char *str, s_conf *conf, int *flag);
int process_f(const char *str, s_conf *conf, int *flag);
int append_to_string_list(const char *new_str, s_str_el **strs);
int insert_string(const char *new_str, s_str_el **strs);
int read_file_with_patterns(const char *fname, s_str_el **strs);
int import_patterns(FILE *f, s_str_el **strs);
void prepare_patterns(s_conf *conf);
int compile_patterns(s_conf *conf);

#endif