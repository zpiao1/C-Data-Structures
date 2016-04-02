#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int data;
	int key;

	struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

bool isEmpty() 
{
	return head == NULL;
}

int length()
{
	int length = 0;

	// if list is empty
	if (!head)
		return 0;
	
	current = head->next;
	while (current != head)
	{
		length++;
		current = current->next;
	}

	return length;
}

// insert link at the first location
void insertFirst(int key, int data)
{
	// create a link
	struct node *current = head;
	struct node *link = (struct node*) malloc(sizeof(struct node));
	link->key = key;
	link->data = data;
	if (isEmpty())
		link->next = link;
	else
	{
		// point it to old first node
		link->next = head;
		// point first to new first
		while (current && current->next != head)
			current = current->next;
		current->next = link;
	}
	head = link;
}

// delete first item
struct node *deleteFirst()
{
	// save reference to first link
	struct node *tempLink = head;
	struct node *current = head;

	if (!head)
		return NULL;

	if (head->next == head)
		head = NULL;
	else
	{
		while (current && current->next != head)
			current = current->next;
		head = head->next;
		current->next = head;
	}
	return tempLink;
}

// display the list
void printList()
{
	struct node *ptr = head;
	printf("\n[ ");

	// start from the beginning
	if (head)
		do
		{
			printf("(%d, %d) ", ptr->key, ptr->data);
			ptr = ptr->next;
		} while (ptr != head);
	printf(" ]");
}

int main()
{
	insertFirst(1, 10);
	insertFirst(2, 20);
	insertFirst(3, 30);
	insertFirst(4, 1);
	insertFirst(5, 40);
	insertFirst(6, 56);

	printf("Original List: ");
	// print list
	printList();

	head = head->next;
	printList();
	
	while (!isEmpty())
	{
		struct node *temp = deleteFirst();
		printf("\nDeleted value: ");
		printf("(%d, %d) ", temp->key, temp->data);
		free(temp);
	}

	printf("\nList after deleting all items: ");
	printList();

	return 0;
}