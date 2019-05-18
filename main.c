
// Jakub Grzegorczyk

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "QueueLib.h"
#include "BSTLib.h"
#include "StackLib.h"
#include "ListLib.h"



void changeUserInput(char SeatMap[][26], char seatNumber[], int *row, int *col) {
	int i = 0;

	*row = (int)seatNumber[0]-65;
	*col = atoi(seatNumber + 1);
}

void get_command_line_parameter(char *argv[], char ParamName[], char ParamValue[]) {
	int i= 0;
	
	while (argv[++i] != NULL) {
		if (!strncmp(argv[i], ParamName, strlen(ParamName))) {
			strcpy(ParamValue, strchr(argv[i], '=') + 1);
		}
	}
	return;
}

void printTheaterSeatMap(char TheaterSeatMap[][26], int row, int col) {
	
	int c;
	for (c = 0; c < col; c++) {
		printf("\tSeat%d",c+1);
	}
	printf("\n\n");
	int i = 0;
	for (i = 0; i < row; i++) {
		int j = 0;
		printf("Row %c\t",65+i);
		for (j = 0; j < col; j++) {
			printf("%c\t",TheaterSeatMap[i][j]);
		}
		printf("\n\n");
	}
	
}


void wrtieSeatMap(FILE *OuputFile, char UpdatedSeatMap[][26], int row, int col) {
	
	int i = 0;
	
	for (i = 0; i < row; i++) {
		int j = 0;
		for (j = 0; j < col; j++) {
			fprintf(OuputFile, "%c", UpdatedSeatMap[i][j]);
		}
	}
}


void strToUpper(char string[]) {
	int i = 0;
	for (i = 0; i < strlen(string); i++) {
		string[i] = toupper(string[i]);
	}
}


int seatCheck1(int row, int col, char seatMap[][26]) {
	if (seatMap[row][col-1] == 'X') {
		return 1;
	} else {
		return 0;
	}
}

int main(int argc, char *argv[]) {
	
	QNODE *QueueHead = NULL;
	QNODE *QueueTail = NULL;
	char CustomerName[30];
	FILE *QueueFile;
	char arg_value[10];
	char que[10] = "QUEUE=";
	char QueueFileName[10];
	char ReceiptNumberFromCommandLine[10];
	FILE *ZipFile;
	char arg_value_1[10];
	char zip[10] = "ZIPFILE=";
	char ZipFileName[10];
	SNODE *StackTop = NULL;
	FILE *SeatMapInputFile;
	FILE *SeatMapOuputFile;
	char SeatMapFileName[10];
	char recipNumber[20] = "RECEIPTNUMBER=";
	char MovieTheaterName[40];
    char ZipCode[6];
    char FileName[100];
    char Dimensions[6];
	char *Token;
	char line[100];
	int choice = 1;
	char zipCodeChoice[6] = {};
	char dimensions[6] = {};
	char TheaterSeatMap[20][26];
	int row;
	int col;
	int userChosenRow;
	int userChosenCol;
	BNODE *BSTNode = NULL;
	int QCheck = 0;
	char x[2] = "x";
	
	get_command_line_parameter(argv, recipNumber, ReceiptNumberFromCommandLine);
	get_command_line_parameter(argv, zip, arg_value_1);
	strcpy(ZipFileName, arg_value_1);
	ZipFile = fopen(ZipFileName, "r");
	get_command_line_parameter(argv, que, arg_value);
	strcpy(QueueFileName, arg_value);
	QueueFile = fopen(QueueFileName, "r");
	
	
	if (QueueFile == NULL) {
		printf("The queue file is empty.\n");
		exit(0);
	}
	
	while (fgets(CustomerName, 30, QueueFile)!= NULL) {
		
		if (ferror(QueueFile)) {
			printf("Error reading queue file\n");
			exit(0);
		} else {
			
			CustomerName[strlen(CustomerName)-2] = '\0';
			enQueue(CustomerName, &QueueHead, &QueueTail);
		}
	}
	
	fclose(QueueFile);	
	if (ZipFile == NULL) {
		printf("The queue file is empty.\n");
		exit(0);
	}
	int TicketNumber = atoi(ReceiptNumberFromCommandLine);
	while(fgets(line, 100, ZipFile) != NULL) {
		
		if (ferror(ZipFile)) {
			printf("Error reading zip file\n");
			exit(0);
		} else {
			Token = strtok(line, "|");
			strcpy(MovieTheaterName, Token);
			Token = strtok(NULL, "|");
			strcpy(ZipCode, Token);
			Token = strtok(NULL, "|");
			strcpy(FileName, Token);
			Token = strtok(NULL, "\n");
			strcpy(Dimensions, Token);
			AddBSTNode(&BSTNode, MovieTheaterName, ZipCode, FileName, Dimensions);
		
		}
	}
	
	fclose(ZipFile);

	printf("\n1.\tSell tickets to next customer\n\n");
	printf("2.\tSee who's in line\n\n");
	printf("3.\tSee the seat map for a given theater\n\n");
	printf("4.\tPrint today's receipts\n\n");
	printf("Choice: ");
	scanf("%d", &choice); 
	printf("\n\n");
	
	while(QueueHead != NULL || QCheck != 1) {
		
		if (choice >= 1 && choice <= 4) {
		
			if (choice == 1) {
				LNODE *LinkedListHead = NULL;
				printf("Hello %s\n\nPick a theater by entering the zipcode\n\n", QueueHead->Name);
				InOrder(BSTNode);
				printf("Enter zip ");
				scanf("%s", zipCodeChoice);
				printf("\n");
				BNODE *FoundZipCode = SearchForBNODE(BSTNode, zipCodeChoice);
				
				if (FoundZipCode != NULL) {
				
					strcpy(dimensions, FoundZipCode->Dimensions);
					char *tokenDimension = strtok(dimensions, x);
					row = atoi(tokenDimension);
					tokenDimension = strtok(NULL, x);
					col = atoi(tokenDimension);
					strcpy(SeatMapFileName, FoundZipCode->FileName);
					SeatMapInputFile = fopen(SeatMapFileName, "r");
					
					
					if (SeatMapInputFile == NULL) {
						printf("The map doesnt exist!\n");
					} else {
					
						char freeSeats[521] = {};
						
						fgets(freeSeats, 521, SeatMapInputFile);
						
						fclose(SeatMapInputFile);
						
						if (strlen(freeSeats) == row*col) {
						
							
							int i = 0;
							int ShiftSeat = 0;
							for (i = 0; i < row; i++) {
								int j = 0;
								for (j = 0; j < col; j++) {
									TheaterSeatMap[i][j] = freeSeats[j+ShiftSeat];
								}
								ShiftSeat += j;
							}
							
							int counting = 0;
							int checking = 0;
							int TicketNumber;
							printTheaterSeatMap(TheaterSeatMap, row, col);

							printf("How many movie tickets do you want to buy? "); // asking user for unput
							scanf("%d",&TicketNumber);
							
							while (counting < TicketNumber) {
												
								char seatNumber[4];
								int seatCheck = 0;
								printf("\nPick a seat: ");
								scanf("%s", seatNumber);
								printf("\n");
								strToUpper(seatNumber);
								changeUserInput(TheaterSeatMap, seatNumber, &userChosenRow, &userChosenCol);
								checking = seatCheck1(userChosenRow, userChosenCol, TheaterSeatMap);
								while (seatCheck != 1) {
									if (userChosenRow <= row && userChosenCol <= col && checking == 0) {
										TheaterSeatMap[userChosenRow][userChosenCol-1] = 'X';
										seatCheck++;
										counting++;
										InsertNode(&LinkedListHead, seatNumber);
									} else if (userChosenRow >= row || userChosenCol >= col) {
										printTheaterSeatMap(TheaterSeatMap, row, col);
										printf("\nPick another seat:  ");
										scanf("%s",seatNumber);
										printf("\n");
										strToUpper(seatNumber);
										changeUserInput(TheaterSeatMap, seatNumber, &userChosenRow, &userChosenCol);
										checking = seatCheck1(userChosenRow, userChosenCol, TheaterSeatMap);
									
									} else if (checking == 1) {
										printTheaterSeatMap(TheaterSeatMap, row, col);
										printf("\nThis sit is taken, chose another one");
										scanf("%s",seatNumber);
										printf("\n");
										strToUpper(seatNumber);
										changeUserInput(TheaterSeatMap, seatNumber, &userChosenRow, &userChosenCol);
										checking = seatCheck1(userChosenRow, userChosenCol, TheaterSeatMap);
									}
								}
								printTheaterSeatMap(TheaterSeatMap, row, col);
							}
							push(&StackTop, LinkedListHead, TicketNumber, FoundZipCode->MovieTheaterName);
							TicketNumber++;
							SeatMapOuputFile = fopen(SeatMapFileName, "w");
							wrtieSeatMap(SeatMapOuputFile, TheaterSeatMap, row, col);
							fclose(SeatMapOuputFile);
							printf("Thank you %s - enjoy your movie!\n", QueueHead->Name);
							deQueue(&QueueHead);
						} else {
							printf("Select another theater! ");
						}
					}
				
				} else {
					printf("\nWrong zipCode! \n");
				}
				
			} else if (choice == 2) {
				printf("Customer Queue\n\n\n");
				DisplayQueue(QueueHead);
			} else if (choice == 3) {
				InOrder(BSTNode);
				printf("Enter zip ");
				scanf("%s", zipCodeChoice);
				printf("\n");
				BNODE *FoundZipCode = SearchForBNODE(BSTNode, zipCodeChoice); // returning seaching for node
				if (FoundZipCode != NULL) {
					strcpy(dimensions, FoundZipCode->Dimensions);
					char *tokenDimension = strtok(dimensions, x);
					row = atoi(tokenDimension);
					tokenDimension = strtok(NULL, x);
					col = atoi(tokenDimension);
					strcpy(SeatMapFileName, FoundZipCode->FileName); // coping filename
					SeatMapInputFile = fopen(SeatMapFileName, "r");
					char freeSeats[521] = {};
					fgets(freeSeats, 521, SeatMapInputFile);
					fclose(SeatMapInputFile);
					if (strlen(freeSeats) == row*col) {
						int i = 0;
						int ShiftSeat = 0;
						for (i = 0; i < row; i++) {
							int j = 0;
							for (j = 0; j < col; j++) {
								TheaterSeatMap[i][j] = freeSeats[j+ShiftSeat];
							}
							ShiftSeat += j;
						}
						
						printTheaterSeatMap(TheaterSeatMap, row, col);
						
					} else {
						printf("Pick another theater\n");
					}
				
				} else {
					printf("\nInvalid zipcode! Please reenter.\n");
				}
			} else if (choice == 4) {
				
				if (QueueHead == NULL) {
					QCheck++;
					printf("\nGood job - you sold tickets to all of the customers in line.\n\n"); // displaying
				}
				char ticketHL[4];
				if (StackTop == NULL) {
					printf("Today's receipts have already been displayed!\n");
				} else {
					printf("Today's receipts\n\n");
					while (StackTop != NULL) {
						printf("Receipt #%d\n\n\t%s\n\n", StackTop->ReceiptNumber, StackTop->MovieTheaterName);
						while (StackTop->TicketList != NULL) {
								ReturnAndFreeLinkedListNode(&StackTop->TicketList, ticketHL);
								printf("\t%s", ticketHL);
								strcpy(ticketHL, "");
						}
						printf("\n\n");
						pop(&StackTop);
					}
				}
			}
			if (QueueHead != NULL) { // checking quehead 
			
				printf("\n1.\tSell tickets to next customer\n\n"
					   "2.\tSee whos in line\n\n"
					   "3.\tSee the seat map for a given theater\n\n"
					   "4.\tPrint today's receipts\n\n"
					   "Choice: ");
				scanf("%d", &choice); 
				printf("\n\n");
			
			} else {
				
				choice = 4;
			}
			
		} else {
			printf("Invalid input. Please reenter!\n\n1.\tSell tickets to next customer\n\n"
				   "2.\tSee whos in line\n\n"
				   "3.\tSee the seat map for a given theater\n\n"
				   "4.\tPrint today's receipts\n\n"
			       "Choice: ");
			scanf("%d", &choice); 
			printf("\n\n");
		}
	}
	return 0;
}
