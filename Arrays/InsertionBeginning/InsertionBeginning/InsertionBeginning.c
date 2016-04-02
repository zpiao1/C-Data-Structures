#include <stdio.h>
#define MAX 5

int main()
{
	int array[MAX] = { 2,3,4,5 };
	int N = 4;		// number of elements in array
	int i = 0;		// loop variable
	int value = 1;	// new data element to be stored in array

	// print array before insertion
	printf("Printing array before insertion -\n");

	for (i = 0; i < N; i++)
		printf("array[%d] = %d \n", i, array[i]);

	// now shift rest of elements downwards
	for (i = N - 1; i >= 0; i--)
		array[i + 1] = array[i];

	// add new element at first position
	array[0] = value;

	// increase N to reflect number of elements
	N++;

	// print to confirm
	printf("Printing array after insertion -\n");

	for (i = 0; i < N; i++)
		printf("array[%d] = %d\n", i, array[i]);

	return 0;
}