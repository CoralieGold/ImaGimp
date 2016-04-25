#include <stdio.h>
#include <stdlib.h>

#include "variables.h"
#include "lut.h"
#include "pixel.h"

typedef struct calque{
	struct calque *next;
	struct calque *previous;
	LUT *listLUT;
	int fusion;
	float alpha;
	Pixel pixels[512][512]; // Les images font toutes 512 * 512 pixels
} Calque;

Calque * initListCalque();
int isListCalqueNull(Calque *List);
void addCalque(Calque *List);
void removeCalque(Calque *List);
void fusionCalques();
Calque * naviguate(Calque * cActif, int choix);
