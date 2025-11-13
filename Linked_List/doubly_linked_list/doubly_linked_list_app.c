#include "doubly_linked_list.h"

void printMenu(void);

int main(void)
{
	struct dNode *head = NULL;
	int choice, data, position, result;

	while (1) {
		printMenu();
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("Enter data to insert at end: ");
			scanf("%d", &data);
			insertDLLNodeAtEnd(&head, data);
			break;
		case 2:
			printf("Enter data to insert at beginning: ");
			scanf("%d", &data);
			insertDLLNodeAtBegin(&head, data);
			break;
		case 3:
			printf("Enter position to insert at (0-based index): ");
			scanf("%d", &position);
			printf("Enter data to insert: ");
			scanf("%d", &data);
			insertDLLNodeAtPosition(head, position, data);
			break;
		case 4:
			printf("Enter position of node to delete (0-based index): ");
			scanf("%d", &position);
			result = deleteDLLNodeAtPosition(&head, position);
			if (result != -1 && result != -2) {
				printf("Deleted data: %d\n", result);
			}
			break;
		case 5:
			printf("Enter value of node to delete: ");
			scanf("%d", &data);
			result = deleteDLLNodeByValue(&head, data);
			if (result != -1) {
				printf("Deleted data: %d\n", result);
			}
			break;
		case 6:
			printf("Doubly Linked List: ");
			displayDoublyLL(head);
			break;
		case 7:
			printf("Length of Doubly Linked List: %d\n", getDoublyLLLength(head));
			break;
		case 0:
			printf("Exiting program.\n");
			return 0;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	}
	return 0;
}

void printMenu(void)
{
	printf("\n--- Doubly Linked List Operations ---\n");
	printf("1. Insert node at end\n");
	printf("2. Insert node at beginning\n");
	printf("3. Insert node at specific position (Excluding 0-index)\n");
	printf("4. Delete node by position\n");
	printf("5. Delete node by value\n");
	printf("6. Display linked list\n");
	printf("7. Get list length\n");
	printf("0. Exit\n");
}


#if 0
#include "doubly_linked_list.h"

int main(void)
{
	struct dNode *head = NULL;

	insertDLLNodeAtEnd(&head, 5);
	displayDoublyLL(head);
	printf("%d\n", getDoublyLLLength(head));
	insetDLLNodeAtBegin(&head, 1);
	displayDoublyLL(head);
	printf("%d\n", getDoublyLLLength(head));
	insertDLLNodeAtPosition(head, 1, 22);
	displayDoublyLL(head);
	printf("%d\n", getDoublyLLLength(head));
	deleteDLLNodeAtPosition(&head, 0);
	displayDoublyLL(head);
	printf("%d\n", getDoublyLLLength(head));

#endif

#if 0
	insertDLLNodeAtEnd(&head, 15);
	insertDLLNodeAtEnd(&head, 25);
	displayDoublyLL(head);

	insetDLLNodeAtBegin(&head, 10);
	insetDLLNodeAtBegin(&head, 20);
	displayDoublyLL(head);

	insertDLLNodeAtPosition(head, 1, 22);
	insertDLLNodeAtPosition(head, 7, 77);
	displayDoublyLL(head);

	deleteDLLNodeAtPosition(&head, 0);
	displayDoublyLL(head);
	deleteDLLNodeAtPosition(&head, 4);
	displayDoublyLL(head);
	deleteDLLNodeAtPosition(&head, 1);
	displayDoublyLL(head);
	deleteDLLNodeByValue(&head, 15);
	displayDoublyLL(head);
	deleteDLLNodeByValue(&head, 22);
	displayDoublyLL(head);
	deleteDLLNodeByValue(&head, 25);
	displayDoublyLL(head);
	deleteDLLNodeAtPosition(&head, 0);
	displayDoublyLL(head);
	return 0;
}
#endif

