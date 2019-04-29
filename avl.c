#include <stdlib.h>
#include "header.h"

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