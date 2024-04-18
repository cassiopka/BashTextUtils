#ifndef S21_GREP_OUTPUT
#define S21_GREP_OUTPUT

#include <stdio.h>
#include <string.h>

#include "s21_grep_types.h"

void output_line(const s_fdata *fdata, const s_conf *conf);
void output_file(const s_fdata *fdata, const s_conf *conf);

#endif