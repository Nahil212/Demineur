#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
	int marked;
	int hidden;
	int bombAround;
	int bomb;
}Case;

Case** placeBomb(Case** board, int nbBomb, int size);
Case** createBoard(int diff);

int validPos(int i, int j, int size);
int countBomb(Case** board, int size);
int charToInt(char letter);

void discover(Case** board, int x, int y, int size);
void initBomb(Case** board, int bombX, int bombY, int size);
void printCase(Case** board,int i,int j);
void printBoard(Case** board, int size);
void markCase(Case** board, int x, int y);
