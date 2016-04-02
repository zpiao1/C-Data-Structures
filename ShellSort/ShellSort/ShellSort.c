#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define MAX 7
int intArray[MAX] = { 4,6,3,2,1,9,7 };
void printline(int count)
{
	while (count-- >= 0)
		putchar('=');
	putchar('\n');
}
void display()
{
	int i;
	putchar('[');
	// navigate through all items
	for (i = 0; i < MAX; i++)
		printf("%d ", intArray[i]);
	printf("]\n");
}
void shellSort()
{
	int inner, outer;
	int valueToInsert;
	int interval = 1;
	int elements = MAX;
	int i = 0;
	while (interval <= elements / 3)
		interval = interval * 3 + 1;
	while (interval > 0)
	{
		printf("Iteration %d#\n", i);
		display();
		for (outer = interval; outer < elements; outer++)
		{
			valueToInsert = intArray[outer];
			inner = outer;
			// Insertion Sort
			while (inner > interval - 1 && intArray[inner - interval] >= valueToInsert)
			{
				intArray[inner] = intArray[inner - interval];
				inner -= interval;
				printf("Item moved: %d\n", intArray[inner]);
			}
			intArray[inner] = valueToInsert;
			printf("Item inserted: %d, at position: %d\n", valueToInsert, inner);
		}
		interval = (interval - 1) / 3;
		i++;
	}
}

int main()
{
	printf("Input Array: ");
	display();
	printline(50);
	shellSort();
	printf("Output Array: ");
	display();
	printline(50);
	return 0;
}