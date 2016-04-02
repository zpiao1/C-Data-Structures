#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#define MAX 20

// array of items on which linear search will be conducted.
int intArray[MAX] = { 1,2,3,4,6,7,9,11,12,14,15,16,17,19,33,34,43,45,55,66 };

void printline(int count)
{
	int i;
	for (i = 0; i < count - 1; i++)
		printf("=");

	printf("=\n");
}

// this method makes a linear search
int find(int data)
{
	int comparisons = 0;
	int index = -1;
	int i;

	// navigate through all items
	for (i = 0; i < MAX; i++)
	{
		// count the comparisons made
		comparisons++;

		// if data found, break the loop;
		if (data == intArray[i])
		{
			index = i;
			break;
		}
	}
	printf("Total comparisons made: %d\n", comparisons);
	return index;
}

void display()
{
	int i;
	printf("[");

	// navigate through all items
	for (i = 0; i < MAX; i++)
		printf("%d ", intArray[i]);

	printf("]\n");
}

int main()
{
	int location;
	printf("Input Array: ");
	display();
	printline(50);

	// find location of 1
	location = find(55);

	// if element was not found
	if (location != -1)
		printf("\nElement found at location: %d", (location + 1));
	else
		printf("Element not found.");
	return 0;
}