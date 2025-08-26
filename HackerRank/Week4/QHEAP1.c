#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define LIMIT 100000

int heap[LIMIT];
int count = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void siftUp(int pos) {
    while (pos > 0) {
        int parent = (pos - 1) / 2;
        if (heap[pos] < heap[parent]) {
            swap(&heap[pos], &heap[parent]);
            pos = parent;
        } else {
            break;
        }
    }
}

void siftDown(int pos) {
    while (1) {
        int left = 2 * pos + 1;
        int right = 2 * pos + 2;
        int smallest = pos;

        if (left < count && heap[left] < heap[smallest]) smallest = left;
        if (right < count && heap[right] < heap[smallest]) smallest = right;

        if (smallest != pos) {
            swap(&heap[pos], &heap[smallest]);
            pos = smallest;
        } else {
            break;
        }
    }
}

void add(int x) {
    heap[count] = x;
    siftUp(count);
    count++;
}

void removeVal(int x) {
    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (heap[i] == x) {
            idx = i;
            break;
        }
    }
    if (idx == -1) return;

    heap[idx] = heap[count - 1];
    count--;
    siftDown(idx);
    siftUp(idx);
}

int peekMin() {
    return heap[0];
}

int main() {
    int queries;
    scanf("%d", &queries);

    while (queries--) {
        int type, val;
        scanf("%d", &type);

        if (type == 1) {
            scanf("%d", &val);
            add(val);
        } else if (type == 2) {
            scanf("%d", &val);
            removeVal(val);
        } else if (type == 3) {
            printf("%d\n", peekMin());
        }
    }
    return 0;
}
