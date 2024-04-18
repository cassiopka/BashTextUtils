#include "s21_grep_auxiliary.h"

int count_elements(s_str_el *element) {
    int count = 0;

    while (element) {
        count++;
        element = element->next;
    }

    return count;
}

void remove_newline(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
        }
    }
}