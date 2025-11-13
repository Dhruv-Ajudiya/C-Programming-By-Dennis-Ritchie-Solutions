#ifndef __CIRCULAR_LINKED_LIST_H__
#define __CIRCULAR_LINKED_LIST_H__

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>

/** STRUCTURE DEFINITION */
struct Node {
	int data;
	struct Node* next;
};

/** FUNCTION PROTOTYPES */
struct Node* createNode(int iData);
void insertAtBeginning(struct Node** head, int iData);
void insertAtEnd(struct Node** head, int iData);
void deleteNode(struct Node** head, int iData);
void display(struct Node* head);
int sumOfEvenNumbers(struct Node* head);
void displayMenu(void);

#endif /* __CIRCULAR_LINKED_LIST_H__ */
