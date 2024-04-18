#include <stdio.h>
#include <string.h>

#include "my_cat_lib.h"

int main(int argc, char **argv) {
    int overall_res = 0;
    int current_res = 0;
    int stop = 0;
    int flag = options;
    s_ops ops = {0, 0, 0, 0, 0, 0};

    for (int i = 1; i < argc && !stop; i++) {
        if (flag == options && *argv[i] != '-') {
            flag = files;
        }
        switch (flag) {
            case options:
                stop = process_option(argv[i], &ops);
                break;
            case files:
                current_res = process_file(argv[i], &ops);
        }
        if (current_res == 1 && overall_res == 0) {
            overall_res = current_res;
        }
    }

    if (stop) {
        overall_res = stop;
    }

    return overall_res;
}