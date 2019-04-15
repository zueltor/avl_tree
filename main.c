//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct node node;
struct node {
	node *left;
	node *right;
	int val;
	unsigned int height;
};


int tree_balance_factor(node *p)
{
	int heightleft = 0;
	int heightright = 0;
	if (p->left != NULL)
		heightleft = p->left->height;

	if (p->right != NULL)
		heightright = p->right->height;

	return heightright - heightleft;
}

void tree_height(node *p)
{
	int heightleft = 0,
		heightright = 0;

	if (p->left != NULL)
		heightleft = p->left->height;

	if (p->right != NULL)
		heightright = p->right->height;

	p->height = (heightleft > heightright) ? heightleft + 1 : heightright + 1;

}

node *tree_rotate_right(node *tree)
{
	node *p = tree->left;
	tree->left = p->right;
	p->right = tree;
	tree_height(tree);
	tree_height(p);
	return p;
}

node *tree_rotate_left(node *tree)
{
	node *p = tree->right;
	tree->right = p->left;
	p->left = tree;
	tree_height(tree);
	tree_height(p);
	return p;
}

node *balance(node *tree)
{
	tree_height(tree);

	int bfactor = tree_balance_factor(tree);

	if (bfactor == 2)
	{
		if (tree_balance_factor(tree->right) < 0)
		{
			tree->right = tree_rotate_right(tree->right);
		}
		return tree_rotate_left(tree);
	}

	if (bfactor == -2)
	{
		if (tree_balance_factor(tree->left) > 0)
		{
			tree->left = tree_rotate_left(tree->left);
		}
		return tree_rotate_right(tree);
	}
	return tree;
}

node *insert(int val, node *tree)
{
	
	if (tree == NULL)
	{
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

void delete_tree(node *tree)
{
	if (tree == NULL)
		return;
	delete_tree(tree->left);
	delete_tree(tree->right);
	free(tree);
}

int main(void)
{
	unsigned int n;

	scanf_s("%d", &n);

	if (n == 0)
	{
		printf("0");
		return 0;
	}

	node *tree = NULL;
	for (unsigned int i = 0; i < n; i++)
	{
		int a;
		scanf_s("%d", &a);
		tree = insert(a, tree);
	}
	printf("%d", tree->height);
	delete_tree(tree);

	return 0;
}