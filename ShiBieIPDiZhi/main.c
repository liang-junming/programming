#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isErrorMask(int mask[4]) {
    if (mask[0] + mask[1] + mask[2] + mask[3] == 0) {
        return -1;
    }
    if (mask[0] + mask[1] + mask[2] + mask[3] == 255*4) {
        return -1;
    }
    for (int i = 0; i < 4; i++) {
        unsigned char tmp = mask[i];
        if (tmp == 0) {
            break;
        }
        while (!(tmp & 1)) {
            printf("%x \n", tmp);
            tmp = tmp >> 1;
        }
        while (tmp & 1) {
            tmp = tmp >> 1;
        }
        if (tmp) {
            return -2;
        }
    }
    return 0;
}

int isIpInGroup(int group[2][4], int ip[4]) {
    for (int i = 0; i < 4; i++) {
        if (ip[i] < group[0][i] || ip[i] > group[1][i]) {
            return 0;
        }
    }

    return 1;
}

int isInPrivate(int private[3][2][4], int ip[4]) {
    for (int i = 0; i < 3; i++) {
        if (isIpInGroup(private[i], ip)) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int A[2][4] = {{1, 0, 0, 0}, {126, 255, 255, 255}};
    int B[2][4] = {{128, 0, 0, 0}, {191, 255, 255, 255}};
    int C[2][4] = {{192, 0, 0, 0}, {223, 255, 255, 255}};
    int D[2][4] = {{224, 0, 0, 0}, {239, 255, 255, 255}};
    int E[2][4] = {{240, 0, 0, 0}, {255, 255, 255, 255}};

    int private[3][2][4] = {{{10, 0, 0, 0}, {10, 255, 255, 255}},
                            {{172, 16, 0, 0}, {172, 31, 255, 255}},
                            {{192, 168, 0, 0}, {192, 168, 255, 255}}};
    int a=0, b=0, c=0, d=0, e=0, error=0, pri=0;
    char input[100];
    char *ipStr, *maskStr;
    int ip[4] = {0, 0, 0, -1}, mask[4] = {0, 0, 0, -1};
    while (scanf("%s", input) != EOF) {
        ipStr = strtok(input, "~");
        maskStr = strtok(NULL, "~");
        char *p = strtok(ipStr, ".");
        for (int i = 0; i < 4; i++) {
            ip[i] = atoi(p);
            p = strtok(NULL, ".");
            if (p == NULL) {
                break;
            }
        }
        p = strtok(maskStr, ".");
        for (int i = 0; i < 4; i++) {
            mask[i] = atoi(p);
            p = strtok(NULL, ".");
            if (p == NULL) {
                break;
            }
        }

        if (ip[3] < 0 || mask[3] < 0) {
            error++;
            continue;;
        }
        if (ip[0] == 0 || ip[0] == 127) {
            continue;;
        }
        if (isErrorMask(mask)) {
            error++;
            continue;;
        }
        if (isInPrivate(private, ip)) {
            pri++;
        }
        if (isIpInGroup(A, ip)) {
            printf("%d.%d.%d.%d\n\n", ip[0], ip[1], ip[2], ip[3]);
            a++;
            continue;;
        }
        if (isIpInGroup(B, ip)) {
            b++;
            continue;;
        }
        if (isIpInGroup(C, ip)) {
            c++;
            continue;
        }
        if (isIpInGroup(D, ip)) {
            d++;
            continue;
        }
        if (isIpInGroup(E, ip)) {
            e++;
            continue;
        }
    }

    printf("%d %d %d %d %d %d %d\n", a, b, c, d, e, error, pri);
    return 0;
}