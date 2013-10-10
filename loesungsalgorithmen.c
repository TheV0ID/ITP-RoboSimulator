#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "loesungsalgorithmen.h"
#include "Szenario.h"

void runSzenario3OURL(){
    if(getSchrittZaehler()<2)U(1);
    else if(getSchrittZaehler()>=2&&getSchrittZaehler()<6)R(1);
    else if(getSchrittZaehler()>=6&&getSchrittZaehler()<8)U(1);
    else if(getSchrittZaehler()>=8&&getSchrittZaehler()<12)L(1);
    else if(getSchrittZaehler()>=12&&getSchrittZaehler()<14)U(1);
    else if(getSchrittZaehler()>=14&&getSchrittZaehler()<20)R(1);
    else if(getSchrittZaehler()>=20)O(1);

	printf("schritte = %i\n",getSchrittZaehler());
	printf("%i", getBlickrichtung());
}

void runSzenario5dotfinder(){
    if(getFrontZeichen()=='.'||getFrontZeichen()=='Z'){
        geheNachVorn(1);
        setZeichenAnPosition(' ', getRoboterPosition());
    }else{
        drehen(45,1);
    }
}

void runSzenario4rightTurn(){
    if(getFrontZeichen()=='#'){
        drehe();
    }
    if(getFrontZeichen()=='#'){
        drehe();
        drehe();
    }
    if(getFrontZeichen()=='#'){
        drehe();
        drehe();
        drehe();
    }
    geheNachVorn(1);
}

void runSzenario3Karteerstellen(){
    int zellencode;
    int zeichen;
    int posZeichen=holeSpeicherstand2d(getRoboterPosition().x,getRoboterPosition().y);
    int problem=0;

    if(!posZeichen){
        //rundumblick bestimmen
        int a=getBlickrichtung();
        setBlickrichtung(0);
        zellencode=0;

        if(frontSensor())zellencode+=1;
        if(rechterSensor())zellencode+=10;
        if(heckSensor())zellencode+=100;
        if(linkerSensor())zellencode+=1000;
        setBlickrichtung(a);
        //
        switch(zellencode){
            // ein ausgang
            case 1:zeichen=219;break;
            case 10:zeichen=219;break;
            case 100:zeichen=219;break;
            case 1000:zeichen=219;break;
            //zwei ausgänge
            //gegenüber
            case 101:zeichen=186;break;
            case 1010:zeichen=205;break;
            //nicht gegenüber
            case 11:zeichen=200;break;
            case 1001:zeichen=188;break;
            case 110:zeichen=201;break;
            case 1100:zeichen=187;break;
            // drei ausgänge
            case 111:zeichen=204;break;
            case 1101:zeichen=185;break;
            case 1011:zeichen=202;break;
            case 1110:zeichen=203;break;
            // vier ausgänge
            case 1111:zeichen=206;break;
            default:zeichen=0;problem=1;
        }
        if(!problem)setzeSpeicherstand2d(zeichen,getRoboterPosition().x,getRoboterPosition().y);

    }
    gebe2dSpeicherAus();
    if(!problem){
/*
        //bewegen wenn in gespeicherter karte nichts in einem der nachbar felder steht gehe in das nachbarfeld wenn da etwes steht drehe algorithmus bis wieder ein freies feld gefünden wird
        int oben = holeSpeicherstand2d(roboterPosition.x,roboterPosition.y+1);
        int unten = holeSpeicherstand2d(roboterPosition.x,roboterPosition.y-1);
        int rechts = holeSpeicherstand2d(roboterPosition.x+1,roboterPosition.y);
        int links = holeSpeicherstand2d(roboterPosition.x-1,roboterPosition.y);

        if(!oben && getZeichenAnKoordinaten(roboterPosition.x,roboterPosition.y+1)!='#'){
            printf("O");
            O(1);
            setBlickrichtung(0);
        }else if(!rechts && getZeichenAnKoordinaten(roboterPosition.x+1,roboterPosition.y)!='#'){
            printf("R");
            R(1);
            setBlickrichtung(2);
        }else if(!unten && getZeichenAnKoordinaten(roboterPosition.x,roboterPosition.y-1)!='#'){
            printf("U");
         U(1);
            setBlickrichtung(4);
        }else if(!links && getZeichenAnKoordinaten(roboterPosition.x-1,roboterPosition.y)!='#'){
            printf("L");
            L(1);
            setBlickrichtung(6);
        }
        if(!frontSensor()){
            drehe();    gebe2dSpeicherAus();
        }
        if(!frontSensor()){
            drehe();
            drehe();gebe2dSpeicherAus();
        }
        if(!frontSensor()){
            drehe();
            drehe();
            drehe();    gebe2dSpeicherAus();
        }
        geheNachVorn(1);
*/
    }
    printf("%i\n",posZeichen);
    printf("zellencode:%i\t%c \nfront:%i \nrechts:%i \nheck:%i \nlinks:%i \n",zellencode,zeichen,frontSensor(),rechterSensor(),heckSensor(),linkerSensor());
}

void runSzenario3quickReturn(){
    int *a=hole1dSpeicherArray();
    if(getZeichenAnPosition(getRoboterPosition())=='Z'){
        a[0]=getSchrittZaehler();
    }
    if(a[0]==0){
        if(getFrontZeichen()=='#'){
            drehe();
        }
        if(getFrontZeichen()=='#'){
            drehe();
            drehe();
        }
        if(getFrontZeichen()=='#'){
            drehe();
            drehe();
            drehe();
        }
        a[1+getSchrittZaehler()]=getBlickrichtung();
        geheNachVorn(1);
    }else{
    	//TODO MEGA SCHEI?E!
        if(getBlickrichtung()==0)geheNachVorn(1);
        if(getBlickrichtung()==2)
        if(getBlickrichtung()==4)
        if(getBlickrichtung()==6)
        a[0]--;
    }
}

void runSzenario4files(){
    int feld,
        norden,
        osten,
        sueden,
        westen,
        richtungNaechstesFeld;

    char* datenbank = DatenbankDateiPfad;
    char* feldString = malloc(sizeof(char)*250);
    char* frontFeld = malloc(sizeof(char)*250);

    holeInhaltAusDatei(feldString, 250, getRoboterPosition().x, getRoboterPosition().y, datenbank);
    sscanf(feldString,"F%i_N%i_O%i_S%i_W%i",&feld, &norden, &osten, &sueden, &westen);

    // wenn das Feld noch nicht besucht ist, sieh dich um und gehe ein Feld weiter
    if(!feld){
        umsehen(feldString);
        sscanf(feldString,"F%i_N%i_O%i_S%i_W%i",&feld, &norden, &osten, &sueden, &westen);
    }else{
        //falls schon besucht, erhöhe den Feld-counter um 1
        feld++;
    }
    //speichere aktuelles Feld
    sprintf(feldString,"F%i_N%i_O%i_S%i_W%i",feld, norden, osten, sueden, westen);
    speichereInDatenbank(feldString,getRoboterPosition().x,getRoboterPosition().y,datenbank);

    richtungNaechstesFeld=naechstesFeld(datenbank);

    // berechnet ob man in die entgegengesetzte Richtung gehen soll
    if((4+getBlickrichtung())%8==richtungNaechstesFeld){
        //wenn der Robotor in einer Sackgasse steckt und nur nach Hinten gehen kann, erhöhe den Feld wert noch einmal um Eins,
        //damit nicht im naechsten Feld der Roboter auf die Idee kommt das aktüelle Sackgassenfeld wieder zu besuchen.
        feld++;
        sprintf(feldString,"F%i_N%i_O%i_S%i_W%i",feld, norden, osten, sueden, westen);
        speichereInDatenbank(feldString,getRoboterPosition().x,getRoboterPosition().y,datenbank);
    }
    // gucke in die Richtung des nächsten Feldes
    setBlickrichtung(richtungNaechstesFeld);

	printf("\n x=%i, y=%i feld: %s naechstesFeld %i \n",getRoboterPosition().x,getRoboterPosition().y,feldString,richtungNaechstesFeld);
    // und gehe nach vorne
    geheNachVorn(1);
    free(datenbank);free(feldString);free(frontFeld);
}

void gameOfLife() {
	Position p;
	int x, y;
	char** nachher = malloc(sizeof(char*)*kartenXLaenge);
	for(x = 0; x < kartenXLaenge; x++) {
		nachher[x] = malloc(sizeof(char)*kartenYLaenge);
	}
	for(x = 0; x < kartenXLaenge; x++) {
		for(y = 0; y < kartenYLaenge; y++) {
			p.x = x;
			p.y = y;
			int i;
			int lebend = 0;
			for(i = 0; i < 8; i++) {
				printf("Nicht kaputt: %ix%i at %i\n", x, y, i);
				Parzelle* par = getNachbarZelle(p, i);
				if(par == NULL) {
					printf("NULL\n");
				} else {
					printf("parzelle %ix%i, zeichen: %c\n", par->pos.x, par->pos.y, par->zeichen);
				}

				if(par != NULL && par->zeichen == '#') {
					lebend++;
				}
			}
			if(lebend < 2) {
				nachher[x][y] = ' ';
			} else if(lebend == 3) {
				nachher[x][y] = '#';
			} else if(lebend > 3) {
				nachher[x][y] = ' ';
			} else {
				nachher[x][y] = getZeichenAnKoordinaten(x, y);
			}
		}
	}
	setKarte(nachher, kartenXLaenge, kartenYLaenge);
	aktualisiereParzellen();
}
