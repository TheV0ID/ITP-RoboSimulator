#include "Karte.h"

int kartenXLaenge=0;
int kartenYLaenge=0;
int zeichneRoboter = 1;
int torusRaum=0;
char **karte;
Parzelle** parzellen;
Parzelle** roboterPositionen; //Enthaelt pointer auf die Parzellen, in denen sich roboter befinden.

int mapRichtungsOffsets[8][2] = { {0,-1}, {1,-1}, {1,0}, {1,+1}, {0,1}, {-1,+1}, {-1,0}, {-1,-1}};

//Sofern ein Zeichen der Karte auf 'Z' gesetzt wird, so wird das letzte Auftreten hier vermerkt.
Position ziel = {-1, -1};

void initialisierung(int anzahlSpalten, int anzahlZeilen) {
	roboterPositionen = malloc(sizeof(Parzelle*)*100); //Lege als Groesse 100 fest, das reicht und schadet nicht.

	kartenYLaenge=anzahlZeilen;
	kartenXLaenge=anzahlSpalten;

    karte=malloc(sizeof(char*)*kartenXLaenge);
    parzellen=malloc(sizeof(Parzelle*)*kartenXLaenge);
	int i,j;
	for(i=0;i<kartenXLaenge;i++){
 		karte[i]=malloc(sizeof(char)*kartenYLaenge);
 		parzellen[i]=malloc(sizeof(Parzelle)*kartenYLaenge);
 		for(j=0;j<kartenYLaenge;j++){
 			Position pos = {i, j};
			Parzelle p = {pos, ' ', -1};
			parzellen[i][j]= p;
		}
	}
}

char getZeichenAnPosition(Position position) {
	return getZeichenAnKoordinaten(position.x, position.y);
}

char getZeichenAnKoordinaten(int x, int y) {
	if(x >= kartenXLaenge || x<0 || y >= kartenYLaenge ||y<0) {
		printf("GetZeichen: Position %ix%i liegt nicht auf der Karte! \\-1 zurueck gegeben", x, y);
		return -1;
	} else {
		return parzellen[x][y].zeichen;
	}
}


int setZeichenAnPosition(char zeichen,Position position) {
	return setZeichenAnKoordinaten(zeichen, position.x, position.y);
}

int setZeichenAnKoordinaten(char zeichen, int x, int y) {
	if(x >= kartenXLaenge || x<0 || y >= kartenYLaenge || y<0) {
		printf("SetZeichen: Position %ix%i liegt nicht auf der Karte! -1 zurueck gegeben", x, y);
		return -1;
	} else {
		if(zeichen == 'Z') {
			ziel.x = x;
			ziel.y = y;
		}
		parzellen[x][y].zeichen = zeichen;
		karte[x][y]=zeichen;
		return 0;
	}
}

void setKarte(char **kartenmat, int weite, int hoehe){
    if(kartenXLaenge!=0 && kartenYLaenge!=0){
        if(weite==kartenXLaenge && kartenYLaenge==hoehe){
            int y=0,x=0;
            for(y=0;y<hoehe;++y){
                for(x=0;x<weite;++x){
                    setZeichenAnKoordinaten(kartenmat[x][y], x, y);
                }
            }
        } else {
			printf("Die angegebenen Werte für Weite und Hoehe passen nicht zur bereits erstellten Karte");
        }
    }
}


void zeichneKarte() {
	system("cls");

	int i,j;
	Position position;

	for(i = 0; i < kartenYLaenge; i++) {
		for(j = 0; j < kartenXLaenge; j++) {
			position.x = j;
			position.y = i;
			char zeichen;
			if(zeichneRoboter && parzellen[j][i].roboterID != -1) {
				zeichen = getRoboterZeichen(parzellen[j][i].roboterID);
			} else {
				zeichen = getZeichenAnPosition(position);
			}
			printf("%c",zeichen);
		}
		printf("\n");
	}
}

Position getZiel() {
	return ziel;
}

void setzeRoboterAufKarte(int roboterID, Position pos) {
	Parzelle* p = roboterPositionen[roboterID];
	p->roboterID = -1;
	//printf("Die Position war: %ix%i\n", p->pos.x, p->pos.y);
	roboterPositionen[roboterID] = &parzellen[pos.x][pos.y];
	parzellen[pos.x][pos.y].roboterID = roboterID;
	//printf("Die Position ist nun: %ix%i", parzellen[pos.x][pos.y].pos.x, parzellen[pos.x][pos.y].pos.y);
}

void aktualisiereParzellen() {
	int x, y;
	for(x = 0; x < kartenXLaenge; x++) {
		for(y = 0; y < kartenYLaenge; y++) {
			parzellen[x][y].zeichen = karte[x][y];
		}
	}
}

Parzelle* getNachbarZelle(Position p, int richtung) {
	int x = p.x+mapRichtungsOffsets[richtung][0];
	int y = p.y+mapRichtungsOffsets[richtung][1];
	if(x < 0 || x >= kartenXLaenge) {
		if(torusRaum) {
			x = x < 0 ? kartenXLaenge-1 : 0;
		} else {
			x = -1;
		}
	}
	if(y < 0 || y >= kartenYLaenge) {
		if(torusRaum) {
			y = y < 0 ? kartenYLaenge-1 : 0;
		} else {
			y = -1;
		}
	}
	if(p.x < 0 || p.y < 0) {
		return NULL;
	}
	return &parzellen[x][y];
}
