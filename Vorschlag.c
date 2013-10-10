//Dashier in karte.c und natürlich in karte.h

int mapRichtungsOffsets[8][2] = { {0,-1}, {1,-1}, {1,0}, {1,+1}, {0,1}, {-1,+1}, {-1,0}, {-1,-1}};

char getNachbarZelle(Position p, int richtung) {
	int x = p.x+mapRichtungsOffsets[richtung][0];
	int y = p.y+mapRichtungsOffsets[richtung][1];
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
	if(p.x < 0 || p.y < 0) {
		0;
	}
	return karte[x][y];
}


//********************************

//Dashier über run() ausführen, also vermutlich in Loesungsalgorithmen

void gameOfLife() {
	Position p;
	int x, y;
	char** nachher = malloc(sizeof(char*)*kartenXLaenge);
	for(x = 0; x < kartenXLaenge; x++) {
		nachher[x] = malloc(sizeof(char)*kartenYLaenge);
	}
	for(x = 0; x < kartenXLaenge; x++) {
		for(y = 0; y < kartenYLaenge; y++) {
			p.x = x;
			p.y = y;
			int i;
			int lebend = 0;
			for(i = 0; i < 8; i++) {
				char zeichen = getNachbarZelle(p, i);

				if(zeichen == '#') { //Oder || zeichen == 0, wenn Randzellen, dort wo die Map zuende wäre, wenn kein torus raum eingestellt ist, als lebend zählen sollen 
					lebend++;
				}
			}
			if(lebend < 2) {
				nachher[x][y] = ' ';
			} else if(lebend == 3) {
				nachher[x][y] = '#';
			} else if(lebend > 3) {
				nachher[x][y] = ' ';
			} else {
				nachher[x][y] = getZeichenAnKoordinaten(x, y);
			}
		}
	}
	setKarte(nachher, kartenXLaenge, kartenYLaenge);
}

//***************************
//Als Szenario einfach szenario 1 kopieren und am Ende einmal an der Roboterposition das Roboterzeichen durch Leertaste oder Doppelkreuz ersetzen, sodass der Roboter nicht angezeigt wird.