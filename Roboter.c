#include "Roboter.h"
#include <math.h>
#include "Szenario.h"

Position roboterPosition;
int blickrichtung=0;
int kollision=0;
int speicherKapazitaet=1000;

int spicher2dxKapazitaet=100;
int spicher2dyKapazitaet=100;

char aussehen=2;
char zwischenSpeicher = ' ';
int richtungsOffsets[8][2] = { {0,-1}, {1,-1}, {1,0}, {1,+1}, {0,1}, {-1,+1}, {-1,0}, {-1,-1}};
/*
        701     7^1
        6R2     <R>
        543     5v3
*/
//char aussehensArray[9] = {'0', '1', '2', '3', '4', '5', '6', '7', 2};
// andere anzeige für den Roboter 9te stelle für das aussehen des roboters
char aussehensArray[9] = {'^', 191, '>', 217, 'v', 192, '<', 218, 2};
int anzahlGesammelterGegenstaende = 0;

void initialisiereRoboter(Position pos,int blickR){
    speicher1d=malloc(sizeof(int) * speicherKapazitaet);
    int i,j;
    for(i=0;i<speicherKapazitaet;i++){
        speicher1d[i]=0;
    }

    spicher2dxKapazitaet=kartenXLaenge;
    spicher2dyKapazitaet=kartenXLaenge;
    speicher2d=malloc(sizeof(int*)*spicher2dxKapazitaet);

	for(i=0;i<spicher2dxKapazitaet;i++){
 		speicher2d[i]=malloc(sizeof(int)*spicher2dyKapazitaet);
	}
	for(i=0;i<spicher2dxKapazitaet;i++){
 		for(j=0;j<spicher2dyKapazitaet;j++){
            speicher2d[i][j]=0;
        }
	}

    roboterPosition = pos;
	blickrichtung=blickR;
	aussehen = aussehensArray[blickrichtung];
	karte[roboterPosition.x][roboterPosition.y]=aussehen;
}

int* hole1dSpeicherArray(){
    return speicher1d;
}

int holeSpeicherstand2d(int x, int y){
    return speicher2d[x][y];
}

void setzeSpeicherstand2d(int speicherstand, int x, int y){
    speicher2d[y][x]=speicherstand;
}

void drehe(){
    drehen(90,1);
    drehungsZaehler++;
    drehungsZaehler++;
}

void drehen(int grad,int drehRichtung){

        int a=grad%360+23;
        a=a/45;
        if(drehRichtung){
            blickrichtung=blickrichtung+a;

        }else{
            blickrichtung=blickrichtung-a;
            blickrichtung=blickrichtung+8;
        }
        drehungsZaehler+=a;
        blickrichtung=blickrichtung%8;
        aussehen=aussehensArray[blickrichtung];
        setZeichenAnPosition(aussehen,roboterPosition);
        zeichneKarte();
}

void gebe2dSpeicherAus(){
    int i,j,z;
    for(i=0;i<spicher2dxKapazitaet;++i){
        for(j=0;j<spicher2dyKapazitaet;++j){
                z=speicher2d[i][j];
                if(z){
                    printf("%c",z);
                }else{
                    printf("%i",z);
                }
            }
        printf("\n");
    }
}

int bewegeRoboter(Position von, Position nach){
    if((von.x<0||von.y<0||nach.x<0||nach.y)<0){
        kollision=1;
        return 0;
    }
    if(getZeichenAnKoordinaten(nach.x,nach.y)=='#'){
            kollision=1;
            return 0;
    }
    setZeichenAnPosition(zwischenSpeicher,von);
    zwischenSpeicher = getZeichenAnPosition(nach);
	setZeichenAnPosition(aussehen,nach);
	roboterPosition=nach;
    return 1;
}

int motorLinksUndRechtsAn(int schritte){
		Position p = getFrontPosition();
		schrittZaehler++;
	return bewegeRoboter(roboterPosition,p);
}

int geheNachVorn(int schritte){
    return motorLinksUndRechtsAn(schritte);
}

void motorRechtsAn(int schritte){
	int i;
    for(i=0;i<schritte;++i)drehen(45,0);
}

void motorLinksAn(int schritte){
	int i;
    for(i=0;i<schritte;++i)drehen(45,1);
}

char getFrontZeichen() {
	Position p = getFrontPosition();
	if(p.x < 0 || p.y < 0) {
		return '#';
	}
	return getZeichenAnKoordinaten(p.x,p.y);
}

int frontSensor(){
    return getFrontZeichen()!='#';
}
int heckSensor(){
    int heckrichtung=(blickrichtung+4)%8;
    Position p = getPositionInRichtung(heckrichtung);
    return getZeichenAnPosition(p)!='#';
}
int linkerSensor(){
    int heckrichtung=(blickrichtung+6)%8;
    Position p = getPositionInRichtung(heckrichtung);
    return getZeichenAnPosition(p)!='#';
}
int rechterSensor(){
    int heckrichtung=(blickrichtung+2)%8;
    Position p = getPositionInRichtung(heckrichtung);
    return getZeichenAnPosition(p)!='#';
}

Position getPositionInRichtung(int richtung){
    int x = roboterPosition.x+richtungsOffsets[richtung][0];
	int y = roboterPosition.y+richtungsOffsets[richtung][1];
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
	Position p = {x, y};
	return p;
}

double getEntfernungZumZiel() {
	Position p = getZiel();
	if(p.x != -1 && p.y != -1) {
		return sqrt(pow(p.x-roboterPosition.x, 2)+pow(p.y-roboterPosition.y, 2));
	}
	return -1;
}

int getBlickrichtung() {
	return blickrichtung;
}

void setBlickrichtung(int blickRichtung){
    if(blickRichtung<0){
        blickrichtung=0;
        aussehen=aussehensArray[0];
    }else if(blickRichtung==8){
        blickrichtung=0;
        aussehen=aussehensArray[blickRichtung];
    }else if(blickRichtung<8){
        blickrichtung=blickRichtung;
        aussehen=aussehensArray[blickRichtung];
    }else{
        blickrichtung=0;
        aussehen=aussehensArray[0];
    }
}

//int richtungsOffsets[8][2] = { {0,-1}, {1,-1}, {1,0}, {1,+1}, {0,1}, {-1,+1}, {-1,0}, {-1,-1}};
Position getFrontPosition() {
    return getPositionInRichtung(blickrichtung);
}

void setZwischenSpeicherZeichen(char c) {
	zwischenSpeicher = c;
}

int greifeGegenstand() {
    char zeichen = getFrontZeichen();
    if(istZeichenRelevant(zeichen)) {
		anzahlGesammelterGegenstaende++;
		setZeichenAnPosition(' ', getFrontPosition());
		return 1;
	}
	return 0;
}

int getAnzahlGesammelterGegenstaende() {
	return anzahlGesammelterGegenstaende;
}

int O(int schritte){
    int i;
    Position nach;
    for(i=0;i<schritte;i++){
        nach = roboterPosition;
        nach.y--;
        if(!bewegeRoboter(roboterPosition, nach))return 0;
        schrittZaehler++;
    }
    return 1;
}

int U(int schritte){
    int i;
    Position nach;
    for(i=0;i<schritte;i++){
        nach = roboterPosition;
        nach.y++;
        if(!bewegeRoboter(roboterPosition, nach))return 0;
        schrittZaehler++;
    }
    return 1;
}

int L(int schritte){
    int i;
     Position nach;
    for(i=0;i<schritte;i++){
        nach = roboterPosition;
        nach.x--;
        if(!bewegeRoboter(roboterPosition, nach))return 0;
        schrittZaehler++;
    }
    return 1;
}

int R(int schritte){
    int i;
    Position nach;
    for(i=0;i<schritte;i++){
        nach = roboterPosition;
        nach.x++;
        if(!bewegeRoboter(roboterPosition, nach))return 0;
        schrittZaehler++;
    }
    return 1;
}
