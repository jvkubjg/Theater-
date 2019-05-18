#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BSTLib.h"

// First parameter - Address of BSTnode
// Second parameter - MovieTheaterName
// Third parameter - ZipCode
// Fourth parameter - FileName containing seat map (XXXOOOO)
// Fifth parameter - Dimensions of theater

void AddBSTNode(BNODE **CurrentNode, char MovieTheaterName[], char ZipCode[], char FileName[], char Dimensions[]) {

	if (*CurrentNode == NULL) {
		*CurrentNode = (BNODE *)malloc(sizeof(BNODE));
		(*CurrentNode)->left = (*CurrentNode)->right = NULL;
		strcpy((*CurrentNode)->MovieTheaterName, MovieTheaterName);
		strcpy((*CurrentNode)->ZipCode, ZipCode);
		strcpy((*CurrentNode)->FileName, FileName);
		strcpy((*CurrentNode)->Dimensions, Dimensions);
	} else {
		if (strcmp(ZipCode, (*CurrentNode)->ZipCode) < 0) {
			AddBSTNode(&((*CurrentNode)->left), MovieTheaterName, ZipCode, FileName, Dimensions);
		} else if (strcmp(ZipCode, (*CurrentNode)->ZipCode) > 0) {
			AddBSTNode(&((*CurrentNode)->right), MovieTheaterName, ZipCode, FileName, Dimensions);
		} else {
			printf("Duplicate Element !! Not Allowed !!!");
		}
	}
}


void InOrder(BNODE *tree_node) {
	if (tree_node != NULL) {
		InOrder(tree_node->left);
		printf("%-32s\t%s\n\n", tree_node->MovieTheaterName, tree_node->ZipCode);
		InOrder(tree_node->right);
	}
}


BNODE *SearchForBNODE(BNODE *R, char ZipCode[])
{

	if(R == NULL || strcmp(ZipCode, R->ZipCode)==0)
	{
		return R;
	}
	else if(strcmp(ZipCode, R->ZipCode)<0)
	{
		return SearchForBNODE(R->left, ZipCode);
	}
	else if(strcmp(ZipCode, R->ZipCode)>0)
	{
		return SearchForBNODE(R->right, ZipCode);
	}
	
	
}
