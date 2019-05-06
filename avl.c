#include <stdlib.h>
#include <stdio.h>
#include "header.h"

int avl(char *in, char *out) {
    unsigned int n;
    FILE *f1 = fopen(in, "rb");
    FILE *f2 = fopen(out, "wb");
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

void print_help(void) {
    printf("AVL: <inputfile> <outputfile>");
}


int tree_balance_factor(node *p) {
    int heightleft;
    int heightright;

    heightleft = (p->left != NULL) ? p->left->height : 0;
    heightright = (p->right != NULL) ? p->right->height : 0;

    return heightright - heightleft;
}

void tree_height(node *p) {
    int heightleft;
    int heightright;

    heightleft = (p->left != NULL) ? p->left->height : 0;
    heightright = (p->right != NULL) ? p->right->height : 0;

    p->height = (heightleft > heightright) ? heightleft + 1 : heightright + 1;

}

node *tree_rotate_right(node *tree) {
    node *p = tree->left;
    tree->left = p->right;
    p->right = tree;
    tree_height(tree);
    tree_height(p);
    return p;
}

node *tree_rotate_left(node *tree) {
    node *p = tree->right;
    tree->right = p->left;
    p->left = tree;
    tree_height(tree);
    tree_height(p);
    return p;
}

node *balance(node *tree) {
    tree_height(tree);

    int bfactor = tree_balance_factor(tree);

    if (bfactor == 2) {
        if (tree_balance_factor(tree->right) < 0) {
            tree->right = tree_rotate_right(tree->right);
        }
        return tree_rotate_left(tree);
    }

    if (bfactor == -2) {
        if (tree_balance_factor(tree->left) > 0) {
            tree->left = tree_rotate_left(tree->left);
        }
        return tree_rotate_right(tree);
    }
    return tree;
}

node *insert(int val, node *tree) {

    if (tree == NULL) {
        node *p = malloc(sizeof(node));
        p->left = NULL;
        p->right = NULL;
        p->val = val;
        p->height = 1;
        return p;
    }

    if (val < tree->val)
        tree->left = insert(val, tree->left);
    else
        tree->right = insert(val, tree->right);

    return balance(tree);
}

void delete_tree(node *tree) {
    if (tree == NULL)
        return;
    delete_tree(tree->left);
    delete_tree(tree->right);
    free(tree);
}