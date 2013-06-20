#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "loesungsalgorithmen.h"
#include "Roboter.h"

void runSzenario3OURL(){
    if(schrittZaehler<2)U(1);
    else if(schrittZaehler>=2&&schrittZaehler<6)R(1);
    else if(schrittZaehler>=6&&schrittZaehler<8)U(1);
    else if(schrittZaehler>=8&&schrittZaehler<12)L(1);
    else if(schrittZaehler>=12&&schrittZaehler<14)U(1);
    else if(schrittZaehler>=14&&schrittZaehler<20)R(1);
    else if(schrittZaehler>=20)O(1);

	printf("schritte = %i\n",schrittZaehler);
	printf("%i", getBlickrichtung());
}

void runSzenario5dotfinder(){
    if(getFrontZeichen()=='.'||getFrontZeichen()=='Z'){
        geheNachVorn(1);
        zwischenSpeicher=' ';
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
    int posZeichen=holeSpeicherstand2d(roboterPosition.x,roboterPosition.y);
    int problem=0;

    if(!posZeichen){
        //rundumblick bestimmen
        int a=blickrichtung;
        blickrichtung=0;
        zellencode=0;

        if(frontSensor())zellencode+=1;
        if(rechterSensor())zellencode+=10;
        if(heckSensor())zellencode+=100;
        if(linkerSensor())zellencode+=1000;
        blickrichtung=a;
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
        if(!problem)setzeSpeicherstand2d(zeichen,roboterPosition.x,roboterPosition.y);

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
    if(zwischenSpeicher=='Z'){
        a[0]=schrittZaehler;
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
        a[1+schrittZaehler]=blickrichtung;
        geheNachVorn(1);
    }else{
        if(blickrichtung==0)geheNachVorn(1);
        if(blickrichtung==2)
        if(blickrichtung==4)
        if(blickrichtung==6)
        a[0]--;
    }

}
