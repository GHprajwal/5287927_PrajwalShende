#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define LIMIT 1000000

typedef struct {
    int type;
    char *info;
} Step;

char text[LIMIT + 1];
int size = 0;

Step history[LIMIT];
int histTop = -1;

void doAppend(char *w) {
    int len = strlen(w);
    strncpy(text + size, w, len);
    size += len;
    text[size] = '\0';
    history[++histTop].type = 1;
    history[histTop].info = strdup(w);
}

void doDelete(int k) {
    char *removed = (char *)malloc((k + 1) * sizeof(char));
    strncpy(removed, text + size - k, k);
    removed[k] = '\0';
    size -= k;
    text[size] = '\0';
    history[++histTop].type = 2;
    history[histTop].info = removed;
}

void doPrint(int k) {
    printf("%c\n", text[k - 1]);
}

void doUndo() {
    if (histTop < 0) return;
    Step last = history[histTop--];
    if (last.type == 1) {
        int len = strlen(last.info);
        size -= len;
        text[size] = '\0';
    } else if (last.type == 2) {
        int len = strlen(last.info);
        strncpy(text + size, last.info, len);
        size += len;
        text[size] = '\0';
    }
    free(last.info);
}

int main() {
    int Q;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            char w[LIMIT + 1];
            scanf("%s", w);
            doAppend(w);
        } else if (type == 2) {
            int k;
            scanf("%d", &k);
            doDelete(k);
        } else if (type == 3) {
            int k;
            scanf("%d", &k);
            doPrint(k);
        } else if (type == 4) {
            doUndo();
        }
    }
    return 0;
}
