#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

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

void run()
{

//    runSzenario3quickReturn();
//    runSzenario3Karteerstellen();
//    runSzenario3OURL();
//    runSzenario4rightTurn();
//    runSzenario5dotfinder();

    runSzenario4files();


}

int main(int argc, char const *argv[])
{

	int wiederholen=1;
    ladeSzenario(4);
    zeichneKarte();
	if(wiederholen){
		while(!istZielErreicht() && programmLaeuft && !kollision)
		{
			zeichneKarte();
			run();
			nachDurchlauf();
			//system("pause");
			millisleep(500);
		}
	}else{
		run();
	}
	zeichneKarte();
	vorEnde();
    system("pause");
	return 0;
}
