#ifndef KARTE_H_INCLUDED
#define KARTE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>

#include "Algorithmen.h"

#define nord 0
#define nordOst 1
#define ost 2
#define suedOst 3
#define sued 4
#define suedWest 5
#define west 6
#define nordWest 7

/*
 * Die Groessen der Karte
 * */
extern int kartenXLaenge;
extern int kartenYLaenge;

/*
 * Wenn torusRaum auf 1 gesetzt ist wird die Karte als ein Torus behandelt
 * ist torusRaum 0 so muss auf die Grenzen der Karte geachtet werden
 * */
extern int torusRaum;

/*
 * Die Karte selbst ist eine Matrix karte[x][y](kein C-String).
 * Der Ursprung(0,0) der Karte ist links oben und der Punkt (x-1,y-1) ist die rechte untere Ecke.
 * */
extern char **karte;


/*
 * fuer eine einheitliche Benutzug der Koordinaten der Karte ist der Typ Position definiert der die Koordinaten eines Punktes speichert
 * */
typedef struct PositionStruct{
	int x;
	int y;
} Position;

/*
*/
extern Position ziel;


/*
 * Erstellt die Karte in Form eines char[] das gefuellt ist mit ' ' chars und
 * eine x kreuz y Matrix darstellt mit x=anzahlSpalten und y=anzahlZeilen
 * */
void initialisierung(int anzahlSpalten, int anzahlZeilen);

/*
* macht es möglich eine Karte in form eines Strings zu übergeben und zeichnet die zeichen als karte. zur zeilen trennung dienen '\n' zeichen. Die fünktion überprüft die angegebene weite und höhe mit der inizialisirten karte.
*/
void setKarte(char **kartenstr, int weite, int hoehe);

/*
 * gibt das Zeichen an der uebergebenen Position wieder.
 * */
char getZeichenAnPosition(Position position);
char getZeichenAnKoordinaten(int x, int y);

/*
 * setzst das uebergebene Zeichen an die uebergebene Position mit Pruefung der Position
 * gibt 0 zurueck wenn das Zeichen gesetzt werden konnte, wenn nicht einen anderen Wert.
 * */
int setZeichenAnPosition(char zeichen, Position position);
int setZeichenAnKoordinaten(char zeichen, int x, int y);

/*
 * Zeichnet die aktuelle karte auf dem CMD.
 * */
void zeichneKarte();

/*
* Sofern die Karte ein Zielfeld besitzt, gibt diese Funktion dieses Feld zurück. Ansonsten die Position (-1, -1)
*/
Position getZiel();



#endif // KARTE_H_INCLUDED
