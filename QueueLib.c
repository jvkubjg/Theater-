#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "QueueLib.h"


void enQueue(char CustomerName[], QNODE **QueHead, QNODE **QueTail)
{
    QNODE *NewNode = malloc(sizeof(QNODE)); // Allocatin memory for this qnode
    strcpy(NewNode->Name, CustomerName); // saying Name for the name, which gonna me our name of customer
    NewNode->next_ptr = NULL; // next ptr is gonna point to NULL 
    
                            
    if(*QueHead == NULL) // if the QueHGead is null 
    {
        *QueHead = *QueTail = NewNode; // then we saying QueHead gonna be our NewNode nad QueTail also 
        
    }
    else
    {
        (*QueTail)->next_ptr = NewNode; 
        *QueTail = NewNode;   
    }            
    
}
                     	                                   
void deQueue(QNODE **QueHead) 
{
	QNODE *TempPtr = (*QueHead)->next_ptr; // our QueHead node is already done, we initilizai it TempPtr w
	
	if (*QueHead != NULL) // if the queHead is empty, which shoudnt the be saying message
	{
		free(*QueHead); // deallocats memory 
		*QueHead = TempPtr;  // QueHead gonna be our TempPtr
	}
}


void DisplayQueue(QNODE *QueHead)
{
    QNODE *TempPtr = QueHead;
    while(TempPtr!=NULL)
    {
        printf("%s\n", TempPtr->Name);
        TempPtr = TempPtr->next_ptr;
    }
}
