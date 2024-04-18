#include <stdio.h>

int main(int argc, char **argv) {
    int res = 0;
    FILE *f = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: ./create_ascii_plus <FILE>");
        res = -1;
    }

    if (!res) {
        f = fopen(argv[1], "wb");
        if (f) {
            for (int i = 0; i <= 159; i++) {
                fputc(i, f);
            }
            fclose(f);
        } else {
            res = -1;
        }
    }

    return res;
}