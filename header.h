#pragma once

typedef struct node node;
struct node {
    node *left;
    node *right;
    int val;
    char height;
};

int avl(char *in, char *out);

int tree_balance_factor(node *p);

void tree_height(node *p);

node *tree_rotate_right(node *tree);

node *tree_rotate_left(node *tree);

node *balance(node *tree);

node *insert(int val, node *tree);

void delete_tree(node *tree);

void print_help(void);
