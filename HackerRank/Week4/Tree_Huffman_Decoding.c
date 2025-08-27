#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
};

struct Node* createNode(char ch, int freq, struct Node* left, struct Node* right) {
    struct Node* n = malloc(sizeof(struct Node));
    n->ch = ch;
    n->freq = freq;
    n->left = left;
    n->right = right;
    return n;
}

int compare(struct Node* a, struct Node* b) {
    if (a->freq != b->freq) return a->freq - b->freq;
    return (unsigned char)a->ch - (unsigned char)b->ch;
}

struct Heap {
    struct Node** arr;
    int size;
};

void push(struct Heap* h, struct Node* node) {
    int i = h->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (compare(h->arr[parent], node) <= 0) break;
        h->arr[i] = h->arr[parent];
        i = parent;
    }
    h->arr[i] = node;
}

struct Node* pop(struct Heap* h) {
    struct Node* top = h->arr[0];
    struct Node* last = h->arr[--h->size];
    int i = 0;
    while (2*i+1 < h->size) {
        int left = 2*i+1, right = left+1, smallest = left;
        if (right < h->size && compare(h->arr[right], h->arr[left]) < 0) smallest = right;
        if (compare(last, h->arr[smallest]) <= 0) break;
        h->arr[i] = h->arr[smallest];
        i = smallest;
    }
    h->arr[i] = last;
    return top;
}

char* strCopy(const char* s) {
    char* d = malloc(strlen(s) + 1);
    strcpy(d, s);
    return d;
}

void assignCodes(struct Node* root, char* path, int depth, char* table[256]) {
    if (!root) return;
    if (!root->left && !root->right) {
        if (depth == 0) { path[0] = '0'; depth = 1; }
        path[depth] = '\0';
        table[(unsigned char)root->ch] = strCopy(path);
        return;
    }
    path[depth] = '0'; assignCodes(root->left, path, depth+1, table);
    path[depth] = '1'; assignCodes(root->right, path, depth+1, table);
}

void decode_huff(struct Node* root, char* encoded) {
    struct Node* cur = root;
    for (int i = 0; encoded[i]; i++) {
        cur = (encoded[i] == '0') ? cur->left : cur->right;
        if (!cur->left && !cur->right) {
            putchar(cur->ch);
            cur = root;
        }
    }
}

int main() {
    char input[10005];
    fgets(input, sizeof(input), stdin);
    int n = strlen(input);
    if (n > 0 && input[n-1] == '\n') input[--n] = '\0';

    int freq[256] = {0};
    for (int i = 0; i < n; i++) freq[(unsigned char)input[i]]++;

    struct Heap h; 
    h.arr = malloc(512 * sizeof(struct Node*));
    h.size = 0;

    for (int c = 0; c < 256; c++)
        if (freq[c] > 0) push(&h, createNode(c, freq[c], NULL, NULL));

    if (h.size == 0) return 0;
    while (h.size > 1) {
        struct Node* left = pop(&h);
        struct Node* right = pop(&h);
        push(&h, createNode('\0', left->freq + right->freq, left, right));
    }

    struct Node* root = pop(&h);

    char* table[256] = {0};
    char path[512];
    assignCodes(root, path, 0, table);

    char encoded[20000]; int idx = 0;
    for (int i = 0; i < n; i++) {
        char* code = table[(unsigned char)input[i]];
        for (int j = 0; code[j]; j++) encoded[idx++] = code[j];
    }
    encoded[idx] = '\0';

    decode_huff(root, encoded);
    return 0;
}
