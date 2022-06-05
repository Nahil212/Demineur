#include "demineur.h"

//This function checks if coordinates do not move out of the table to avoid segmentation errors
int validPos(int i, int j, int size){
	if ( (i>=0 && i<size) && (j>=0 && j<size) ){
		return 1;
	}
	else {
		return 0;
	}
}

//This function initializes the squares, around a square where a bomb has been placed, by adding 1 to bombAround
void initBomb(Case** board, int bombX, int bombY, int size){
	int i,j;

	for (i=bombX-1; i<=bombX+1; i++){
		for (j=bombY-1; j<=bombY+1; j++){
			if (validPos(i,j,size)==1){
				board[i][j].bombAround+=1;
			}
		}
	}
	
}

//This function randomly places a number of bombs on the board
Case** placeBomb(Case** board, int nbBomb, int size){
	int i, bombX, bombY;
	
	srand(time(NULL));
	for (i=0;i<nbBomb;i++){
		bombX = rand()%(size-1);
		bombY = rand()%(size-1);
		while (board[bombX][bombY].bomb == 1){ //Make sure not to place several bombs on the same square
			bombX = rand()%(size-1);
			bombY = rand()%(size-1);
		}
		board[bombX][bombY].bomb = 1;
		initBomb(board,bombX,bombY,size);
	}
	return board;
}

//This function creates the game board with a double pointer on the Case structure
Case** createBoard(int diff){
	Case** board;
	int i;
	
	if(diff == 1){
		board=malloc(9*sizeof(Case*));
		for (i=0;i<9;i++){
			board[i] = malloc(9*sizeof(Case));
			memset(board[i], 0x00, sizeof(Case)); //We initialize all the boxes to zero
		}
		board = placeBomb(board, 10, 9);
	}
	else{
		board=malloc(16*sizeof(Case*));
		for (i=0;i<16;i++){
			board[i] = malloc(16*sizeof(Case));
			memset(board[i], 0x00, sizeof(Case));
		}
		board = placeBomb(board, 40, 16);
	}
	return board;	
}

// This function allows to display the right character according to the state of a given cell
void printCase(Case** board,int i,int j){
	if(board[i][j].marked==1){
		printf("#|");
	}
	else if (board[i][j].hidden==0){
		printf("~|");
	}
	else if (board[i][j].bombAround!=0){
		printf("%d|",board[i][j].bombAround);
	}
	else{
		printf(" |");
	}
}


// This function allows you to browse the game board to display it
void printBoard(Case** board,int size){
	int i,j;
	int letter = 65;
	
	printf("   ");
	for(i=0;i<size;i++){
		printf("%c ",letter);
		letter++;
	}
	printf("\n");
	for(i=0;i<size;i++){
		if (i>8){
			printf("%d|",i+1);
		}
		else{
			printf("%d |",i+1);
		}
		for(j=0;j<size;j++){
			printCase(board,i,j);
		}
		printf("\n");
	}
}

// This function allows you to count the number of bombs that remain to be discovered
int countBomb(Case** board, int size){
	int i,j,nbBomb=0;
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if (board[i][j].bomb==1 && board[i][j].marked==0){
				nbBomb++;
			}
		}
	}
	return nbBomb;
}

// This function converts a letter into a number to be used for the board coordinates
int charToInt(char letter){
	if (letter<97){
		return (letter-65);
	}
	else {
		return (letter-97);
	}
}

// This recursive function allows to discover a cell entered in parameter
void discover(Case** board, int x, int y, int size){
	int i,j;
	
	board[x][y].hidden = 1; //We discover the box
	if (board[x][y].bombAround == 0){ // If there is no bomb around it
		for (i=x-1;i<x+2;i++){ // We go through the boxes around
			for (j=y-1;j<y+2;j++){
				if (validPos(i,j,size) == 1){
					if ( (board[i][j].hidden == 0) && (board[i][j].marked == 0) ){ //If the square is not uncovered or marked
						discover(board,i,j,size); // This program is applied to this box
					}
				}
			}
		}
	}
}

// This function allows to (un)mark a cell passed in parameter according to its state
void markCase(Case** board, int x, int y){
	if (board[x][y].marked == 0){
		printf("Un marqueur a été posé sur la case \n\n");
		board[x][y].marked = 1;
	}
	else{
		printf("Le marqueur a été retiré de la case \n\n");
		board[x][y].marked = 0;
	}
}
