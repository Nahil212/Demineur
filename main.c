#include "demineur.h"
#include "score.h"

int main(){
	Case** gameBoard;
	time_t start = time(NULL), end;
	char playerName[50];
	int gameDiff=0, size, action=0, x, lose=0;
	char y;
	
	printf("\n********* DEMINEUR *********\n");
	while (gameDiff!=1 && gameDiff!=2){
		printf("Sélectionnez une difficulté: \n1: Débutant \n2: Intermédiaire\n");
		scanf("%d",&gameDiff);
	}
	gameBoard = createBoard(gameDiff);
	if (gameDiff==1){
		size=9;
	}
	else {
		size=16;
	}
	
	while ((countBomb(gameBoard,size)!=0) && (lose==0)){
		printBoard(gameBoard, size);
		printf("\nIl reste %d bombes à placer \n", countBomb(gameBoard,size));
		
		printf("Voulez vous: \n1: Découvrir une case \n2: Placer/retirer un marqueur de bombe \n");
		scanf("%d",&action);
		while (action!=1 && action!=2){
			printf("Erreur veuillez entrer une action valide \nVoulez vous: \n1: Découvrir une case \n2: Placer/retirer un marqueur de bombe \n");
			scanf("%d",&action);
		}
		
		printf("\nEntrez le numéro de la ligne : ");
		scanf("%d",&x);
		printf("Entrez la lettre de la colonne : ");
		scanf(" %c",&y);
		while (validPos(x-1,charToInt(y),size) != 1){
			printf("\nErreur veuillez entrer des coordonnées valides \nEntrez le numéro de la ligne : ");
			scanf("%d",&x);
			printf("Entrez la lettre de la colonne : ");
			scanf(" %c",&y);
		}
		
		if (action == 1){
			if (gameBoard[x-1][charToInt(y)].bomb == 1){
				printf("Perdu, vous avez déterré une bombe 💣️🤕️ \n");
				lose = 1;
			}
			else{
				discover(gameBoard,x-1,charToInt(y), size);
			}
		}
		else{
			markCase(gameBoard,x-1,charToInt(y));
		}
		action = 0;
	}
	
	if (lose == 0){
		time(&end);
		printf("Gagné, vous avez repéré toutes les bombes 🎉️🤩️ \nVeuillez entrer votre nom: (20 cractères maximum) ");
		scanf("%s", playerName);
		printf("\nTemps de %s : %ld \n", playerName, end-start);
		highScore(gameDiff,playerName,end-start);
	}
}
