#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
typedef struct node {
	int data;
	struct node *left;
	struct node *right;

	int height;
} node;

bool isEmpty(node *root)
{
	return !root;
}

int getHeight(node *root)
{
	if (!root)
		return -1;
	else
		return root->height;
}

node *constructNode(int data)
{
	node *newNode = (node *)malloc(sizeof(node));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	newNode->height = 0;
	return newNode;
}

void update(node *n)
{
	if (n)
		n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
}

void rotateRight(node **ptrRoot)
{
	node *pivot;
	if (!*ptrRoot)
		return;
	pivot = (*ptrRoot)->left;
	(*ptrRoot)->left = pivot->right;
	pivot->right = *ptrRoot;
	*ptrRoot = pivot;
}

void rotateLeft(node **ptrRoot)
{
	node *pivot;
	if (!*ptrRoot)
		return;
	pivot = (*ptrRoot)->right;
	(*ptrRoot)->right = pivot->left;
	pivot->left = *ptrRoot;
	*ptrRoot = pivot;
}

void rebalance(node **ptrRoot)
{
	int leftHeight, rightHeight;
	if (!*ptrRoot)
		return;
	leftHeight = getHeight((*ptrRoot)->left);
	rightHeight = getHeight((*ptrRoot)->right);
	if (leftHeight > 1 + rightHeight)
	{
		if (getHeight((*ptrRoot)->left->left) < getHeight((*ptrRoot)->left->right))
			rotateLeft(&((*ptrRoot)->left));
		rotateRight(ptrRoot);
	}
	else if (rightHeight > 1 + leftHeight)
	{
		if (getHeight((*ptrRoot)->right->right) < getHeight((*ptrRoot)->right->left))
			rotateRight(&((*ptrRoot)->right));
		rotateLeft(ptrRoot);
	}
	update((*ptrRoot)->left);
	update((*ptrRoot)->right);
	update(*ptrRoot);
}

void insert(node **ptrRoot, int data)
{
	if (!(*ptrRoot))
		*ptrRoot = constructNode(data);
	else if ((*ptrRoot)->data > data)
		insert(&((*ptrRoot)->left), data);
	else if ((*ptrRoot)->data < data)
		insert(&((*ptrRoot)->right), data);
	rebalance(ptrRoot);
}

void inOrderTraversal(node *root)
{
	if (root)
	{
		inOrderTraversal(root->left);
		printf("%d ", root->data);
		inOrderTraversal(root->right);
	}
}

node * findSuccessor(node *root)
{
	node *curr;
	if (!root)
		return NULL;
	curr = root->right;
	while (curr && curr->left)
		curr = curr->left;
	return curr;
}

void removeNode(node **ptrRoot, int data)
{
	node *toBeRemoved;
	if (!(*ptrRoot))
		return;
	if ((*ptrRoot)->data < data)
		removeNode(&((*ptrRoot)->right), data);
	else if ((*ptrRoot)->data > data)
		removeNode(&((*ptrRoot)->left), data);
	else
	{
		if ((*ptrRoot)->left && (*ptrRoot)->right)
		{
			toBeRemoved = findSuccessor(*ptrRoot);
			(*ptrRoot)->data = toBeRemoved->data;
			removeNode(&((*ptrRoot)->right), toBeRemoved->data);
		}
		else
		{
			toBeRemoved = *ptrRoot;
			*ptrRoot = ((*ptrRoot)->left ? (*ptrRoot)->left : (*ptrRoot)->right);
			free(toBeRemoved);
		}
	}
	rebalance(ptrRoot);
}


int main()
{
	int i;
	node *root = NULL;
	srand((unsigned int)time(NULL));
	for (i = 1; i < 30; i++)
		insert(&root, rand() % 500);
	inOrderTraversal(root);
	putchar('\n');
	while (!isEmpty(root))
	{
		printf("Data to be removed: %d\n", root->data);
		removeNode(&root, root->data);
		inOrderTraversal(root);
		putchar('\n');
	}
	return 0;
}