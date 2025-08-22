#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void get_primes(int *prime_list, int q) {
    int found = 0, candidate = 2;
    while (found < q) {
        if (is_prime(candidate)) {
            prime_list[found++] = candidate;
        }
        candidate++;
    }
}

int* waiter(int n, int* plates, int q, int* result_size) {
    int *prime_list = malloc(q * sizeof(int));
    get_primes(prime_list, q);

    int *stackA = malloc(n * sizeof(int));
    int *stackB = malloc(n * sizeof(int));
    int *answer = malloc(n * sizeof(int));

    int topA = n - 1;
    for (int i = 0; i < n; i++) {
        stackA[i] = plates[i];
    }

    int ans_pos = 0;

    for (int round = 0; round < q; round++) {
        int prime = prime_list[round];
        int newA_top = -1;
        int topB = -1;
        int *nextA = malloc(n * sizeof(int));

        while (topA >= 0) {
            int plate = stackA[topA--];
            if (plate % prime == 0) {
                stackB[++topB] = plate;
            } else {
                nextA[++newA_top] = plate;
            }
        }

        while (topB >= 0) {
            answer[ans_pos++] = stackB[topB--];
        }

        free(stackA);
        stackA = nextA;
        topA = newA_top;
    }

    while (topA >= 0) {
        answer[ans_pos++] = stackA[topA--];
    }

    *result_size = ans_pos;

    free(stackA);
    free(stackB);
    free(prime_list);

    return answer;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    int *plates = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &plates[i]);
    }

    int result_size;
    int *result = waiter(n, plates, q, &result_size);

    for (int i = 0; i < result_size; i++) {
        printf("%d\n", result[i]);
    }

    free(plates);
    free(result);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
