#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *copy_str(char *s) {
    char *new_str = malloc(strlen(s) * sizeof(char));
    strcpy(new_str, s);
    return new_str;
}

int main() {
    char * copy_of_str = copy_str("hello world!");
    printf("%s\n", copy_of_str);

    return 0;
}
