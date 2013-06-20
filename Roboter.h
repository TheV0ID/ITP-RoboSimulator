#ifndef ROBOTER_H_INCLUDED
#define ROBOTER_H_INCLUDED

#include "Karte.h"
#include "Auswertung.h"

#include <stdbool.h>
/*
* Speichert die Position des roboters auf der Karte
*/
extern Position  roboterPosition;

/*                                             701
 *Zeigt die Blickrichtung des Roboters R an :  6R2
 *                                             543
 * */
extern int blickrichtung;

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
/*
* speichert die Zeichen der positionen zwischen die sich an der position des Roboters befanden. kann genutzt werden um diese zu löschen durch überschreiben mit ' '.
*/
extern char zwischenSpeicher;

/*
* gibt an ob der Roboter kollidiert ist oder nicht 0 sollange der roboter nicht kollidiert ist.
*/
extern int kollision;

// Initialisierung
/*
 *Initialisiert den Roboter
 * */
void initialisiereRoboter(Position position,int blickrichtung);

/*
* Setze das Zeichen, das an der Stelle des Roboters platziert wird, wenn dieser sich das nächste mal weiterbewegt.
*/
void setZwischenSpeicherZeichen(char c);

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
 * Die Sensoren geben "false" wieder wenn der jeweilige Sensor eine Wand erkannt hat, sonst "true".
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
* bewegt den Roboter nach oben um die ubergebene anzahl der schritte. Gibt 1 im erfolgsfall zuruck 0 sonst.
*/
int O(int schritte);

/*
* bewegt den Roboter nach unten um die ubergebene anzahl der schritte. Gibt 1 im erfolgsfall zuruck 0 sonst.
*/
int U(int schritte);


/*
* bewegt den Roboter nach links um die ubergebene anzahl der schritte. Gibt 1 im erfolgsfall zuruck 0 sonst.
*/
int L(int schritte);


/*
* bewegt den Roboter nach rechts um die ubergebene anzahl der schritte. Gibt 1 im erfolgsfall zuruck 0 sonst.
*/
int R(int schritte);

/*
* bewegt den Roboter von position von zur position nach wenn die position nach frei ist. Gibt 1 im erfolgsfall zuruck 0 sonst.
*/
int bewegeRoboter(Position von, Position nach);


#endif // ROBOTER_H_INCLUDED
