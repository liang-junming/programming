#include <stdio.h>
#include <string.h>

void read_str_use_scanf() {
    char input[1024];
    /*
     * 遇空格、制表符、换行符结束一次读取，函数返回
     * 输入：abc def
     *      123
     * 输出：abc 3
     *      def 3
     *      123 3
     */
    while (scanf("%s", input) != EOF) {
        printf("%s len: %d\n", input, strlen(input));
    }
}

void read_str_use_fgets() {
    char input[1024];
    /*
     * 遇换行符结束一次读取，函数返回，换行符会被读入字符串中
     * 输入：abc def
     *      123
     * 输出：abc def
     *       len: 8
     *      123
     *       len: 4
     */
    while (fgets(input, sizeof(input), stdin) != NULL) {
        printf("%s len: %d\n", input, strlen(input));
    }
}

void read_int_use_scanf() {
    int num;
    /*
     * scanf返回读取到的整数个数
     * 读取到EOF返回EOF
     * 如果读取到不匹配数字的字符直接返回已读取到的整数的个数
     * scanf遇到不匹配的字符会中断读取，不匹配的字符还在缓冲区，可以使用getchar()调过当前字符
     * 输入：12;34,56 78
     * 输出：12 34 56 78
     */
    while (1) {
        const int ret = scanf("%d", &num);
        if (ret == EOF) {
            break;
        }
        if (ret == 1) {
            printf("%d\n", num);
        } else {
            getchar();
        }
    }
}

int main(void) {
    read_int_use_scanf();
    printf("End!");
    return 0;
}