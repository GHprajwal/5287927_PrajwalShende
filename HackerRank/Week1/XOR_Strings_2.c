#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main() {
    char first[100005], second[100005];
    if (scanf("%100004s %100004s", first, second) != 2) {
        return 0;
    }
    int length = strlen(first);
    for (int i = 0; i < length; i++) {
        int bit1 = first[i] - '0';
        int bit2 = second[i] - '0';
        int xor_result = bit1 ^ bit2;
        putchar(xor_result + '0');
    }
    putchar('\n');
    return 0;
}
