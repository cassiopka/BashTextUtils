#ifndef S21_GREP_TYPES
#define S21_GREP_TYPES
#define BUFF_SIZE 128

#include <regex.h>

typedef struct options {
    unsigned c : 1;
    unsigned f : 1;
    unsigned h : 1;
    unsigned i : 1;
    unsigned l : 1;
    unsigned n : 1;
    unsigned o : 1;
    unsigned s : 1;
    unsigned v : 1;
} s_ops;

typedef struct string_element {
    char *str;
    struct string_element *next;
} s_str_el;

typedef struct compiled_element {
    regex_t pat;
    struct compiled_element *next;
} s_comp_el;

typedef struct configurations {
    s_ops ops;
    s_str_el *pats_lit;
    s_comp_el *pats_comp;
    s_str_el *strs;
    int mode;
    int files_count;
} s_conf;

typedef struct file_data {
    const char *fname;
    int line_num;
    char *line;
    s_str_el *substrs;
    int matched_count;
} s_fdata;

enum flags { flag_any, flag_e_pat, flag_f_pat };

enum codes { arg_op, arg_e_pat, arg_f_pat, arg_str };

enum modes { selected, all, none };

#endif