#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node {
	int data;
	struct node *left;
	struct node *right;
} node;

bool isEmpty(node *root)
{
	return !root;
}
// Iterative functions
void insert(node **ptrRoot, int data)
{
	node *newNode = (node *)malloc(sizeof(node));
	node *curr = *ptrRoot;
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	if (!(*ptrRoot))
		*ptrRoot = newNode;
	else
	{
		while (curr)
		{
			if (curr->data > data)
				if (curr->left)
					curr = curr->left;
				else
				{
					curr->left = newNode;
					return;
				}
			else if (curr->data < data)
				if (curr->right)
					curr = curr->right;
				else
				{
					curr->right = newNode;
					return;
				}
		}
	}
}

node *search(node *root, int data)
{
	node *curr = root;
	while (curr)
	{
		if (curr->data == data)
			return curr;
		else if (curr->data > data)
			curr = curr->left;
		else
			curr = curr->right;
	}
	// curr is NULL now
	return curr;
}

node *findSuccessor(node *root)
{
	node *curr;
	if (!(root->left) || !(root->right))
		return NULL;
	curr = root->right;
	while (curr->left)
		curr = curr->left;
	return curr;
}

void removeNode(node **ptrRoot, int data)
{
	node *curr = *ptrRoot;
	node *parent = NULL;
	node *replace;
	if (!(*ptrRoot))
	{
		fprintf(stderr, "Tree is empty!\n");
		return;
	}
	// The node is the root
	if ((*ptrRoot)->data == data)
	{
		// change to root to its existent child or NULL if no existent child
		*ptrRoot = ((*ptrRoot)->left ? (*ptrRoot)->left : (*ptrRoot)->right);
		free(curr);
		return;
	}
	while (curr)
	{
		// moving towards to node to be removed
		// move the parent as well
		if (curr->data > data)
		{
			parent = curr;
			curr = curr->left;
		} 
		else if (curr->data < data)
		{
			parent = curr;
			curr = curr->right;
		}
		else
		{
			// curr->data == data, node is found
			// Case 1: both children exist
			if (curr->left && curr->right)
			{
				// look for its successor
				replace = findSuccessor(curr);
				// replace the data with the successor's
				curr->data = replace->data;
				// move towards the replace
				parent = curr;
				curr = curr->right;
				while (curr)
				{
					if (curr->data > replace->data)
					{
						parent = curr;
						curr = curr->left;
					}
					else if (curr->data < replace->data)
					{
						parent = curr;
						curr = curr->right;
					}
					// found the replace
					// replace can have at most a right child (tree)
					else
					{
						if (curr == parent->left)
							parent->left = (curr->right ? curr->right : curr->left);
						else
							parent->right = (curr->right ? curr->right : curr->left);
						break;
					}
				}
			}
			// Case 2 & 3: at most one child exists
			else
			{
				if (curr == parent->left)
					parent->left = (curr->left ? curr->left : curr->right);
				else 
					parent->right = (curr->right ? curr->right : curr->left);
			}
			free(curr);
			return;
		}
	}
	// curr == NULL, cannot find the node to be removed
	fprintf(stderr, "The node is not found!\n");
}

// recursive functions
void recInsert(node **ptrRoot, int data)
{
	if (!(*ptrRoot))
	{
		*ptrRoot = (node *)malloc(sizeof(node));
		(*ptrRoot)->left = (*ptrRoot)->right = NULL;
		(*ptrRoot)->data = data;
	}
	else if ((*ptrRoot)->data > data)
		recInsert(&((*ptrRoot)->left), data);
	else if ((*ptrRoot)->data < data)
		recInsert(&((*ptrRoot)->right), data);
}

node *recSearch(node *root, int data)
{
	if (!root)
	{
		fprintf(stderr, "The tree is empty!\n");
		return NULL;
	}
	if (root->data > data)
		return recSearch(root->left, data);
	else if (root->data < data)
		return recSearch(root->right, data);
	else
		return root;
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
// Use this to the node to be moved with recFindMin(curr-right);
node *recFindMin(node *root)
{
	return (root->left ? recFindMin(root->left) : root);
}

void recRemoveNode(node **ptrRoot, int data)
{
	node *toBeRemoved;
	if (!(*ptrRoot))
	{
		fprintf(stderr, "The node is not found!\n");
		return;
	}
	if ((*ptrRoot)->data < data)
		recRemoveNode(&((*ptrRoot)->right), data);
	else if ((*ptrRoot)->data > data)
		recRemoveNode(&((*ptrRoot)->left), data);
	else
	{
		if ((*ptrRoot)->left && (*ptrRoot)->right)
		{
			toBeRemoved = recFindMin((*ptrRoot)->right);
			(*ptrRoot)->data = toBeRemoved->data;
			recRemoveNode(&((*ptrRoot)->right), toBeRemoved->data);
		}
		else
		{
			toBeRemoved = *ptrRoot;
			*ptrRoot = ((*ptrRoot)->left ? (*ptrRoot)->left : (*ptrRoot)->right);
			free(toBeRemoved);
		}
	}
}

int main()
{
	node *iterRoot = NULL;
	node *recRoot = NULL;
	node *temp = NULL;
	int array[7] = { 27, 14, 35, 10, 19, 31, 42 };
	int i;
	for (i = 0; i < 7; i++)
		insert(&iterRoot, array[i]);
	for (i = 0; i < 7; i++)
		recInsert(&recRoot, array[i]);
	printf("iterRoot: in order traversal: \n");
	inOrderTraversal(iterRoot);
	putchar('\n');
	printf("recRoot: in order traversal: \n");
	inOrderTraversal(recRoot);
	putchar('\n');

	i = 14;
	temp = search(iterRoot, i);
	if (temp)
	{
		printf("Element found: %d\n", temp->data);
		removeNode(&iterRoot, temp->data);
		inOrderTraversal(iterRoot);
		putchar('\n');
	}
	else
		printf("Element not found\n");

	temp = recSearch(recRoot, i);
	if (temp)
	{
		printf("Element found: %d\n", temp->data);
		recRemoveNode(&recRoot, temp->data);
		inOrderTraversal(recRoot);
		putchar('\n');
	}
	else
		printf("Element not found\n");

	i = 35;
	temp = search(iterRoot, i);
	if (temp)
	{
		printf("Element found: %d\n", temp->data);
		removeNode(&iterRoot, temp->data);
		inOrderTraversal(iterRoot);
		putchar('\n');
	}
	else
		printf("Element not found\n");

	temp = recSearch(recRoot, i);
	if (temp)
	{
		printf("Element found: %d\n", temp->data);
		recRemoveNode(&recRoot, temp->data);
		inOrderTraversal(recRoot);
		putchar('\n');
	}
	else
		printf("Element not found\n");

	while (!isEmpty(iterRoot))
		removeNode(&iterRoot, iterRoot->data);
	printf("iterRoot: in order traversal: \n");
	inOrderTraversal(iterRoot);
	putchar('\n');

	while (!isEmpty(recRoot))
		recRemoveNode(&recRoot, recRoot->data);
	printf("recRoot: in order traversal: \n");
	inOrderTraversal(recRoot);
	putchar('\n');

	return 0;
}