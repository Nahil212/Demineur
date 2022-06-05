#include "score.h"

// Cette fonction permet de régler le meilleur score dans le fichier texte approprié
void highScore(int diff, char* playerName, int playerScore){
	FILE* score;
	char curName[20];
	int i,curScore;
	
	if (diff=1){
		score = fopen("easyScore.txt", "r+");
	}
	else {
		score = fopen("hardScore.txt", "r+");
	}
	if (score == NULL){
		printf("Ouverture du fichier impossible\n");
		printf("Code d'erreur = %d \n", errno);
		printf("Message d'erreur : %s \n", strerror(errno));exit(1);
	}
	
	fgets(curName,21,score);
	fscanf(score,"%d",&curScore);
	if (playerScore < curScore){
		rewind(score);
		fputs(playerName, score);
		for(i=strlen(playerName);i<20;i++){
			fputc('-',score);
		}
		if (playerScore<1000){
			fputc('0',score);
			if (playerScore<100){
				fputc('0',score);
			}
		}
		fprintf(score,"%d",playerScore);
		printScore(score, playerScore);
	}
	else {
		printScore(score, curScore);
	}
	fclose(score);
}

// Cette fonction permet d'afficher le record enregistré dans les fichiers
void printScore(FILE* fichier, int score){
	char name[20];
	int i;
	char car;
	
	rewind(fichier);
	for(i=0;i<20;i++){
		car=fgetc(fichier);
		if (car!='-'){
			name[i]=car;
		}
	}
	printf("\n**********RECORD**********\n");
	printf("%s: %ds \n", name, score);
}
