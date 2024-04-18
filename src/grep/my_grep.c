#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep_args.h"
#include "s21_grep_auxiliary.h"
#include "s21_grep_free.h"
#include "s21_grep_match.h"
#include "s21_grep_output.h"
#include "s21_grep_types.h"

int main(int argc, char **argv) {
    int res = 1;
    int stop = 0;
    int flag = flag_any;
    s_conf conf = {{0, 0, 0, 0, 0, 0, 0, 0, 0}, NULL, NULL, NULL, selected, 0};

    for (int i = 1; i < argc && !stop; i++) {
        int code = classify_arg(argv[i], flag);
        flag = flag_any;
        switch (code) {
            case arg_op:
                stop = set_options(argv[i], &conf, &flag);
                break;
            case arg_e_pat:
                stop = append_to_string_list(argv[i], &(conf.pats_lit));
                break;
            case arg_f_pat:
                stop = read_file_with_patterns(argv[i], &(conf.pats_lit));
                break;
            case arg_str:
                stop = append_to_string_list(argv[i], &(conf.strs));
        }
    }

    if (!stop) {
        stop = check_flag(flag);
    }

    if (!stop) {
        prepare_patterns(&conf);
        stop = compile_patterns(&conf);
    }

    if (!stop) {
        conf.files_count = count_elements(conf.strs);
        res = read_files(&conf);
    } else {
        res = stop;
    }

    free_strings_list(conf.pats_lit);
    free_compiled_list(conf.pats_comp);
    free_strings_list(conf.strs);

    return res;
}