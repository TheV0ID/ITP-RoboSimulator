#ifndef SZENARIO_H_INCLUDED
#define SZENARIO_H_INCLUDED


#include "Roboter.h"
/*
 *In der Szenarionummer wird die aktuelle Nummer des gewaehlten Senarios gespeichert.
 * */
extern int szenarioNummer;

/*
 * Speichert den pfad der zu verwändenden csv datei
 * */
extern char* DatenbankDateiPfad;

/*
 * Laedt das Szenario mit der uebergebenen Nummer
 * */
void ladeSzenario(int szenarioNummer);


/*
* Gibt wahr (return-Wert > 0) zurück, wenn das Ziel des Szenarios erreicht ist
*/
int istZielErreicht();

/*
* Aufzurufen nach jedem Durchlauf der run()-funktion, um auf die Aktionen des Roboters reagieren zu können.
*/
void nachDurchlauf();

/*
* Gibt wahr zurück, wenn es sich bei dem gegebenen Zeichen, um ein für das Szenario relevantes Zeichen handelt, wie etwa beim Einsammeln.
*/
int istZeichenRelevant(char zeichen);

 /*
 * Die Funktion szenarioX()// |x in [1,9]
 * laedt das jeweilige Szenario in die Karte und setzt den Roboter an einen vorgegebenen Punkt
 * */
void szenario1();
void szenario2();
void szenario3();
void szenario4();
void szenario5();
void szenario6();
void szenario7();
void szenario8();
void szenario9();



#endif // SZENARIO_H_INCLUDED
