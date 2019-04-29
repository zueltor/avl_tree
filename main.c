#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "header.h"

int main(void) {
    unsigned int n;

    FILE *f1 = fopen("in.txt", "rb");
    FILE *f2 = fopen("out.txt", "wb");
    if (f1 == NULL) {
        return 1;
    }
    if (f2 == NULL) {
        return 1;
    }

    fscanf(f1, "%d", &n);

    if (n == 0) {
        printf("0");
        return 0;
    }

    node *tree = NULL;
    for (unsigned int i = 0; i < n; i++) {
        int a;
        fscanf(f1, "%d", &a);
        tree = insert(a, tree);
    }
    fprintf(f2, "%d", tree->height);
    delete_tree(tree);
    fclose(f1);
    fclose(f2);
    return 0;
}