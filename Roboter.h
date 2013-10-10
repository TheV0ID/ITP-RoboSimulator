#ifndef ROBOTER_H_INCLUDED
#define ROBOTER_H_INCLUDED

#include "Karte.h"
#include "Auswertung.h"

typedef struct RoboterStruct {
	int roboterID;
	Position pos;
	int blickrichtung;
	char* aussehensArray;
	char aussehen;
	int aussehenAbhaengigVonBlickrichtung;
	char* unpassierbareZeichen;
	int unpassierbareZeichenLaenge;
	int kollision; //Hat eine Kollision stattgefunden? 0 so lange dies nicht passiert ist.
	int drehungsZaehler;
	int schrittZaehler;
	int anzahlGesammelterGegenstaende;
} Roboter;

extern Roboter* aktuellerRoboter;
extern Roboter* alleRoboter;

extern int anzahlRoboter;


/*
* Speichert die Position des roboters auf der Karte. VARIABLE NUR NOCH AUS KOMPATIBILITÄTSGRÜNDEN IM CODE!
*/
//extern Position roboterPosition;

/*                                             701
 *Zeigt die Blickrichtung des Roboters R an :  6R2
 *                                             543

 VARIABLE NUR NOCH AUS KOMPATIBILITÄTSGRÜNDEN IM CODE!
 * */
//extern int blickrichtung;

/*
* Der Speicher kann genutzt werden um Informationen uber meherere run() durchläufe zu bewahren.
*/
int speicherKapazitaet;
int *speicher1d;

/*
* gibt die adresse des Speichers zuruck
*/
int* hole1dSpeicherArray();
void gebe2dSpeicherAus();
/*
* zweidimensionales int array zum speichern von Informationen dazu sind funktionen zum erhlten der informationen und zum setzen der informationen.
*/
int spicher2dxKapazitaet;
int spicher2dyKapazitaet;
int **speicher2d;
int holeSpeicherstand2d(int x, int y);
void setzeSpeicherstand2d(int speicherstand, int x, int y);


// Initialisierung
/*
 *Initialisiert den Roboter
 * */
void initialisiereRoboter(Position position,int blickrichtung);

//bewegung

/*
 * Gibt die aktuelle Blickrichtung des Roboters wieder
 * */
int getBlickrichtung();

/*
 *setzt die Blickrichtung des Roboters
 */
void setBlickrichtung(int blickRichtung);

/*
* Gibt die Position des aktuell ausgewählten Roboters zurück.
*/
Position getRoboterPosition();

/*
 *dreht den Roboter um eine vordefinierte schrittzahl in vorgegebener richtung wie in den ersten Uebungen zb. rechtsherum um 90 grad
 * */
void drehe();

/*
 *dreht den roboter um eine anzahl an grad in 45grad schritten bei denen 0 immer die front des Roboters ist.
 *die drehRichtung gibt an ob linksherum(gegen den Uhrzeigersinn) oder rechtsherum(im Uhrzeigersinn) gedreht wird
 */
void drehen(int grad,int drehRichtung);

/*
 * Schaltet den rechten Motor an, bewirkt die Drehung gegen den Uhrzeigersinn.
 * die Schritte wirken sich auf die Gradzahl der Drehung aus. Schrittweite von 1 ist eine Drehung um 45 grad gegen den uhrzeigersinn so wÃ¼rde
 * aus der Blickrichtung 0 die blickrichtung 7
 */
void motorRechtsAn(int schritte);
/*
 * Schaltet den linken Motor an, bewirkt die Drehung im Uhrzeigersinn.
 * die schritte wirken sich auf die gradzahl der drehung an schrittweite von 1 ist eine Drehung um 45 grad im Uhrzeigersinn so wÃ¼rde
 * aus der Blickrichtung 0 die Blickrichtung 1
 */
void motorLinksAn(int schritte);

/*
 * Schaltet beide Motoren an und bewirkt die Bewegung in Blickrichtung um die uebergebene Anzahl an Schritten. Die tatsächlich zurückgelegte Anzahl an Schritten wird zurückgegeben.
 */
int motorLinksUndRechtsAn(int schritte);

/*
* bewegt den roboter nach vorne um die anzahl schritte;
*/
int geheNachVorn(int schritte);

//sensoren

/*
 * Die Sensoren geben "false" (0) wieder wenn der jeweilige Sensor eine Wand erkannt hat, sonst "true" (1).
 * */
int frontSensor();
int heckSensor();
int linkerSensor();
int rechterSensor();

/*
* Gibt die Entfernung zum Ziel an, sofern eines existiert. Ansonsten -1
*/
double getEntfernungZumZiel();

/*
* Gibt die Position zurück diesich zum roboter in uebergebener richtung befindet. Liegt die Position nicht innerhalb der Karte,
* ist mindestens eine der beiden Koordinaten negativ
*/
Position getPositionInRichtung(int richtung);
/*
* Gibt die Position in Blickrichtung des Roboters zurück. Liegt die Position nicht innerhalb der Karte,
* ist mindestens eine der beiden Koordinaten negativ
*/
Position getFrontPosition();

/*
* Liefert das Zeichen in Blickrichtung des Roboters zurück.
*/
char getFrontZeichen();

/*
* Sammelt das vor dem Roboter liegende Item ein. Bei einem Fehlschlag wird 0 zurückgegeben.
*/
int greifeGegenstand();

/*
* Gibt die Anzahl der bereits vom Roboter gefunden Gegenstände zurück.
*/
int getAnzahlGesammelterGegenstaende();

/*
* bewegt den Roboter so weit wie möglich nach oben um die ubergebene anzahl der schritte. Gibt 1 im erfolgsfall zuruck 0 sonst.
*/
int O(int schritte);

/*
* bewegt den Roboter so weit wie möglich nach unten um die ubergebene anzahl der schritte. Gibt 1 im erfolgsfall zuruck 0 sonst.
*/
int U(int schritte);


/*
* bewegt den Roboter so weit wie möglich nach links um die ubergebene anzahl der schritte. Gibt 1 im erfolgsfall zuruck 0 sonst.
*/
int L(int schritte);


/*
* bewegt den Roboter so weit wie möglich nach rechts um die ubergebene anzahl der schritte. Gibt 1 im erfolgsfall zuruck 0 sonst.
*/
int R(int schritte);

/*
* bewegt den Roboter von position von zur position nach wenn die position nach frei ist. Gibt 1 im erfolgsfall zuruck 0 sonst.
*/
int bewegeRoboter(Position von, Position nach);

/*
* Gibt das Zeichen mit der der Roboter mit der gegebenen Kennnummer dargestellt werden soll.
* Dies kann je nach Roboter und je nach Blickrichtung variieren.
*/
char getRoboterZeichen(int roboterID);

/*
* Gibt an, ob das gegebene Zeichen für den aktuellen Roboter passierbar ist.
* So können verschiedene Roboter verschiedene Geländetauglichkeit haben.
* 0 steht für nicht passierbar, 1 für passierbar.
*/
int istZeichenPassierbar(char c);

int getSchrittZaehler();

void erhoeheSchrittZaehler();

int getKollision();

void setKollision(int i);

Roboter* getRoboter(int roboterID);

int erzeugeNeuenRoboter(int roboterID, Position pos, int blickrichtung, char* aussehensArray, char aussehen, int aussehenAbhaengigVonBlickrichtung, char* unpassierbareZeichen, int unpassierbareZeichenLaenge);

char getZeichenAnRoboterPosition();

#endif // ROBOTER_H_INCLUDED
