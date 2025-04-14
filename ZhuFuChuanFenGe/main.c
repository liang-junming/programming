#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char str[102] = {'\0'};

    scanf("%s", str);
    const char *p = str;
    while (strlen(p) > 0) {
        char substr[9];
        strncpy(substr, p, 8);
        if (strlen(substr) < 8) {
            memset(substr + strlen(substr), '0', 8 - strlen(substr));
            substr[8] = '\0';
        }
        printf("%s\n", substr);
        p += 8;
    }
}