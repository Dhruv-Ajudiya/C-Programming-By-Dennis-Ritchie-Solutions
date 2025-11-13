/*
 * This program writes a version of binary search function with only one test
 * inside the loop and measure the difference in run-time for both versions.
 * Author	: Dhruv Ajudiya
 * Created	: 21 August 2024
 * Modified	: 21 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <time.h>

/** REQUIRED MACRO */
#define MAXLENGTH	100	/* Maximum length of the array */

/** FUNCTION PROTOTYPES */
int binarySearchOneTest(int iTargetValue, int iSortedArray[], int iArraySize);
int binarySearchTwoTests(int iTargetValue, int iSortedArray[], int iArraySize);
void bubbleSort(int iInputArray[], int iArraySize);

/** MAIN PROGRAM */
/*
 * main: It takes sorted array along with its size and the value to search for
 *	 from the user and calls the binary search function with one test case
 *	 and two test case in it and calculates the difference in run-time for both
 *	 versions.
 */
int main(void)
{
	int iTargetValue = 0;			/* Value to be searched */
	int iSortedArray[MAXLENGTH] = {0};	/* Array to store user input */
	int iArraySize = 0;			/* Size of the input array */
	int i = 0;				/* Index variable to iterate in loop */
	int iResult;				/* Result of the binary search function */

	clock_t startTime, endTime;	/* To measure execution time */
	double dCpuTimeUsed;		/* Stores the time taken by a function */

	printf("Enter the size of array: ");
	scanf("%d", &iArraySize);
	printf("Enter the array in increasing order: ");
	for (i = 0; i < iArraySize; i++)
		scanf("%d", &iSortedArray[i]);
	printf("Enter the value of target to be found: ");
	scanf("%d", &iTargetValue);

	bubbleSort(iSortedArray, iArraySize);

	/* Measure and display runtime of the binary search with two test cases */
	startTime = clock();
	iResult =  binarySearchTwoTests(iTargetValue, iSortedArray, iArraySize);
	if (iResult == -1)
		printf("Element %d not found in the array\n", iTargetValue);
	else
		printf("\nPosition of target is: %d", iResult);
	endTime = clock();
	dCpuTimeUsed = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
	printf("\nTime taken for original binary search: %f seconds\n", dCpuTimeUsed);

	/* Measure and display runtime of the binary search with one test case */
	startTime = clock();
	iResult =  binarySearchTwoTests(iTargetValue, iSortedArray, iArraySize);
	if (iResult == -1)
		printf("Element %d not found in the array\n", iTargetValue);
	else
		printf("\nPosition of target is: %d", iResult);
	endTime = clock();
	dCpuTimeUsed = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
	printf("\nTime taken for optimized binary search: %f seconds\n", dCpuTimeUsed);

	return 0;
} /* End main() */

/*
 * binarySearchTwoTests	: Performs a binary search with two tests inside the loop
 * Input		: iTargetValue (value to search for)
 *			  iSortedArray (sorted array in which to search)
 *			  iArraySize (size of the array)
 * Return		: The position of the target value in the array, or -1 if not found
 * Author		: Dhruv Ajudiya
 * Created		: 21 August 2024
 * Modified		: 21 August 2024
 */
int binarySearchTwoTests(int iTargetValue, int iSortedArray[], int iArraySize)
{
	int iLowIndex = 0;			/* Lowest value of the array index */
	int iHighIndex = iArraySize - 1;	/* Highest value of the array index */
	int iMidIndex = 0;			/* Mid value of the array index */

	while (iLowIndex <= iHighIndex) {
		iMidIndex = (iLowIndex + iHighIndex) / 2;
		if (iTargetValue < iSortedArray[iMidIndex])
			iHighIndex = iMidIndex - 1;
		else if (iTargetValue > iSortedArray[iMidIndex])
			iLowIndex = iMidIndex + 1;
		else
			return iMidIndex; /* Target found */
	}

	return -1; /* No match found */
} /* End binarySearchTwoTests() */

/*
 * binarySearchOneTest	: Performs a binary search with only one test inside the loop
 * Input		: iTargetValue (value to search for)
 *			  iSortedArray (sorted array in which to search)
 *			  iArraySize (size of the array)
 * Return		: The position of the target value in the array, or -1 if not found
 * Author		: Dhruv Ajudiya
 * Created		: 21 August 2024
 * Modified		: 21 August 2024
 */
int binarySearchOneTest(int iTargetValue, int iSortedArray[], int iArraySize)
{
	int iLowIndex = 0;			/* Lowest value of the array index */
	int iHighIndex = iArraySize - 1;	/* Highest value of the array index */
	int iMidIndex = 0;			/* Mid value of the array index */

	while (iLowIndex <= iHighIndex && iTargetValue != iSortedArray[iMidIndex]) {
		iMidIndex = (iLowIndex + iHighIndex) / 2;
		if (iTargetValue < iSortedArray[iMidIndex])
			iHighIndex = iMidIndex - 1;
		else
			iLowIndex = iMidIndex + 1;
	}

	if (iTargetValue == iSortedArray[iMidIndex])
		return iMidIndex; /* Target found */
	else
		return -1; /* No match found */
} /* End binarySearchOneTest() */

/*
 * bubbleSort	: Sorts the array in increasing order using the Bubble Sort algorithm.
 * Input	: iInputArray[] (the array to be sorted)
 *		  iArraySize (size of the array)
 * Output	: Array is sorted in place
 * Author	: Dhruv Ajudiya
 * Created	: 21 August 2024
 * Modified	: 21 August 2024
 */
void bubbleSort(int iInputArray[], int iArraySize)
{
	int i, j;	/* Index vairable to iterate in the loop */
	int iTemp;	/* Temporary variable for swapping */

	for (i = 0; i < iArraySize - 1; i++) {
		for (j = 0; j < iArraySize - i - 1; j++) {
			if (iInputArray[j] > iInputArray[j + 1]) {
				iTemp = iInputArray[j];
				iInputArray[j] = iInputArray[j + 1];
				iInputArray[j + 1] = iTemp;
			}
		}
	}
} /* End bubbleSort() */
