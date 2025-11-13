/*
 * This program demonstrates operations on a circular linked list such as insertion, deletion,
 * displaying the list, and calculating the sum of even numbers in the list.
 * Author   : Dhruv Ajudiya
 * Created  : 21 October 2024
 * Modified : 21 October 2024
 */

/** REQUIRED HEADER FILES */
#include "circular_linked_list.h"

/** MAIN PROGRAM */
/*
 * main: Demonstrates program for performing various circular linked list operations.
 */
int main(void)
{
	struct Node* head = NULL;	/* Pointer to the head of the circular linked list */
	int iChoice;			/* Store user's menu choice */
	int iData;			/* Store data for insertion/deletion */

	while (1) {
		displayMenu();
		scanf("%d", &iChoice);

		switch (iChoice) {
		case 1:
			printf("Enter the value to insert at the beginning: ");
			scanf("%d", &iData);
			insertAtBeginning(&head, iData);
			break;
		case 2:
			printf("Enter the value to insert at the end: ");
			scanf("%d", &iData);
			insertAtEnd(&head, iData);
			break;
		case 3:
			printf("Enter the value to delete: ");
			scanf("%d", &iData);
			deleteNode(&head, iData);
			break;
		case 4:
			display(head);
			break;
		case 5:
			printf("Sum of even numbers: %d\n", sumOfEvenNumbers(head));
			break;
		case 0:
			printf("Exiting program...\n");
			return 0;
		default:
			printf("Invalid choice! Please try again.\n");
			break;
		}
	}

	return 0;
} /* End main() */

