#ifndef FICHIER_H_
#define FICHIER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pixel.h"
#include "calque.h"
#include "lut.h"

// Lecture d'une image ppm
Calque * lireImage(char nomImage[]);

// Ecriture d'une image ppm
void ecritureImage(Calque * imageFinale, char nomImage[]);

#endif


