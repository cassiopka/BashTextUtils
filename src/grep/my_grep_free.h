#ifndef S21_GREP_FREE
#define S21_GREP_FREE

#include <regex.h>
#include <stdlib.h>

#include "s21_grep_types.h"

void free_strings_list(s_str_el *strs);
void free_compiled_list(s_comp_el *pats_comp);

#endif