#include <stdio.h>
#include <string.h>

void getString(char *str, int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}