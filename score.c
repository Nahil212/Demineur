#include "score.h"

// This function allows the best score to be set in the appropriate text file
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
		for(i=strlen(playerName);i<20;i++){ // We set the player's name to a length of 20 by completing it with "-", it simplifies the score reading
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

// This function displays the record recorded in the files
void printScore(FILE* fichier, int score){
	char name[20];
	int i;
	char car;
	
	rewind(fichier);
	for(i=0;i<20;i++){
		car=fgetc(fichier);
		if (car!='-'){
			name[i]=car; // We take the player's name by removing the "-"
		}
	}
	printf("\n**********RECORD**********\n");
	printf("%s: %ds \n", name, score);
}
