#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a) - (*(int*)b);
}

void findZigZagSequence(int *a, int n) {
    qsort(a, n, sizeof(int), cmp);
    int mid = (n - 1) / 2;
    int tmp = a[mid];
    a[mid] = a[n - 1];
    a[n - 1] = tmp;

    int i = mid + 1, j = n - 2;
    while (i < j) {
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        i++; j--;
    }

    for (int k = 0; k < n; k++) {
        if (k) printf(" ");
        printf("%d", a[k]);
    }
    printf("\n");
}

int main(void) {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        scanf("%d", &n);
        int *arr = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
        findZigZagSequence(arr, n);
        free(arr);
    }
    return 0;
}
