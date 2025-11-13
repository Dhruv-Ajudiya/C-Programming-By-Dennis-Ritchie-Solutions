#include "doubly_linked_list.h"

void insertDLLNodeAtEnd(struct dNode **head, int data)
{
	struct dNode* current;
	struct dNode* newNode;

	if (head == NULL) {
		printf("Error: The head pointer is NULL\n");
		return;
	}

	if (*head == NULL) {
		newNode = (struct dNode *)malloc(sizeof(struct dNode));
		if (newNode == NULL) {
			printf("Error: Memory allocation failed\n");
			return ;
		}
		newNode->data = data;
		newNode->prev = NULL;
		newNode->next = NULL;
		*head = newNode;
	} else {
		current = *head;
		while (current->next != NULL)
			current = current->next;

		newNode = (struct dNode *)malloc(sizeof(struct dNode));
		if (newNode == NULL) {
			printf("Error: Memory allocation failed\n");
			return ;
		}
		newNode->data = data;
		newNode->next = NULL;

		current->next = newNode;
		newNode->prev = current;
	}

}

void insertDLLNodeAtBegin(struct dNode **head, int data)
{
	struct dNode* newNode;

	if (head == NULL) {
		printf("Error: The head pointer is NULL\n");
		return;
	}

	if (*head == NULL) {
		newNode = (struct dNode *)malloc(sizeof(struct dNode));
		if (newNode == NULL) {
			printf("Error: Memory allocation failed\n");
			return ;
		}
		newNode->data = data;
		newNode->prev = NULL;
		newNode->next = NULL;
		*head = newNode;
	} else {
		newNode = (struct dNode *)malloc(sizeof(struct dNode));
		if (newNode == NULL) {
			printf("Error: Memory allocation failed\n");
			return ;
		}
		newNode->data = data;
		newNode->prev = NULL;
		newNode->next = *head;
		*head = newNode;
	}
}

void insertDLLNodeAtPosition(struct dNode *head, int index, int data)
{
	int i;
	struct dNode* current = head;
	struct dNode* newNode;

	if (head == NULL) {
		printf("Error: Doubly linked list is empty, insertion not possible\n");
		return;
	}

	if (index <= 0) {
		printf("Error: Enter valid index\n");
		return ;
	}

	for (i = 0; i < index - 1 && current->next != NULL; i++)
		current = current->next;

	if (i != index - 1) {
		printf("Error: Index out of range\n");
		return;
	}

	newNode = (struct dNode *)malloc(sizeof(struct dNode));
	if (newNode == NULL) {
		printf("Error: Memory allocation failed\n");
		return ;
	}
	newNode->data = data;
	
	newNode->next = current->next;
	newNode->prev = current;

	if (current->next != NULL)
		current->next->prev = newNode;
	current->next = newNode;
}

void displayDoublyLL(struct dNode *head)
{
	struct dNode* current = head;

	if (head == NULL) {
		printf("Error: Doubly linked list is empty\n");
		return ;
	}
	
	while (current != NULL) {
		printf("%d -> ", current->data);
		current = current->next;
	}
	printf("NULL\n");
}

int getDoublyLLLength(struct dNode* head)
{
	int length = 0;
	struct dNode* current = head;

	if (head == NULL) {
		printf("Error: Doubly linked list is empty\n");
		return length;
	}
	
	while (current != NULL) {
		length++;
		current = current->next;
	}

	return length;
}

int deleteDLLNodeAtPosition(struct dNode **head, int index)
{
	int i, data;
	struct dNode *current = *head;
	struct dNode *temp;

	if (*head == NULL) {
		printf("Error: Doubly linked list is empty\n");
		return -1;
	}
	
	if (index < 0) {
		printf("Error: Invalid index\n");
		return -2;
	}

	if (index == 0) {
		data = current->data;
		*head = (*head)->next;
		if (*head != NULL)
			(*head)->prev = NULL;
		free(current);
		return data;
	}

	for (i = 0; i < index - 1 && current->next != NULL; i++)
		current = current->next;

	if (i != index - 1 || current->next == NULL) {
		printf("Error: Invalid index\n");
		return -2;
	}

	temp = current->next;
	data = temp->data;

	current->next = temp->next;
	if (temp->next != NULL)
		temp->next->prev = current;
	
	free(temp);

	return data;
}

int deleteDLLNodeByValue(struct dNode** head, int value)
{
	int i, data;
	struct dNode *current = *head;

	if (*head == NULL) {
		printf("Error: Doubly linked list is empty\n");
		return -1;
	}

	if ((*head)->data == value) {
		data = current->data;
		*head = (*head)->next;
		if (*head != NULL)
			(*head)->prev = NULL;
		free(current);
		return data;
	}

	while (current != NULL && current->data != value)
		current = current->next;
	if (current == NULL) {
		printf("Error: Value %d not found in the list\n", value);
		return -1;
	}
	data = current->data;

	if (current->next != NULL)
		current->next->prev = current->prev;


	if (current->prev != NULL)
		current->prev->next = current->next;
	
	free(current);
	return data;
}
