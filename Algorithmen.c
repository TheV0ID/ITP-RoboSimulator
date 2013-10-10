#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Algorithmen.h"
#include "Roboter.h"


//Variablen für Befehle aus einer Datei
FILE * datei;
int sprungmarke = -1;
int aktuelleZeile = -1;

//Wenn die Befehlsdatei noch nicht geladen wurde, soll dies hier geschehen.
void initialisiere(char pfad[]) {
	if(datei == NULL) {
		datei = fopen(pfad, "r");
		if(datei == NULL) {
			printf("\n\nDie Datei s konnte nicht geöffnet werden.\n\n");
		}
	}
}

//Das rand muss der Form rand(x,y) entsprechen und darf nur einstellige Zahlen enthalten.
int werteRandAus(char befehl[]) {
	int lower = 0;
	int upper = 1;
	if(strncmp("rand(", befehl, 5) == 0) {
		if('0' <= befehl[5] && befehl[5] <= '9') {
			lower = befehl[5]-'0';
		}
		if('0' <= befehl[7] && befehl[7] <= '9') {
			upper = befehl[7]-'0';
		}
	}
	if(upper-lower > 0) {
		return rand()%(upper-lower+1)+lower;
	} else {
		return lower;
	}
}

/*Wertet einen Befehl aus. Möglich bisher:
Loop:
vor(); Ohne/mit einer Zahl und einem Aufruf von rand(x,y)
drehe(); Ohne/mit einer Zahl und einem Aufruf von rand(x,y)

Beispiel:
	vor(rand(2,3));
	vor(5);
	vor();

Gibt 1 zurück, wenn ein sinnvoller Befehl gefunden wurde, 0 bei Kommentaren, nicht-Befehlen
und Befehlen die keine direkte Auswirkung haben (wie etwa Loop:)
*/
int werteAus(char befehl[]) {
	char * arg;
	if(befehl[0] == '#') {
		return 0;
	}
	if(strncmp("Loop:", befehl, 5) == 0) {
		sprungmarke = aktuelleZeile+1;
		return 0;
	} else if(strncmp("vor(", befehl, 4) == 0) {
		arg = &befehl[4];
		if(')'==arg[0]) {
			motorLinksUndRechtsAn(1);
		} else if('0' <= arg[0] && arg[0] <= '9') {
			motorLinksUndRechtsAn(arg[0]-'0');
		} else {
			motorLinksUndRechtsAn(werteRandAus(arg));
		}
		return 1;
	} else if(strncmp("drehe(", befehl, 6) == 0) {
		arg = &befehl[6];
		if(')'==arg[0]) {
			motorLinksAn(1);
		} else if('0' <= arg[0] && arg[0] <= '9') {
			motorLinksAn(arg[0]-'0');
		} else {
			motorLinksAn(werteRandAus(arg));
		}
		return 1;
	}
	return 0;
}

//Liest die Befehle für den Roboter aus einer Datei
void ausDatei(char* pfad, int* programmLaeuft) {

	initialisiere(pfad);
	char zeile[100];
	int sinnvollerBefehlGefunden = 0;
	while(sinnvollerBefehlGefunden == 0) {
		if(fgets(zeile, 100, datei) != NULL) { //Die Datei ist noch nicht zuende
			aktuelleZeile++;
			sinnvollerBefehlGefunden = werteAus(zeile);
			if(sinnvollerBefehlGefunden) {
				printf("%s\n", zeile);
			}
		} else if(sprungmarke != -1) { //Dateiende erreicht und es existiert eine Sprungmarke
			rewind(datei);
			int i = 0;
			while(i++ < sprungmarke && fgets(zeile, 100, datei));
		} else { //Dateiende erreicht, ohne dass jemals eine Sprungmarke aufgetreten ist.
			*programmLaeuft = 0;
			sinnvollerBefehlGefunden = 1;
		}
	}
}


int enthaelt(char zeichenArray[], int laenge, char zeichen) {
	int i = 0;
	for(; i < laenge; i++) {
		if(zeichenArray[i] == zeichen) {
			return 1;
		}
	}
	return 0;
}

void kopiere(char* neu, char* alt, int laenge) {
	for(laenge--; laenge >= 0; laenge--) {
		neu[laenge] = alt[laenge];
	}
}


int sucheGespeicherteKoordinaten(int x,int y, char* pfad,int* zeile){
    int i,
        x2,
        y2;
    char *str = malloc(sizeof(char)*150);

    FILE* db = fopen(pfad,"r");
    if(db == NULL){
            printf("Fehler beim laden der Datei: %s\n",pfad);
            return 1;
    }
    // falls die Koordinaten noch nicht gespeichert wurden, schreibe -1 in "zeile"
    *zeile=-1;
    for(i=1;fgets(str,150,db)!= NULL;++i){
        if(i){
            sscanf(str,"%i; %i; %*s ;",&x2,&y2);
            if(x==x2&&y==y2){
                // falls passende Koordinaten gefunden wurden, schreibe die Zeile "i" in der sie gefunden wurden in "zeile"
                *zeile=i;
            }
        }
    }
    fclose(db);
    free(db);
    free(str);

    return 0;
}

int anhaengen(char* pfad,char* inhalt){
    FILE* db = fopen(pfad, "a");
    if(db == NULL){
        printf("Fehler bei Dateizugriff!\n");
        return 1;
    }
    fprintf(db, "%s",inhalt);;
    fclose(db);

    free(db);
    return 0;
}

int wieLangIstDatei(char* pfad){
    int len;

    FILE* db = fopen(pfad, "r");
    if(db == NULL){
        printf("Fehler bei Dateizugriff!\n");
        return -1;
    }
    char* str=malloc(sizeof(char)*250);
    for(len=0;fgets(str,250,db)!=NULL;len++);
    fclose(db);

    free(db);
    free(str);
    return len;
}

int einfuegenInZeile(char* pfad,int zeile,char* str){
    int size = wieLangIstDatei(pfad);
    int i,inhaltslaenge=250;
    char** dateiInhalt=malloc(size*sizeof(char*));
    for(i=0;i<size;i++){
        dateiInhalt[i]=malloc(inhaltslaenge*sizeof(char));
    }

    FILE* db = fopen(pfad, "r");
    if(db == NULL){
        printf("Fehler bei Dateizugriff!\n");
        return 1;
    }
    for(i=0;i<size;i++){
        fgets(dateiInhalt[i],inhaltslaenge,db);
    }
    strcpy(dateiInhalt[zeile-1],str);

    fclose(db);
    db = fopen(pfad, "w");
    if(db == NULL){
        printf("Fehler bei Dateizugriff!\n");
        return 1;
    }
    for(i=0;i<size;i++){
        fprintf(db,"%s",dateiInhalt[i]);
    }
    fclose(db);

    for(i=0;i<size;i++){
        free(dateiInhalt[i]);
    }
    free(dateiInhalt);
    free(db);

    return 0;
}

int speichereInDatenbank(char* inhalt,int x,int y,char* pfad){
    int zeile;
    if(sucheGespeicherteKoordinaten(x, y, pfad, &zeile)){
        return 1;
    }
    char* str=malloc(sizeof(char)*250);
    sprintf(str, "%i; %i; %s ;\n",x,y,inhalt);
    if(zeile==-1){
        anhaengen(pfad,str);
    }else{
        einfuegenInZeile(pfad,zeile,str);
    }
    free(str);
    return 0;
}

int holeInhaltAusDatei(char* inhalt,int inhaltLaenge, int x, int y, char* pfad){
    int pos;
    if(sucheGespeicherteKoordinaten(x,y,pfad,&pos)){
        return 1;
    }
    strcpy(inhalt,"F0_N0_O0_S0_W0");
    if(pos!=-1){
        int i;
        FILE* db = fopen(pfad, "r");
        if(db == NULL){
            printf("Fehler bei Dateizugriff!\n");
            return 1;
        }
        for(i=0;i<pos;i++){
            fgets(inhalt,inhaltLaenge,db);
            sscanf(inhalt,"%*i; %*i; %s ;",inhalt);
        }
        fclose(db);
        free(db);
    }
    return 0;
}

void umsehen(char* feldString){
    int blick,
        norden=0,
        osten=0,
        sueden=0,
        westen=0;

    blick=getBlickrichtung();
    setBlickrichtung(nord);
    if(frontSensor())norden=1;
    if(rechterSensor())osten=1;
    if(heckSensor())sueden=1;
    if(linkerSensor())westen=1;
    setBlickrichtung(blick);

    sprintf(feldString,"F1_N%i_O%i_S%i_W%i", norden, osten, sueden, westen);
}

int naechstesFeld(char* datenbank){
    int b=getBlickrichtung(),
        ausgaenge=0,
        feld,
        hinten,
        min,
        res;
    int* fi = malloc(sizeof(int)*8);
    fi[0]=0; fi[1]=9999999;// ausgangNord, Feldwerd nord
    fi[2]=0; fi[3]=9999999;// ausgangWest, Feldwerd west
    fi[4]=0; fi[5]=9999999;// ausgangSued, Feldwerd sued
    fi[6]=0; fi[7]=9999999;// ausgangOst, Feldwerd ost

    char* frontFeld = malloc(sizeof(char)*250);
    char* Feldstr = malloc(sizeof(char)*250);

    if(holeInhaltAusDatei(Feldstr, 250, getRoboterPosition().x, getRoboterPosition().y, datenbank)){
        return -1;
    }
    sscanf(Feldstr,"F%i_N%i_O%i_S%i_W%i",&feld, &fi[nord], &fi[ost], &fi[sued], &fi[west]);
    if(fi[nord]){
        setBlickrichtung(nord);
        if(holeInhaltAusDatei(frontFeld, 250, getFrontPosition().x, getFrontPosition().y, datenbank)){
            return -1;
        }
        sscanf(frontFeld,"F%i_N%*i_O%*i_S%*i_W%*i", &fi[nord+1]);
        ausgaenge++;
    }
    if(fi[ost]){
        setBlickrichtung(ost);
        if(holeInhaltAusDatei(frontFeld, 250, getFrontPosition().x, getFrontPosition().y, datenbank)){
            return -1;
        }
        sscanf(frontFeld,"F%i_N%*i_O%*i_S%*i_W%*i", &fi[ost+1]);
        ausgaenge++;
    }
    if(fi[sued]){
        setBlickrichtung(sued);
        if(holeInhaltAusDatei(frontFeld, 250, getFrontPosition().x, getFrontPosition().y, datenbank)){
            return -1;
        }
        sscanf(frontFeld,"F%i_N%*i_O%*i_S%*i_W%*i", &fi[sued+1]);
        ausgaenge++;
    }
    if(fi[west]){
        setBlickrichtung(west);
        if(holeInhaltAusDatei(frontFeld, 250, getFrontPosition().x, getFrontPosition().y, datenbank)){
            return -1;
        }
        sscanf(frontFeld,"F%i_N%*i_O%*i_S%*i_W%*i", &fi[west+1]);
        ausgaenge++;
    }
    setBlickrichtung(b);
    hinten = (b+4)%8;

    min=fi[nord+1];
    if(fi[ost+1]<min)min=fi[ost+1];
    if(fi[sued+1]<min)min=fi[sued+1];
    if(fi[west+1]<min)min=fi[west+1];

    //Reihenfolge für Bewegung nächstes Feld liegt:
    if(fi[getBlickrichtung()]&&fi[getBlickrichtung()+1]==min){// vorne
        res=getBlickrichtung();
    }else{
        drehen(90,0);
        // rechts
        if(fi[getBlickrichtung()]&&fi[getBlickrichtung()+1]==min){
            res=getBlickrichtung();
        }else{
            drehen(90,0);drehen(90,0);
            b=(b+4)%8;// links
            if(fi[getBlickrichtung()]&&fi[getBlickrichtung()+1]==min){
                res=getBlickrichtung();
            }else{
                drehen(90,0);drehen(90,0);drehen(90,0);
                // hinten
                if(fi[getBlickrichtung()]&&fi[getBlickrichtung()+1]==min){
                    res=getBlickrichtung();
                }
            }
        }
    }
    printf("\nAusgaenge: %i, v=%i,h=%i |=>>> res = %i\n",ausgaenge,getBlickrichtung(),hinten,res);
    printf("\n\t\t%i\n\t%i\t%i\t%i\n\t\t%i\n", fi[nord+1], fi[west+1], feld, fi[ost+1], fi[sued+1]);

    //Arrays freigeben
    free(fi);free(frontFeld);free(Feldstr);
    return res;
}


