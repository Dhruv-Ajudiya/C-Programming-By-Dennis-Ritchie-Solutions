/** REQUIRED HEADER FILES */
#include "circular_linked_list.h"

/*
 * displayMenu	: Displays the menu options to the user.
 * Author	: Dhruv Ajudiya
 * Created	: 21 October 2024
 * Modified	: 21 October 2024
 */
void displayMenu(void)
{
	printf("\n--- Circular Linked List Menu ---\n");
	printf("1. Insert at Beginning\n");
	printf("2. Insert at End\n");
	printf("3. Delete Node\n");
	printf("4. Display linked list\n");
	printf("5. Sum of Even Numbers\n");
	printf("0. Exit\n");
	printf("Enter your choice: ");
} /* End displayMenu() */

/*
 * createNode	: Creates a new node with the given data.
 * Input	: iData (integer data to store in the node)
 * Return	: Pointer to the newly created node.
 * Author	: Dhruv Ajudiya
 * Created	: 21 October 2024
 * Modified	: 21 October 2024
 */
struct Node* createNode(int iData)
{
	struct Node* newNode;	/* Pointer to the new node created */

	newNode = (struct Node*)malloc(sizeof(struct Node));
	if (newNode == NULL) {
		printf("Error: Memory allocation failed\n");
		return NULL;
	}
	newNode->data = iData;
	newNode->next = newNode;

	return newNode;
} /* End createNode() */

/*
 * insertAtBeginning	: Inserts a new node at the beginning of the circular linked list.
 * Input		: head (pointer to head node)
 *			  iData (integer data to insert)
 * Author		: Dhruv Ajudiya
 * Created		: 21 October 2024
 * Modified		: 21 October 2024
 */
void insertAtBeginning(struct Node** head, int iData)
{
	struct Node* newNode;		/* Pointer to the new node created */
	struct Node* current = *head;	/* Pointer to point the current node of the list */

	newNode = (struct Node*)malloc(sizeof(struct Node));
	if (newNode == NULL) {
		printf("Error: Memory allocation failed\n");
		return ;
	}
	newNode->data = iData;

	if (*head == NULL) {
		newNode->next = newNode;
		*head = newNode;
	} else {
		while (current->next != *head)
			current = current->next;

		current->next = newNode;
		newNode->next = *head;
		*head = newNode;
	}
} /* End insertAtBeginning() */

/*
 * insertAtEnd	: Inserts a new node at the end of the circular linked list.
 * Input	: head (pointer to head node)
 *		  iData (integer data to insert)
 * Author	: Dhruv Ajudiya
 * Created	: 21 October 2024
 * Modified	: 21 October 2024
 */
void insertAtEnd(struct Node** head, int iData)
{
	struct Node* newNode;		/* Pointer to the new node created */
	struct Node* current = *head;	/* Pointer to point the current node of the list */

	newNode = (struct Node*)malloc(sizeof(struct Node));
	if (newNode == NULL) {
		printf("Error: Memory allocation failed\n");
		return ;
	}
	newNode->data = iData;

	if (*head == NULL) {
		newNode->next = newNode;
		*head = newNode;
	} else {
		while (current->next != *head)
			current = current->next;

		newNode->next = *head;
		current->next = newNode;
	}
} /* End insertAtEnd() */

/*
 * deleteNode	: Deletes a node from the circular linked list.
 * Input	: head (pointer to head node)
 *		  iData (integer data to delete)
 * Author	: Dhruv Ajudiya
 * Created	: 21 October 2024
 * Modified	: 21 October 2024
 */
void deleteNode(struct Node** head, int iData)
{
	struct Node* current = *head;	/* Pointer to the current node in the list */
	struct Node* prev = NULL;	/* Pointer to the previous node in the list */
	struct Node* temp;		/* Pointer to point current node temporarily */
	struct Node* last;		/* Pointer to the last node in the list */

	if (*head == NULL) {
		printf("Error: Linked list is empty\n");
		return ;
	}

	/* If the list contains only one node */
	if (*head == (*head)->next && (*head)->data == iData) {
		free(*head);
		*head = NULL;
		return ;
	}

	/* Deleting the head node */
	if ((*head)->data == iData) {
		last = *head;
		while (last->next != *head)
			last = last->next;

		last->next = (*head)->next;
		temp = *head;
		*head = (*head)->next;
		free(temp);
		return ;
	}

	/* Deleting other nodes */
	do {
		prev = current;
		current = current->next;
		if (current->data == iData) {
			prev->next = current->next;
			free(current);
			return ;
		}
	} while (current != *head);

	printf("Node with value %d not found\n", iData);
} /* End deleteNode() */

/*
 * display	: Displays the data in the circular linked list.
 * Input	: head (pointer to head node)
 * Author	: Dhruv Ajudiya
 * Created	: 21 October 2024
 * Modified	: 21 October 2024
 */
void display(struct Node* head)
{
	struct Node* current = head;	/* Pointer to the current node of the list */

	if (head == NULL) {
		printf("Error: Linked list is empty\n");
		return ;
	}

	do {
		printf("%d ", current->data);
		current = current->next;
	} while (current != head);

	printf("\n");
} /* End display() */

/*
 * sumOfEvenNumbers	: Calculates the sum of all even numbers in the circular linked list.
 * Input		: head (pointer to head node)
 * Return		: Sum of even numbers (integer)
 * Author		: Dhruv Ajudiya
 * Created		: 21 October 2024
 * Modified		: 21 October 2024
 */
int sumOfEvenNumbers(struct Node* head)
{
	int iSum = 0;			/* Store the sum of even numbers */
	struct Node* current = head;	/* Pointer to the current node of the list */

	if (head == NULL) {
		printf("Error: Linked list is empty\n");
		return iSum;
	}

	do {
		if ((current->data % 2) == 0)
			iSum += current->data;
		current = current->next;
	} while (current != head);

	return iSum;
} /* End sumOfEvenNumbers() */
