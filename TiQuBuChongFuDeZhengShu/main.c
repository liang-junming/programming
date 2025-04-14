#include <stdbool.h>
#include <stdio.h>

int main() {
    int input;
    bool flag[10] = {false};
    int result = 0;

    scanf("%d", &input);
    while (input != 0) {
        const int num = input % 10;
        input /= 10;
        if (!flag[num]) {
            result = result * 10 + num;
            flag[num] = true;
        }
    }
    printf("%d\n", result);
}
