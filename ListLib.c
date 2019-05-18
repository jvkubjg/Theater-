#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ListLib.h"

void InsertNode(LNODE **LinkedListHead, char CustomerTicket[]) {
	
	LNODE *TempPtr, *PrevPtr, *NewNode;
	
	PrevPtr = NULL;
	TempPtr = *LinkedListHead;
	
	while (TempPtr!= NULL && strcmp(TempPtr->Ticket, CustomerTicket) < 0) {
		PrevPtr = TempPtr;
		TempPtr = TempPtr->next_ptr;
	}
	
	NewNode= malloc(sizeof(LNODE));
	strcpy(NewNode->Ticket, CustomerTicket);
	NewNode->next_ptr = TempPtr;
	
	if (PrevPtr == NULL) {
		*LinkedListHead = NewNode;
	}
	else
	{
		PrevPtr->next_ptr = NewNode;
	}
	
}
	
	
void ReturnAndFreeLinkedListNode(LNODE **LLH, char tickets[])
{
	LNODE *TempPtr;
	TempPtr = *LLH;
	strcpy(tickets, TempPtr->Ticket);
	*LLH = TempPtr->next_ptr; 
	free(TempPtr);
	
	
}
