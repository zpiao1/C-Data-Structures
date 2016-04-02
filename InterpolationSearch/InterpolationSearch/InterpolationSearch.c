#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#define MAX 10
// array of items on which interpolation search will be conducted.
int list[MAX] = { 10, 14, 19, 26, 27, 31, 33, 35, 42, 44 };

int interpolationSearch(int data, int *comparisons)
{
	int lo = 0;
	int hi = MAX - 1;
	int mid = -1;
	int index = -1;
	*comparisons = 1;
	while (list[hi] != list[lo] && data >= list[lo] && data <= list[hi])
	{
		(*comparisons)++;
		// probe the mid point
		mid = lo + (data - list[lo]) * (hi - lo) / (list[hi] - list[lo]);
		printf("mid = %d\n", mid);

		if (list[mid] < data)
			lo = mid + 1;
		else if (data < list[mid])
			hi = mid - 1;
		else
		{
			index = mid;
			break;
		}
	}
	--(*comparisons);
	return index;
}

int binarySearch(int data, int *comparisons)
{
	int lo = 0;
	int hi = MAX - 1;
	int mid = -1;
	int index = -1;
	*comparisons = 1;
	while (lo <= hi)
	{
		(*comparisons)++;
		mid = lo + (hi - lo) / 2;
		printf("mid = %d\n", mid);

		if (list[mid] == data)
		{
			index = mid;
			break;
		}
		else
		{
			if (list[mid] < data)
				lo = mid + 1;
			else
				hi = mid - 1;
		}
	}
	 --(*comparisons);
	return index;
}

int main()
{
	int i;
	int comp1, comp2;
	int location1, location2;
	for (i = 0; i < MAX + 3; i++)
	{
		if (i == 0)
		{
			location1 = interpolationSearch(1, &comp1);
			location2 = binarySearch(1, &comp2);
		}	
		else if (i == MAX + 1)
		{
			location1 = interpolationSearch(100, &comp1);
			location2 = interpolationSearch(100, &comp2);
		}
		else if (i == MAX + 2)
		{
			location1 = interpolationSearch(20, &comp1);
			location2 = interpolationSearch(20, &comp2);
		}
		else
		{
			location1 = interpolationSearch(list[i - 1], &comp1);
			location2 = binarySearch(list[i - 1], &comp2);
		}
		if (location1 != -1)
			printf("Interpolation search found element at %d\nAfter %d comparisons\n", location1 + 1, comp1);
		else
			printf("Interpolation search could not find element.\nAfter %d comparisons\n", comp1);

		if (location2 != -1)
			printf("Binary search found element at %d\nAfter %d comparisons\n", location2 + 1, comp2);
		else
			printf("Binary search could not find element.\nAfter %d comparisons\n", comp2);
	}
	return 0;
}