#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct node {
	int data;

	struct node *leftChild;
	struct node *rightChild;
};

typedef struct _stacknode {
	struct node *item;
	struct _stacknode *next;
} stack_node;

typedef struct _stack {
	stack_node *top;
} stack;

struct node *root = NULL;
void insert(int data)
{
	struct node *tempNode = (struct node*)malloc(sizeof(struct node));
	struct node *current;
	struct node *parent;

	tempNode->data = data;
	tempNode->leftChild = NULL;
	tempNode->rightChild = NULL;

	// if tree is empty
	if (!root)
		root = tempNode;
	else
	{
		current = root;
		parent = NULL;
		while (1)
		{
			parent = current;
			// go to left of the tree
			if (data < parent->data)
			{
				current = current->leftChild;
				// insert to the left
				if (current == NULL)
				{
					parent->leftChild = tempNode;
					return;
				}
			}	// go to right of the tree
			else
			{
				current = current->rightChild;

				// insert to the right
				if (current == NULL)
				{
					parent->rightChild = tempNode;
					return;
				}
			}
		}
	}
}

bool is_empty_stack(stack *ptr_stack)
{
	return !(ptr_stack->top);
}

void push(stack *ptr_stack, struct node *item)
{
	stack_node *new_node = (stack_node *)malloc(sizeof(stack_node));
	if (!ptr_stack)
		return;
	new_node->item = item;
	if (is_empty_stack(ptr_stack))
		new_node->next = NULL;
	else
		new_node->next = ptr_stack->top;
	ptr_stack->top = new_node;
}

struct node *pop(stack *ptr_stack)
{
	struct node *ret = NULL;
	stack_node *temp = NULL;
	if (!ptr_stack || is_empty_stack(ptr_stack))
		return NULL;
	temp = ptr_stack->top;
	ret = temp->item;
	ptr_stack->top = temp->next;
	free(temp);
	return ret;
}

void remove_all_items(stack *ptr_stack)
{
	stack_node *temp = NULL;
	if (!ptr_stack)
		return;
	while (!is_empty_stack(ptr_stack))
		pop(ptr_stack);
}

struct node *peek(stack *ptr_stack)
{
	if (is_empty_stack(ptr_stack))
		return NULL;
	return ptr_stack->top->item;
}
struct node* search(int data)
{
	struct node *current = root;
	printf("Visiting elements: ");
	while (current->data != data)
	{
		if (current != NULL)
			printf("%d ", current->data);
		// go to left tree
		if (current->data > data)
			current = current->leftChild;
		// else go to right tree
		else
			current = current->rightChild;
		// not found
		if (current == NULL)
			return NULL;
	}
	return current;
}

void pre_order_traversal(struct node* root)
{
	if (root != NULL)
	{
		printf("%d ", root->data);
		pre_order_traversal(root->leftChild);
		pre_order_traversal(root->rightChild);
	}
}

// If leftChild exists and is not visited, push leftChild
// Else (important!!) if rightChild exists and is not visited, puch rightChild
// Else (both children don't exist or both children have been visited), pop current node
// Print if both children don't exist or both children have not been visited
void iterative_pre_order_traversal(struct node *root)
{
	bool visited_left = false, visited_right = false;
	stack s;
	struct node *curr = NULL, *parent = NULL;
	if (!root)
		return;
	s.top = NULL;
	push(&s, root);
	while (!is_empty_stack(&s))
	{
		curr = peek(&s);
		if ((!curr->leftChild || !visited_left) &&
            (!curr->rightChild || !visited_right))
			printf("%d ", curr->data);
		if (curr->leftChild && !visited_left)
		{
			push(&s, curr->leftChild);
			visited_right = false;
		}
		else if (curr->rightChild && !visited_right)
		{
			push(&s, curr->rightChild);
			visited_left = false;
		}
		else
		{
			pop(&s);
			if (!is_empty_stack(&s))
			{
				parent = peek(&s);
				visited_right = (curr == parent->rightChild);
				visited_left = true;
			}
		}
	}
}
void in_order_traversal(struct node *root)
{
	if (root)
	{
		in_order_traversal(root->leftChild);
		printf("%d ", root->data);
		in_order_traversal(root->rightChild);
	}
}

// Print if both children don't exist
// or leftChild exists and visited and rightChild doesn't exist or rightChild exists and not visited
// or only rightChild exists and not visited
void iterative_in_order_traversal(struct node *root)
{
	bool visited_left = false, visited_right = false;
	stack s;
	struct node *curr = NULL, *parent = NULL;
	if (!root)
		return;
	s.top = NULL;
	push(&s, root);
	while (!is_empty_stack(&s))
	{
		curr = peek(&s);
		if ((!curr->leftChild || visited_left) &&
			(!curr->rightChild || !visited_right))
			printf("%d ", curr->data);
		if (curr->leftChild && !visited_left)
		{
			push(&s, curr->leftChild);
			visited_right = false;
		}
		else if (curr->rightChild && !visited_right)
		{
			push(&s, curr->rightChild);
			visited_left = false;
		}
		else
		{
			pop(&s);
			if (!is_empty_stack(&s))
			{
				parent = peek(&s);
				visited_right = (curr == parent->rightChild);
				visited_left = true;
			}
		}
	}
}
void post_order_traversal(struct node *root)
{
	if (root)
	{
		post_order_traversal(root->leftChild);
		post_order_traversal(root->rightChild);
		printf("%d ", root->data);
	}
}
// Push any unvisited child, pop any parent whose both children have been visited
void iterative_post_order_traversal(struct node *root)
{
	bool visited_left = false, visited_right = false;
	stack s;
	struct node *curr = NULL, *parent = NULL;
	if (!root)
		return;
	s.top = NULL;
	push(&s, root);
	while (!is_empty_stack(&s))
	{
		curr = peek(&s);
		if ((!curr->leftChild || visited_left) &&
            (!curr->rightChild || visited_right))
			printf("%d ", curr->data);
		if (curr->leftChild && !visited_left)
		{
			push(&s, curr->leftChild);
			visited_right = false;
		}
		else if (curr->rightChild && !visited_right)
		{
			push(&s, curr->rightChild);
			visited_left = false;
		}
		else
		{
			pop(&s);
			if (!is_empty_stack(&s))
			{
				parent = peek(&s);
				visited_right = (parent->rightChild == curr);
				visited_left = true;
			}
			// Implicitly the same as a separate if:
			// if ((!curr->leftChild && !curr->rightChild) ||
			//     (visited_left && visited_right))
			//printf("%d ", curr->data);
		}
	}
}
int main()
{
	int i;
	int array[] = { 27,14,35,10,42 };
	struct node *temp;
	for (i = 0; i < 5; i++)
		insert(array[i]);

	i = 31;
	temp = search(i);
	if (temp)
		printf("[%d] Element found.\n", temp->data);
	else
		printf("[ x ] Element not found (%d).\n", i);

	i = 15;
	temp = search(i);
	if (temp)
		printf("[%d] Element found.\n", temp->data);
	else
		printf("[ x ] Element not found (%d).\n", i);

	printf("\nPreorder traversal: ");
	pre_order_traversal(root);

	printf("\nIterative preorder traversal: ");
	iterative_pre_order_traversal(root);

	printf("\nInorder traversal: ");
	in_order_traversal(root);

	printf("\nIterative inorder traversal: ");
	iterative_in_order_traversal(root);

	printf("\nPost order traversal: ");
	post_order_traversal(root);

	printf("\nIterative post order traversal: ");
	iterative_post_order_traversal(root);
	return 0;
}