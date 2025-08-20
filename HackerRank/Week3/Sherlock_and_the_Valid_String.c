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

char* isValid(char* s) {
    static char yes[] = "YES";
    static char no[]  = "NO";

    int freq[26] = {0};
    int length = strlen(s);

    for (int i = 0; i < length; i++) {
        freq[s[i] - 'a']++;
    }

    int minFreq = INT_MAX, maxFreq = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            if (freq[i] < minFreq) minFreq = freq[i];
            if (freq[i] > maxFreq) maxFreq = freq[i];
        }
    }

    if (minFreq == maxFreq) {
        return yes;
    }

    int minCount = 0, maxCount = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] == minFreq) minCount++;
        if (freq[i] == maxFreq) maxCount++;
    }

    if (minFreq == 1 && minCount == 1) {
        return yes;
    }

    if (maxFreq - minFreq == 1 && maxCount == 1) {
        return yes;
    }

    return no;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = isValid(s);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);
    if (!data) return NULL;

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) break;

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) return NULL;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
        if (!data) return NULL;
    } else {
        data = realloc(data, data_length + 1);
        if (!data) return NULL;
        data[data_length] = '\0';
    }

    return data;
}
