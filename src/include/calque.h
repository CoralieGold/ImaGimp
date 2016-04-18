#include <stdio.h>
#include <stdlib.h>

#include "lut.h"
#include "pixel.h"

typedef struct calque{
	struct calque *next;
	struct calque *previous;
	LUT *listLUT;
	int fusion;
	float alpha;
	Pixel Pixels[][];
}Calque;

Calque * initListCalque();
int isListCalqueNull(Calque *List);
void addCalque(Calque *List);
int removeCalque(Calque *List);
void fusionCalques();
Calque * naviguate(Calque * cActif, int choix);
