#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/pixel.h"
#include "include/calque.h"
#include "include/lut.h"
#include "include/fichier.h"

int main(int argc, char** argv) {
	if(argc < 4 && argc%2 != 0) {
		printf("Vous devez donner un paramètre pour chaque code LUT.");
		return 1;
	}

	Calque * image = lireImage(argv[1]);
    	printf("image : %d", image->hauteur);

	char codeLut[6];
	int parametre;

	int i = 2;
	while(argc > i) {
		
		strcpy(codeLut,argv[i]);
		parametre = atoi(argv[i+1]);

		addCalque(image);
		if(!strcmp(codeLut, "ADDLUM"))
		image->listLUT = addLum(parametre); //si les deux chaines egales
		else if (!strcmp(codeLut, "DIMLUM")) image->listLUT = dimLum(parametre);
		else if (!strcmp(codeLut, "DIMCON")) image->listLUT = dimCon(parametre);
		else if (!strcmp(codeLut, "ADDCON")) image->listLUT = addCon(parametre);
		else if (!strcmp(codeLut, "INVERT")) image->listLUT = invert(parametre);
		else if (!strcmp(codeLut, "SEPIA")) image->listLUT = sepia(parametre);

		appliquerLut(image);

		i = i + 2;
	}

	fusionCalques(image);

	for(int i = 0; i < image->hauteur; i ++) {
		printf("test");
		for(int j = 0; j < image->largeur; j ++) {
			printf("Pixel %d %d : %d %d %d\n", i, j, image->pixels[i][j].r, image->pixels[i][j].g, image->pixels[i][j].b);
		}
	}

	ecritureImage(image, argv[1]);

	return 0;
}
