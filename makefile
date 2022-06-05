all: game
	
demineur.o: demineur.c demineur.h
	gcc -c demineur.c -o demineur.o
	
score.o: score.c score.h
	gcc -c score.c -o score.o

main.o: main.c demineur.h score.h
	gcc -c main.c -o main.o
	
game: main.o demineur.o score.o
	gcc main.o demineur.o score.o -o game
