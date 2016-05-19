#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/pixel.h"
#include "include/calque.h"
#include "include/lut.h"
#include "include/fichier.h"

int main(int argc, char** argv) {
	if(argc < 4 && argc%2 != 0) {
		printf("Vous devez donner un paramètre pour chaque code LUT.\n");
		return 1;
	}

	Calque * image = lireImage(argv[1]);

	if(image->hauteur * image->largeur > 490000) {
		printf("L'image est trop grande pour être traitée. \n");
		return 1;
	}
	
	char codeLut[6];
	float parametre;

	int i = 2;
	while(argc > i) {
		
		strcpy(codeLut,argv[i]);
		parametre = atof(argv[i+1]);

		addCalque(image);

		if(!strcmp(codeLut, "SEPIA") || !strcmp(codeLut, "GRIS")) {

			if (!strcmp(codeLut, "SEPIA")) sepia(image);
			else if (!strcmp(codeLut, "GRIS")) gris(image);
		}
		else {
			if(!strcmp(codeLut, "ADDLUM"))
			image->listLUT = addLum(parametre); //si les deux chaines egales
			else if (!strcmp(codeLut, "DIMLUM")) image->listLUT = dimLum(parametre);
			else if (!strcmp(codeLut, "DIMCON")) image->listLUT = dimCon(parametre);
			else if (!strcmp(codeLut, "ADDCON")) image->listLUT = addCon(parametre);
			else if (!strcmp(codeLut, "INVERT")) image->listLUT = invert();
		
		
			//fusionCalques(image);
			appliquerLut(image);
		}

		i = i + 2;
	}

	//fusionCalques(image);

	/*for(int i = 0; i < image->largeur * image->hauteur; i ++) {
			printf("Pixel %d : %d %d %d\n", i, image->pixels[i].r, image->pixels[i].g, image->pixels[i].b);
	}*/

	ecritureImage(image, argv[1]);

	return 0;
}
