#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Algorithmen.h"
#include "Roboter.h"

//Variablen für Befehle aus einer Datei
FILE * datei;
int sprungmarke = -1;
int aktuelleZeile = -1;

//Wenn die Befehlsdatei noch nicht geladen wurde, soll dies hier geschehen.
void initialisiere(char pfad[]) {
	if(datei == NULL) {
		datei = fopen(pfad, "r");
		if(datei == NULL) {
			printf("\n\nDie Datei %s konnte nicht geöffnet werden.\n\n");
		}
	}
}

//Das rand muss der Form rand(x,y) entsprechen und darf nur einstellige Zahlen enthalten.
int werteRandAus(char befehl[]) {
	int lower = 0;
	int upper = 1;
	if(strncmp("rand(", befehl, 5) == 0) {
		if('0' <= befehl[5] && befehl[5] <= '9') {
			lower = befehl[5]-'0';
		}
		if('0' <= befehl[7] && befehl[7] <= '9') {
			upper = befehl[7]-'0';
		}
	}
	if(upper-lower > 0) {
		return rand()%(upper-lower+1)+lower;
	} else {
		return lower;
	}
}

/*Wertet einen Befehl aus. Möglich bisher:
Loop:
vor(); Ohne/mit einer Zahl und einem Aufruf von rand(x,y)
drehe(); Ohne/mit einer Zahl und einem Aufruf von rand(x,y)

Beispiel:
	vor(rand(2,3));
	vor(5);
	vor();

Gibt 1 zurück, wenn ein sinnvoller Befehl gefunden wurde, 0 bei Kommentaren, nicht-Befehlen
und Befehlen die keine direkte Auswirkung haben (wie etwa Loop:)
*/
int werteAus(char befehl[]) {
	char * arg;
	if(befehl[0] == '#') {
		return 0;
	}
	if(strncmp("Loop:", befehl, 5) == 0) {
		sprungmarke = aktuelleZeile+1;
		return 0;
	} else if(strncmp("vor(", befehl, 4) == 0) {
		arg = &befehl[4];
		if(')'==arg[0]) {
			motorLinksUndRechtsAn(1);
		} else if('0' <= arg[0] && arg[0] <= '9') {
			motorLinksUndRechtsAn(arg[0]-'0');
		} else {
			motorLinksUndRechtsAn(werteRandAus(arg));
		}
		return 1;
	} else if(strncmp("drehe(", befehl, 6) == 0) {
		arg = &befehl[6];
		if(')'==arg[0]) {
			motorLinksAn(1);
		} else if('0' <= arg[0] && arg[0] <= '9') {
			motorLinksAn(arg[0]-'0');
		} else {
			motorLinksAn(werteRandAus(arg));
		}
		return 1;
	}
	return 0;
}

//Liest die Befehle für den Roboter aus einer Datei
void ausDatei(char* pfad, int* programmLaeuft) {
	initialisiere(pfad);
	char zeile[100];
	int sinnvollerBefehlGefunden = 0;
	while(sinnvollerBefehlGefunden == 0) {
		if(fgets(zeile, 100, datei) != NULL) { //Die Datei ist noch nicht zuende
			aktuelleZeile++;
			sinnvollerBefehlGefunden = werteAus(zeile);
			if(sinnvollerBefehlGefunden) {
				printf("%s\n", zeile);
			}
		} else if(sprungmarke != -1) { //Dateiende erreicht und es existiert eine Sprungmarke
			rewind(datei);
			int i = 0;
			while(i++ < sprungmarke && fgets(zeile, 100, datei));
		} else { //Dateiende erreicht, ohne dass jemals eine Sprungmarke aufgetreten ist.
			*programmLaeuft = 0;
			sinnvollerBefehlGefunden = 1;
		}
	}
}
