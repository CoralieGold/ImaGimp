#ifndef CALQUE_H_
#define CALQUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variables.h"
#include "lut.h"
#include "pixel.h"

typedef struct calque{
	struct calque *next;
	struct calque *previous;
	LUT * listLUT;
	int fusion;
	float alpha;
	int hauteur;
	int largeur;
	char codePPM[3];
	Pixel pixels[490000]; // Images de 1000 pixels au max
} Calque;

Calque * initListCalque();
int isListCalqueNull(Calque *List);
void addCalque(Calque *List);
void removeCalque(Calque *List);
void fusionCalques();
Calque * naviguate(Calque * cActif, int choix);
void appliquerLut(Calque * image);

void sepia(Calque * image);
void gris(Calque * image);

#endif
