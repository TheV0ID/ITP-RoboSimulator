#ifndef ALGORITHMEN_H_INCLUDED
#define ALGORITHMEN_H_INCLUDED


/*
Liest die Anweisungen für den Roboter aus der gegebenen Datei. Bei jedem Aufruf wird genau ein Steuerbefehl abgearbeitet. Ein Beispiel für eine solche Datei, ist die Datei "Befehlsdatei-Beispiel.txt".

Setzt programmLaeuft auf 0, wenn das Dateiende erreicht ist, ohne dass eine Schleife eingebaut worden ist.
*/
void ausDatei(char* pfad, int* programmLaeuft);

/*
* Gibt wahr (1) zurück, wenn das gegebene Array mit der Länge laenge, das gegebene Zeichen enthaelt.
*/
int enthaelt(char zeichenArray[], int laenge, char zeichen);

/*
* Kopiere den Inhalt eines Arrays von alt nach neu
*/
void kopiere(char* neu, char* alt, int laenge);

int sucheGespeicherteKoordinaten(int x,int y, char* pfad,int* zeile);

int anhaengen(char* pfad,char* inhalt);

int wieLangIstDatei(char* pfad);

int einfuegenInZeile(char* pfad,int zeile,char* str);

int speichereInDatenbank(char* inhalt,int x,int y,char* pfad);

int holeInhaltAusDatei(char* inhalt,int inhaltLaenge, int x, int y, char* pfad);

void umsehen(char* feldString);

int naechstesFeld(char* datenbank);


#endif // ALGORITHMEN_H_INCLUDED
