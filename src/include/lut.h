#include <stdio.h>
#include <stdlib.h>

//Liste chainé doublement circulaire
//Pour savoir si on a fait un tour, on stock l'adresse de la liste et on verifie qu'on est pas encore passé dessus

typedef struct lut{
	int LUT[256];
	struct lut *previous;
	struct lut *next;
}LUT;

LUT * initListeLUT();
int isListNull(LUT *List);
void addLUT(LUT *List, int LUT[256]);
void removeNode(LUT *List);

LUT invert();
LUT addLum();
LUT dimLum();
LUT addCon();
LUT dimCon();