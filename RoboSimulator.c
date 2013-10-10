#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include <windows.h>

#include "Szenario.h"
#include "loesungsalgorithmen.h"

#if defined(WIN32)
  #include <windows.h>
#elif defined(__UNIX__)
  #include <unistd.h>
#else
#endif



int millisleep(unsigned ms){
#if defined(WIN32)
  SetLastError(0);
  Sleep(ms);
  return GetLastError() ?-1 :0;
#elif defined(LINUX)
  return usleep(1000 * ms);
#else
#error ("no milli sleep available for platform")
  return -1;
#endif
}

// Globale Variable
int programmLaeuft = 1;

void vorEnde(){
    if(istZielErreicht()) {
		printf("Ziel erreicht!\n%i Schritte und %i 90 Grad Drehungen hat der Roboter gemacht.\n",schrittZaehler,drehungsZaehler);
		system("pause");
	} else {
		printf("Das Programm hat sich vor erreichen des Ziels beendet.\n");
		system("pause");
	}
	int i;
    if(szenarioNummer==1){
        for(i=0;i<=schrittZaehler;++i){
            printf("%i ,",speicher1d[i]);
        }
    }
}
/*
    Hilfsfunktionen für runSzenario4files;
	Ausnahmsweise in dieser Datei. Ansonsten finden sich solche konkreten Algorithmen in Algorithmen.c/.h
*/

//Bekommt gesagt, welcher Roboter gerade aktiv ist. Im Normalfall ist dies immer der einzige Roboter mit der Nummer 0.
void run(int roboterID)
{

//    runSzenario3quickReturn();
//    runSzenario3Karteerstellen();
//    runSzenario3OURL();
//    runSzenario4rightTurn();
//    runSzenario5dotfinder();

    //runSzenario4files();

    while(!frontSensor()) {
		drehe();
    }
    motorLinksUndRechtsAn(1);
}

void runOhneRobo() {
	gameOfLife();
}

int main(int argc, char const *argv[])
{
	int wiederholen=1;
    ladeSzenario(8);
    zeichneKarte();
	if(wiederholen){
			//TODO das mit der kollision tut so nur für den ersten roboter
		while(!istZielErreicht() && programmLaeuft && !(getRoboter(0)->kollision))
		{
			zeichneKarte();
			if(ohneRoboter) {
				runOhneRobo();
			} else {
				int i;
				run(0);
				//Schaltet so lange alle Roboter durch, bis anzahlRoboter erreicht wurde
				for(i = 1; setzeAktuellenRoboterAuf(i); i++) {
					run(i);
				}
				setzeAktuellenRoboterAuf(0);
				nachDurchlauf();
			}
			millisleep(500);
		}
	}else{
		run(0);
	}
	zeichneKarte();
	vorEnde();
    system("pause");
	return 0;
}
