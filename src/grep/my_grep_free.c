#include "s21_grep_free.h"

void free_strings_list(s_str_el *strs) {
    if (strs) {
        free_strings_list(strs->next);
        free(strs->str);
        free(strs);
    }
}

void free_compiled_list(s_comp_el *pats_comp) {
    if (pats_comp) {
        free_compiled_list(pats_comp->next);
        regfree(&(pats_comp->pat));
        free(pats_comp);
    }
}