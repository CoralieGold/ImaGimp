#ifndef FICHIER_H_
#define FICHIER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pixel.h"
#include "calque.h"

Calque * lireImage(char nomImage[]);

void ecritureImage(Calque * imageFinale, char nomImage[]);

#endif


