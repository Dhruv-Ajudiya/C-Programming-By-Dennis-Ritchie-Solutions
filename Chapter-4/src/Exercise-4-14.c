/*
 * This program demonstrates the use of a macro to swap two values of specified types.
 * Author	: Dhruv Ajudiya
 * Created	: 29 August 2024
 * Modified	: 29 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MACRO DEFINITIONS */
/* Macro to swap two values of type t */
#define SWAP(t, x, y) {	\
	t temp;		\
	temp = x;	\
	x = y;		\
	y = temp;	\
}

/** MAIN PROGRAM */
/*
 * main: It provides user to choose the type of values to swap (integer, float, char or double),
 *	 takes input for two values of the chosen type, performs the swap using the SWAP macro,
 *	 and prints the swapped values.
 */
int main(void)
{
	int iIntValue1, iIntValue2;		/* Integer values to swap */
	float fFloatValue1, fFloatValue2;	/* Float values to swap */
	double dDoubleValue1, dDoubleValue2;	/* Double values to swap */
	char cCharValue1, cCharValue2;		/* Character values to swap */
	char cUserChoice;			/* User choice for the type of swap */

	printf("Enter 'I' to swap integer values\n"
		"Enter 'F' to swap float values\n"
		"Enter 'D' to swap double values\n"
		"Enter 'C' to swap character values\n");
	scanf("%c", &cUserChoice);

	switch (cUserChoice) {
	case 'I':
		printf("Enter the two integer values: ");
		scanf("%d %d", &iIntValue1, &iIntValue2);
		SWAP(int, iIntValue1, iIntValue2);
		printf("After swapping integer values: %d %d\n", iIntValue1, iIntValue2);
		break;
	case 'F':
		printf("Enter the two float values: ");
		scanf("%f %f", &fFloatValue1, &fFloatValue2);
		SWAP(float, fFloatValue1, fFloatValue2);
		printf("After swapingd float values: %f %f\n", fFloatValue1, fFloatValue2);
		break;
	case 'D':
		printf("Enter the two double values: ");
		scanf("%lf %lf", &dDoubleValue1, &dDoubleValue2);
		SWAP(double, dDoubleValue1, dDoubleValue2);
		printf("After swapping double values: %lf %lf\n", dDoubleValue1, dDoubleValue2);
		break;
	case 'C':
		printf("Enter the two character values: ");
		scanf(" %c %c", &cCharValue1, &cCharValue2);
		SWAP(char, cCharValue1, cCharValue2);
		printf("After swapping character values: %c %c\n", cCharValue1, cCharValue2);
		break;
	default:
		printf("Error: Invalid choice\n");
		break;
	}

	return 0;
} /* End main() */
