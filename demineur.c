#include "demineur.h"

//Cette fonction vérifie si des coordonnées ne dépacent pas du tableau pour éviter les erreurs de segmentation
int validPos(int i, int j, int size){
	if ( (i>=0 && i<size) && (j>=0 && j<size) ){
		return 1;
	}
	else {
		return 0;
	}
}

//Cette fonction initialise les cases, autour d'un case où une bombe a été placée, en ajoutant 1 à bombAround
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

//Cette fonction place aléatoirement un certain nombre de bombe sur le plateau
Case** placeBomb(Case** board, int nbBomb, int size){
	int i, bombX, bombY;
	
	srand(time(NULL));
	for (i=0;i<nbBomb;i++){
		bombX = rand()%(size-1);
		bombY = rand()%(size-1);
		while (board[bombX][bombY].bomb == 1){ //On s'assure de ne pas placer plusieurs bombes sur une même case
			bombX = rand()%(size-1);
			bombY = rand()%(size-1);
		}
		board[bombX][bombY].bomb = 1;
		initBomb(board,bombX,bombY,size);
	}
	return board;
}

//Cette fonction permet de créer le plateau de jeu avec un pointeur double sur la structure Case
Case** createBoard(int diff){
	Case** board;
	int i;
	
	if(diff == 1){
		board=malloc(9*sizeof(Case*));
		for (i=0;i<9;i++){
			board[i] = malloc(9*sizeof(Case));
			memset(board[i], 0x00, sizeof(Case)); //On initialise toutes les Cases à zéro
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

// Cette fonction permet d'afficher le bon caractère en fonction de l'état d'une case donnée
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


// Cete fonction permet de parcourir le plateau de jeu pour l'afficher
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

// Cette fonction permet de compter le nombre de bombe qu'il reste à découvrir
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

// Cette fonction permet de convertir une lettre en nombre afin de l'utiliser pour les coordonnées du plateau
int charToInt(char letter){
	if (letter<97){
		return (letter-65);
	}
	else {
		return (letter-97);
	}
}

// Cette fonction récursive permet de découvrir une case entrée en paramètre
void discover(Case** board, int x, int y, int size){
	int i,j;
	
	board[x][y].hidden = 1; //On découvre la case
	if (board[x][y].bombAround == 0){ // S'il n'y a pas de bombe autour de celle-ci
		for (i=x-1;i<x+2;i++){ // On parcourt les cases autour
			for (j=y-1;j<y+2;j++){
				if (validPos(i,j,size) == 1){
					if ( (board[i][j].hidden == 0) && (board[i][j].marked == 0) ){ // Si la case n'est ni découverte ni marquée
						discover(board,i,j,size); // On applique ce programme à cette case
					}
				}
			}
		}
	}
}

// Cette fonction permet de (dé)marquer une case passée en paramètre en fonction de son état
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
