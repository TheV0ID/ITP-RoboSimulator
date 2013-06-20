#include "Karte.h"

int kartenXLaenge=0;
int kartenYLaenge=0;
int torusRaum=0;
char **karte;

//Sofern ein Zeichen der Karte auf 'Z' gesetzt wird, so wird das letzte Auftreten hier vermerkt.
Position ziel = {-1, -1};

void initialisierung(int anzahlSpalten, int anzahlZeilen) {
	kartenYLaenge=anzahlZeilen;
	kartenXLaenge=anzahlSpalten;

    karte=malloc(sizeof(char*)*kartenXLaenge);
	int i,j;
	for(i=0;i<kartenXLaenge;i++){
 		karte[i]=malloc(sizeof(char)*kartenYLaenge);
 		for(j=0;j<kartenYLaenge;j++){
			karte[i][j]=' ';
		}
	}
}

char getZeichenAnPosition(Position position) {
	return getZeichenAnKoordinaten(position.x, position.y);
}

char getZeichenAnKoordinaten(int x, int y) {
	if(x >= kartenXLaenge || x<0 || y >= kartenYLaenge ||y<0) {
		printf("Position liegt nicht auf der Karte! \\0 zurueck gegeben");
		return 0;
	} else {
		return karte[x][y];
	}
}


int setZeichenAnPosition(char zeichen,Position position) {
	return setZeichenAnKoordinaten(zeichen, position.x, position.y);
}

int setZeichenAnKoordinaten(char zeichen, int x, int y) {
	if(x >= kartenXLaenge || x<0 || y >= kartenYLaenge || y<0) {
		printf("Position liegt nicht auf der Karte! -1 zurueck gegeben");
		return -1;
	} else {
		if(zeichen == 'Z') {
			ziel.x = x;
			ziel.y = y;
		}
		karte[x][y]=zeichen;
		return 0;
	}
}

void setKarte(char **kartenstr, int weite, int hoehe){
    if(kartenXLaenge!=0 && kartenYLaenge!=0){
        if(weite==kartenXLaenge && kartenYLaenge==hoehe){
            int y=0,x=0;
            for(y=0;y<hoehe;++y){
                for(x=0;x<weite;++x){
                    karte[x][y]=kartenstr[y][x];
                }
            }
        }
    }
}


void zeichneKarte()
{
	int i,j;
	Position position;
	system("cls");
	for(i=0;i<kartenYLaenge;i++)
	{
		for(j=0;j<kartenXLaenge;j++)
		{
			position.x=j;
			position.y=i;
			printf("%c",getZeichenAnPosition(position));
		}
		printf("\n");
	}
}

Position getZiel() {
	return ziel;
}
