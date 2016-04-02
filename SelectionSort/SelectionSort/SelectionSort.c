#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define MAX 7
int intArray[MAX] = { 4,6,3,2,1,9,7 };

void printline(int count)
{
	int i;

	for (i = 0; i < count; i++)
		putchar('=');
	putchar('\n');
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

void selectionSort()
{
	int indexMin, i, j;
	int temp;
	// loop through all numbers
	for (i = 0; i < MAX - 1; i++)
	{
		// set current element as minimum
		indexMin = i;
		// check the element to be minimum
		for (j = i + 1; j < MAX; j++)
			if (intArray[j] < intArray[indexMin])
				indexMin = j;
		if (indexMin != i)
		{
			printf("Items swapped: [%d, %d]\n", intArray[i], intArray[indexMin]);
			// swap the numbers
			temp = intArray[indexMin];
			intArray[indexMin] = intArray[i];
			intArray[i] = temp;
		}

		printf("Iteration %d#: ", i + 1);
		display();
	}
}

int main()
{
	printf("Input Array: ");
	display();
	printline(50);
	selectionSort();
	printf("Output Array: ");
	display();
	printline(50);
	return 0;
}