#include "Roboter.h"
#include <math.h>
#include "Szenario.h"

Roboter* alleRoboter;
Roboter* aktuellerRoboter;
int anzahlRoboter = 1;

int speicherKapazitaet=1000;

int spicher2dxKapazitaet=100;
int spicher2dyKapazitaet=100;

int richtungsOffsets[8][2] = { {0,-1}, {1,-1}, {1,0}, {1,+1}, {0,1}, {-1,+1}, {-1,0}, {-1,-1}};
/*
        701     7^1
        6R2     <R>
        543     5v3
*/
//char aussehensArray[9] = {'0', '1', '2', '3', '4', '5', '6', '7', 2};
// andere anzeige für den Roboter 9te stelle für das aussehen des roboters
//char aussehensArray[9] = {'^', 191, '>', 217, 'v', 192, '<', 218, 2};

void initialisiereRoboter(Position pos, int blickR){
	alleRoboter = malloc(sizeof(Roboter)*anzahlRoboter);

	//Erzeuge den "StandardRobo"
	char* aussehensArray[8] =  {'^', 191, '>', 217, 'v', 192, '<', 218, 2};
	char* unpassierbareZeichen[1] = {'#'};
	erzeugeNeuenRoboter(0, pos, blickR, aussehensArray, 'x', 0, unpassierbareZeichen, 1);
	setzeAktuellenRoboterAuf(0);

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
}


int istGueltigePosition(Position p) {
	return p.x >= 0 && p.y >= 0;
}

int erzeugeNeuenRoboter(int roboterID, Position pos, int blickrichtung, char* aussehensArray, char aussehen,
						 int aussehenAbhaengigVonBlickrichtung, char* unpassierbareZeichen, int unpassierbareZeichenLaenge) {
	if(roboterID >= anzahlRoboter) {
		return 0;
	}
	char* aus = malloc(sizeof(char)*8);
	kopiere(aus, aussehensArray, 8);
	char* un = malloc(sizeof(char)*unpassierbareZeichenLaenge);
	kopiere(un, unpassierbareZeichen, unpassierbareZeichenLaenge);
	Roboter robo = {roboterID, pos, blickrichtung, aus, aussehen, aussehenAbhaengigVonBlickrichtung, un, unpassierbareZeichenLaenge, 0, 0, 0, 0};
	alleRoboter[roboterID] = robo;
	setzeRoboterAufKarte(roboterID, pos);
	return 1;
}

int setzeAktuellenRoboterAuf(int roboterID) {
	if(roboterID >= anzahlRoboter) {
		return 0;
	}
	aktuellerRoboter = &(alleRoboter[roboterID]);
	//Legacy
	//roboterPosition = aktuellerRoboter->pos;
	//blickrichtung = aktuellerRoboter->blickrichtung;
	return 1;
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
    aktuellerRoboter->drehungsZaehler++;
    aktuellerRoboter->drehungsZaehler++;
}

void drehen(int grad,int drehRichtung){

        int a=grad%360+23;
        a=a/45;
        if(drehRichtung){
            aktuellerRoboter->blickrichtung=aktuellerRoboter->blickrichtung+a;

        }else{
            aktuellerRoboter->blickrichtung=aktuellerRoboter->blickrichtung-a;
            aktuellerRoboter->blickrichtung=aktuellerRoboter->blickrichtung+8;
        }
        aktuellerRoboter->drehungsZaehler+=a;
        aktuellerRoboter->blickrichtung=aktuellerRoboter->blickrichtung%8;
        if(aktuellerRoboter->aussehenAbhaengigVonBlickrichtung) {
			aktuellerRoboter->aussehen=aktuellerRoboter->aussehensArray[aktuellerRoboter->blickrichtung];
        }
       // blickrichtung = aktuellerRoboter->blickrichtung;
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

int bewegeRoboter(Position von, Position nach) {
    if(!istGueltigePosition(nach) || !istZeichenPassierbar(getZeichenAnKoordinaten(nach.x,nach.y))){
			printf("position %ix%i\n", nach.x, nach.y);
            printf("Ist die position gueltig? Antwort: %i \n", istGueltigePosition(nach));
            printf("Ist die position passierbar? Antwort: %i \n", istZeichenPassierbar(getZeichenAnKoordinaten(nach.x,nach.y)));
            aktuellerRoboter->kollision=1;
            return 0;
    }
    setzeRoboterAufKarte(aktuellerRoboter->roboterID, nach);
	aktuellerRoboter->pos = nach;
	//roboterPosition = nach;
    return 1;
}

int motorLinksUndRechtsAn(int schritte){
		Position p = getFrontPosition();
		aktuellerRoboter->schrittZaehler++;
	return bewegeRoboter(aktuellerRoboter->pos,p);
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
	if(!istGueltigePosition(p)) {
		return 0;
	}
	return getZeichenAnKoordinaten(p.x,p.y);
}

int sensor(int richtungsOffset) {
	int richtung = (aktuellerRoboter->blickrichtung+richtungsOffset)%8;
	Position p = getPositionInRichtung(richtung);
	if(!istGueltigePosition(p)) { //Außerhalb der Karte
		return 0;
    }
    return istZeichenPassierbar(getZeichenAnPosition(p));
}

int frontSensor(){
    return sensor(0);
}
int heckSensor(){
    return sensor(4);
}
int linkerSensor(){
    return sensor(6);
}
int rechterSensor(){
    return sensor(2);
}

Position getPositionInRichtung(int richtung){
    int x = aktuellerRoboter->pos.x+richtungsOffsets[richtung][0];
	int y = aktuellerRoboter->pos.y+richtungsOffsets[richtung][1];
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
		return sqrt(pow(p.x-aktuellerRoboter->pos.x, 2)+pow(p.y-aktuellerRoboter->pos.y, 2));
	}
	return -1;
}

int getBlickrichtung() {
	return aktuellerRoboter->blickrichtung;
}

void setBlickrichtung(int neueBlickRichtung){
    if(neueBlickRichtung < 0 || neueBlickRichtung > 7) {
		aktuellerRoboter->blickrichtung = 0;
    } else {
		aktuellerRoboter->blickrichtung = neueBlickRichtung;
    }
    if(aktuellerRoboter->aussehenAbhaengigVonBlickrichtung) {
		aktuellerRoboter->aussehen = aktuellerRoboter->aussehensArray[aktuellerRoboter->blickrichtung];
	}
}

//int richtungsOffsets[8][2] = { {0,-1}, {1,-1}, {1,0}, {1,+1}, {0,1}, {-1,+1}, {-1,0}, {-1,-1}};
Position getFrontPosition() {
    return getPositionInRichtung(aktuellerRoboter->blickrichtung);
}

int greifeGegenstand() {
    char zeichen = getFrontZeichen();
    if(istZeichenRelevant(zeichen)) {
		aktuellerRoboter->anzahlGesammelterGegenstaende++;
		setZeichenAnPosition(' ', getFrontPosition());
		return 1;
	}
	return 0;
}

int getAnzahlGesammelterGegenstaende() {
	return aktuellerRoboter->anzahlGesammelterGegenstaende;
}

//Erwartet für x und y einen der werte -1, 0, +1 je nach dem, in welche Richtung gegangen werden soll
//Nur für den internen Gebrauch
int bewegeInRichtung(int schritte, int x, int y) {
	int i;
    Position nach;
    for(i=0;i<schritte;i++){
        nach = aktuellerRoboter->pos;
        nach.x += x;
        nach.y += y;
        if(!bewegeRoboter(aktuellerRoboter->pos, nach)) {
				return 0;
        }
        aktuellerRoboter->schrittZaehler++;
    }
    return 1;
}

int O(int schritte){
    return bewegeInRichtung(schritte, 0, -1);
}

int U(int schritte){
    return bewegeInRichtung(schritte, 0, +1);
}

int L(int schritte){
    return bewegeInRichtung(schritte, -1, 0);
}

int R(int schritte){
    return bewegeInRichtung(schritte, +1, 0);
}

char getRoboterZeichen(int roboterID) {
	return alleRoboter[roboterID].aussehen;
}

int istZeichenPassierbar(char c) {
	return !enthaelt(aktuellerRoboter->unpassierbareZeichen, aktuellerRoboter->unpassierbareZeichenLaenge, c);
	//return c != '#';
}

Position getRoboterPosition() {
	return aktuellerRoboter->pos;
}

int getSchrittZaehler() {
	return aktuellerRoboter->schrittZaehler;
}

void erhoeheSchrittZaehler() {
	aktuellerRoboter->schrittZaehler++;
}

int getKollision() {
	return aktuellerRoboter->kollision;
}

void setKollision(int i) {
	aktuellerRoboter->kollision = i;
}

Roboter* getRoboter(int roboterID) {
	return &(alleRoboter[roboterID]);
}

char getZeichenAnRoboterPosition() {
	return getZeichenAnPosition(aktuellerRoboter->pos);
}
