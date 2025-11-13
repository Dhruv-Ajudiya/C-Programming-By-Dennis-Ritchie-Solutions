#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include <stdio.h>
#include <stdlib.h>

struct dNode {
	int data;
	struct dNode* prev;
	struct dNode* next;
};

void insertDLLNodeAtEnd(struct dNode **head, int data);
void displayDoublyLL(struct dNode *head);
int getDoublyLLLength(struct dNode* head);
void insertDLLNodeAtBegin(struct dNode **head, int data);
void insertDLLNodeAtPosition(struct dNode *head, int index, int data);
int deleteDLLNodeAtPosition(struct dNode **head, int index);
int deleteDLLNodeByValue(struct dNode** head, int value);


#endif /* __DOUBLY_LINKED_LIST_H__ */
