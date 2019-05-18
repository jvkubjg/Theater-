#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "StackLib.h"


void push(SNODE **StackTop, LNODE *LLH, int ReceiptN, char TheaterName[])
{
	SNODE *NewNode = malloc(sizeof(SNODE));
	strcpy(NewNode->MovieTheaterName,TheaterName);
	//printf("%s\n",NewNode->MovieTheaterName);
	NewNode->ReceiptNumber = ReceiptN;
	//printf("%d\n", NewNode->ReceiptNumber);
	NewNode->next_ptr = NULL;
	NewNode->TicketList = LLH;
	if(*StackTop == NULL)
	{
		*StackTop = NewNode;
	}
	else 
	{
		NewNode->next_ptr = *StackTop;
		*StackTop = NewNode;
	}
}

// First parameter - Address of StackTop
void pop(SNODE **StackTop)
{
	SNODE *TempPtr = *StackTop;
	if(*StackTop == NULL)
	{
		printf("Stack is empty\n");
	}
	else 
	{
		free(*StackTop);
		*StackTop = TempPtr->next_ptr;
	}
}
