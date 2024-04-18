#ifndef MY_CAT_LIB
#define MY_CAT_LIB
#define TAB 9
#define NEWLINE 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct options {
    unsigned b : 1;
    unsigned e : 1;
    unsigned n : 1;
    unsigned s : 1;
    unsigned t : 1;
    unsigned v : 1;
} s_ops;

enum flags { options, files };

int process_option(const char *op, s_ops *ops);

int process_long_option(const char *op, s_ops *ops);

int process_short_option(const char *op, s_ops *ops);

int process_file(const char *fname, const s_ops *ops);

void read_and_print(FILE *f, const s_ops *ops);

void print_unprintable(int c);

void print_control_char(int c);

#endif