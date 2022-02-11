#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int nb;
	int pv;
	int montant;
	int x;
	int x_barre;
	int y_barre;
	int degat
}test;


int main(){
	test t1;
	char mummy[100];
	FILE *level=fopen("level1.txt", "r");
	while(!feof(level)){
		fscanf(level, "%s", mummy);
		printf("%s\n", mummy);
		fscanf(level, "%d/%d/%d/%d/%d/%d/%d", &t1.nb, &t1.pv, &t1.montant, &t1.x, &t1.x_barre, &t1.y_barre, &t1.degat);
		printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n", t1.nb, t1.pv, t1.montant, t1.x, t1.x_barre, t1.y_barre, t1.degat);
	}
	fclose(level);
}
