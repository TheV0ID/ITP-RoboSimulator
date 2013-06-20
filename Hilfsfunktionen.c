
int enthaelt(char zeichenArray[], int laenge, char zeichen) {
	int i = 0;
	for(; i < laenge; i++) {
		if(zeichenArray[i] == zeichen) {
			return 1;
		}
	}
	return 0;
}
