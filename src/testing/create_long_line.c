#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int res = 0;
    int len;
    char c;
    FILE *f = NULL;

    if (argc != 4) {
        fprintf(stderr, "Usage: ./create_long_line <FILE> <CHAR> <LENGTH>");
        res = -1;
    }

    if (!res) {
        f = fopen(argv[1], "a");
        if (f) {
            c = atoi(argv[2]);
            len = atoi(argv[3]);
            for (int i = 0; i < len; i++) {
                fputc(c, f);
            }
            fputc('\n', f);
            fclose(f);
        } else {
            res = -1;
        }
    }

    return res;
}