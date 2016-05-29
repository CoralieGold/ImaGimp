#ifndef LUT_H_
#define LUT_H_

#include <stdio.h>
#include <stdlib.h>

/* Structure LUT */
typedef struct lut {
	int LUT[256];
	struct lut *previous;
	struct lut *next;
} LUT;

/** FONCTIONS DE BASE **/

// Initialise une liste
LUT * initListeLUT();

// Retourne 1 si la liste est vide, 0 sinon
int isListNull(LUT *List);

// Ajout d'un LUT -- Ne fonctionne pas à la compilation
void addLUT(LUT *List, int LUT[256]);

// Supprime un lut
void removeLut(LUT *List);

/** MODIFICATION DE L'IMAGE **/

// INVERT : inverse les couleurs
LUT * invert();

// ADDLUM : augmente la luminosite
LUT * addLum(float lum);

// DIMLUM : diminue la luminosite
LUT * dimLum(float lum);

// ADDCON : augmente le contraste
LUT * addCon(float c);

// DIMCON : diminue le contraste
LUT * dimCon(float c);

#endif
