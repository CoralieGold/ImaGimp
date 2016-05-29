#ifndef CALQUE_H_
#define CALQUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variables.h"
#include "lut.h"
#include "pixel.h"

/** Structure Calque **/
typedef struct calque{
	struct calque *next;
	struct calque *previous;
	LUT * listLUT;
	int fusion;
	float alpha;
	int hauteur;
	int largeur;
	char codePPM[3];
	Pixel pixels[490000]; /* Nombre maximum de pixels dans l'image : 700 * 700 */
} Calque;

/** FONCTIONS DE BASES **/

// Initialise une liste de calques
Calque * initListCalque();

// Renvoie 1 si la liste de calques est nulle, 0 sinon
int isListCalqueNull(Calque *List);

// Ajout un calque à une liste de calques
void addCalque(Calque *List);

// Supprime un calque d'une liste de calques
void removeCalque(Calque *List);

// Fusionne des calques
void fusionCalques();

// Renvoie le calque précédent ou suivant 
Calque * naviguate(Calque * cActif, int choix);

// Applique une liste de luts au calque
void appliquerLut(Calque * image);

/** FONCTIONS DE MODIFICATION **/

// Met l'image en noir et blanc
void nb(Calque * image);

// Met l'image en sépia
void sepia(Calque * image);

// Applique un filtre rouge
void rouge(Calque * image);

// Applique un filtre vert
void vert(Calque * image);

// Applique un filtre bleu
void bleu(Calque * image);

// Applique un filtre cyan
void cyan(Calque * image);

// Applique un filtre magenta
void magenta(Calque * image);

// Applique un filtre jaune
void jaune(Calque * image);

#endif
