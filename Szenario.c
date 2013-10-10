#include<time.h>
#include "Szenario.h"
#include<string.h>


int szenarioNummer=1;
//Speichert welche Zeichen relevant sind, zB zum Einsammeln
char* relevanteZeichen;
char* DatenbankDateiPfad;
int laengeRelevanteZeichen = 0;
int ohneRoboter = 0;
//
void ladeSzenario(int szenario){
    szenarioNummer=szenario;
    srand(7);
	switch(szenario) {
		case 1: szenario1(); break;
		case 2: szenario2(); break;
		case 3: szenario3(); break;
		case 4: szenario4(); break;
		case 5: szenario5(); break;
		case 6: szenario6(); break;
		case 7: szenario7(); break;
		case 8: szenario8(); break;
		case 9: szenario9(); break;
	}
}



int istZielErreicht(){

	switch(szenarioNummer) {
		case 2: return getAnzahlGesammelterGegenstaende() == laengeRelevanteZeichen;
            break;
		case 6: {
                    if(getZeichenAnRoboterPosition() == 'Z'){
                        Position ziel3 = {1, 1 };
                        ziel = ziel3;
                    }
                    Position ziel = getZiel();
		            return getRoboterPosition().x == ziel.x && getRoboterPosition().y == ziel.y;
                }
                break;
		default:{
                    Position ziel = getZiel();
		            return getRoboterPosition().x == ziel.x && getRoboterPosition().y == ziel.y;
                    break;
                }
	}


}

void nachDurchlauf() {
	if(szenarioNummer==4){
        //printf("foo bar \n");
    }
}

int istZeichenRelevant(char zeichen) {
	if(szenarioNummer==2) {
		return enthaelt(relevanteZeichen, laengeRelevanteZeichen, zeichen);
	}
	return 0;
}

/*
Grundlegendes Szenario. Der Roboter muss vom Start zum Ziel finden. Durch konstanten Seed immer gleich aufgebaut.
*/
void szenario1(){
    initialisierung(20,20);
	srand(2);
	int i, j;
	int wahrscheinlichkeit=10;

	for (i=0;i<kartenXLaenge;i++){
		for (j=0;j<kartenYLaenge;j++){
			if(rand()%100 < wahrscheinlichkeit) {
				karte[i][j]='#';
			}
			else {
				karte[i][j]=' ';
			}
		}
	}
	aktualisiereParzellen();
	Position position = {0, 0};
	initialisiereRoboter(position, 2);
	setZeichenAnKoordinaten('S', 0, 0);
	setZeichenAnKoordinaten('Z', 15, 15);
}

/*
* Sammler: Der Roboter muss eine gewisse Menge an Beute sammeln. Erst wenn er x%/alles gefunden hat, ist das Ziel erreicht.
*/
void szenario2(){
    initialisierung(20,20);
	srand(2);
	int i, j;
	int wahrscheinlichkeit=10;

	for (i=0;i<kartenXLaenge;i++){
		for (j=0;j<kartenYLaenge;j++){
			if(rand()%100 < wahrscheinlichkeit) {
				karte[i][j]='#';
			}
			else {
				karte[i][j]=' ' ;
			}
		}
	}
	aktualisiereParzellen();
	Position position = {0, 0 };
	initialisiereRoboter(position, 2);
	setZeichenAnKoordinaten('S', 0, 0);
	setZeichenAnKoordinaten('A', 3, 0);
	setZeichenAnKoordinaten('B', 5, 1);
	laengeRelevanteZeichen = 2;
	relevanteZeichen = malloc(laengeRelevanteZeichen * sizeof(char));
	relevanteZeichen[0] = 'A';
	relevanteZeichen[1] = 'B';
}

void szenario3(){
    int i,spalten=9,zeilen=9;
    initialisierung(spalten,zeilen);
    char **arr;
    arr=(char**)malloc(spalten*sizeof(char *));
    for(i=0;i<=spalten;i++)
        arr[i]=(char *)malloc(zeilen*sizeof(char));
          //0123456789012345678901234567890123456789
    arr[0]="#########";
    arr[1]="# #   #Z#";
    arr[2]="# ### # #";
    arr[3]="#     # #";
    arr[4]="##### # #";
    arr[5]="#     # #";
    arr[6]="# ##### #";
    arr[7]="#       #";
    arr[8]="#########";
    setKarte(arr,spalten,zeilen);

    setZeichenAnKoordinaten('S', 1, 1);

    Position position = {1, 1 };
	initialisiereRoboter(position, 2);
    setZeichenAnPosition(2,position);
    Position ziel3 = {7, 1 };
    ziel = ziel3;
}
void szenario4(){
    DatenbankDateiPfad = malloc(250*sizeof(char));
    strcpy(DatenbankDateiPfad,".\\tmp\\EntscheidungsDatenbank.csv");
    //Sollte die Datei nicht vorhanden sein, lege sie mit einer passenden Kopfzeile an
    FILE* datei = fopen(DatenbankDateiPfad, "r");
    if(datei == NULL){
            datei=fopen(DatenbankDateiPfad, "w");
            fprintf(datei, "X; Y; Inhalt ;\n");
    }
    fclose(datei);
    free(datei);


    int i,spalten=40,zeilen=20;
    initialisierung(spalten,zeilen);
    char **arr;
    arr=(char**)malloc(spalten*sizeof(char *));
    for(i=0;i<spalten;i++){
        arr[i]=malloc(zeilen*sizeof(char));
    }

           //0123456789012345678901234567890123456789
    arr[0] ="########################################";
    arr[1] ="#S#   #       #       #   ###        #Z#";
    arr[2] ="# ### # ##### # ##### # # #   #### # # #";
    arr[3] ="# # # #   #     # # # # #   ###  ###   #";
    arr[4] ="# #     # ####### #     #       #   ###";
    arr[5] ="# #######         ##### ######## ##### #";
    arr[6] ="#      # ######       #                #";
    arr[7] ="###### #    # ####### ##################";
    arr[8] ="#      ## # #                          #";
    arr[9] ="# ####    # #########################  #";
    arr[10]="# #  ### ##    #   #      #            #";
    arr[11]="# # ##    #### # # ## # #### ###########";
    arr[12]="#    #  #    #   #    #    # #         #";
    arr[13]="#### ##### # # ###### ######   # ##### #";
    arr[14]="# #  #     # #      #      # ### #     #";
    arr[15]="# # ############### #  ####### # # #####";
    arr[16]="# #                 #            #     #";
    arr[17]="# ###################################  #";
    arr[18]="#                                      #";
    arr[19]="########################################";

    setKarte(arr,spalten,zeilen);

    setZeichenAnKoordinaten('S', 1, 1);

    Position position = {1, 1 };
	initialisiereRoboter(position, 2);

    Position ziel3 = {38, 1 };
    ziel = ziel3;
}
void szenario5(){
    int i,spalten=40,zeilen=20;
    initialisierung(spalten,zeilen);
    char **arr;
    arr=(char**)malloc(spalten*sizeof(char *));
    for(i=0;i<spalten;i++){
        arr[i]=malloc(zeilen*sizeof(char));
    }

           //0123456789012345678901234567890123456789
    arr[0] ="########################################";
    arr[1] ="# ... ....                             #";
    arr[2] ="#   . .  .                             #";
    arr[3] ="#   . .. .                  ....Z      #";
    arr[4] ="#   .  . .                  .          #";
    arr[5] ="#   .... .....           ....          #";
    arr[6] ="#            .           .             #";
    arr[7] ="#            .   .........             #";
    arr[8] ="#.............   .                     #";
    arr[9] ="#.               .                     #";
    arr[10]="#.               .    ...........      #";
    arr[11]="#.     ...........    .         .      #";
    arr[12]="#.     .              ....      .      #";
    arr[13]="#.     .                 .      .      #";
    arr[14]="#.     .                 .      .      #";
    arr[15]="#.     ...................      .      #";
    arr[16]="#.                              .      #";
    arr[17]="#................................      #";
    arr[18]="#                                      #";
    arr[19]="########################################";

    setKarte(arr,spalten,zeilen);
    aktualisiereParzellen();

    setZeichenAnKoordinaten('S', 1, 1);

    Position position = {1, 1 };
	initialisiereRoboter(position, 2);

    Position ziel3 = {32, 3 };
    ziel = ziel3;
}
void szenario6(){
    int i,spalten=9,zeilen=9;
    initialisierung(spalten,zeilen);
    char **arr;
    arr=(char**)malloc(spalten*sizeof(char *));
    for(i=0;i<=spalten;i++)
        arr[i]=(char *)malloc(zeilen*sizeof(char));
          //0123456789012345678901234567890123456789
    arr[0]="#########";
    arr[1]="# #   #Z#";
    arr[2]="# ### # #";
    arr[3]="#     # #";
    arr[4]="##### # #";
    arr[5]="#     # #";
    arr[6]="# ##### #";
    arr[7]="#       #";
    arr[8]="#########";
    setKarte(arr,spalten,zeilen);

    setZeichenAnKoordinaten('S', 1, 1);

    Position position = {1, 1 };
	initialisiereRoboter(position, 2);
    setZeichenAnPosition(2,position);
    Position ziel3 = {0, 0 };
    ziel = ziel3;
}
//Zwei Roboter Test
void szenario7(){
    initialisierung(20,20);
	srand(2);
	int i, j;
	int wahrscheinlichkeit=10;

	for (i=0;i<kartenXLaenge;i++){
		for (j=0;j<kartenYLaenge;j++){
			if(rand()%100 < wahrscheinlichkeit) {
				karte[i][j]='#';
			}
			else {
				karte[i][j]=' ';
			}
		}
	}
	aktualisiereParzellen();
	Position position = {0, 0};
	anzahlRoboter = 2;
	initialisiereRoboter(position, 2);
	Position neuePosition = {2, 2};
	char* aussehensarray[8] = {'t','t','t','t','t','t','t','t'};
	char* unpassierbare[1];
	unpassierbare[0] = '_';
	erzeugeNeuenRoboter(1, neuePosition, 2, aussehensarray, 'z', 0, unpassierbare, 1);
	setZeichenAnKoordinaten('S', 0, 0);
	setZeichenAnKoordinaten('Z', 15, 15);
}


void szenario8(){
	ohneRoboter = 1;
	zeichneRoboter = 0;
	initialisierung(20,20);
	srand(2);
	int i, j;
	int wahrscheinlichkeit=10;

	for (i=0;i<kartenXLaenge;i++){
		for (j=0;j<kartenYLaenge;j++){
			if(rand()%100 < wahrscheinlichkeit) {
				karte[i][j]='#';
			}
			else {
				karte[i][j]=' ';
			}
		}
	}
	aktualisiereParzellen();
	Position p = {0, 0};
	initialisiereRoboter(p, 2);
}
void szenario9(){}
