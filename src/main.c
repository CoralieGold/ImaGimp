#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/pixel.h"
#include "include/calque.h"
#include "include/lut.h"
#include "include/fichier.h"

int main(int argc, char** argv) {
	if(argc < 5 && argc%2 == 0) {
		printf("Vous devez donner un paramètre pour chaque code LUT.\n");
		return 1;
	}

	Calque * image = lireImage(argv[1]);

	if(image->hauteur * image->largeur > 490000) {
		printf("L'image est trop grande pour être traitée. \n");
		return 1;
	}
	
	char nomNouvelleImage[30];
	strcpy(nomNouvelleImage, argv[2]); 
	char codeLut[9];
	float parametre;

	/*image->listLUT = addLum(0);
	appliquerLut(image);
	dessinerHistogramme(image);*/	
	
	printf("Début du traitement.\n");
	int i = 3;
	while(argc > i) {
		
		strcpy(codeLut,argv[i]);
		parametre = atof(argv[i+1]);

		addCalque(image);

		if(!strcmp(codeLut, "SEPIA") || !strcmp(codeLut, "NB") || !strcmp(codeLut, "ROUGE") || !strcmp(codeLut, "VERT") || !strcmp(codeLut, "BLEU") || !strcmp(codeLut, "JAUNE") || !strcmp(codeLut, "MAGENTA") || !strcmp(codeLut, "CYAN")) {
			if (!strcmp(codeLut, "SEPIA")) sepia(image);
			else if (!strcmp(codeLut, "NB")) nb(image);
			else if (!strcmp(codeLut, "ROUGE")) rouge(image);
			else if (!strcmp(codeLut, "VERT")) vert(image);
			else if (!strcmp(codeLut, "BLEU")) bleu(image);
			else if (!strcmp(codeLut, "CYAN")) cyan(image);
			else if (!strcmp(codeLut, "MAGENTA")) magenta(image);
			else if (!strcmp(codeLut, "JAUNE")) jaune(image);
		}
		else {
			if(!strcmp(codeLut, "ADDLUM"))
			image->listLUT = addLum(parametre); //si les deux chaines egales
			else if (!strcmp(codeLut, "DIMLUM")) image->listLUT = dimLum(parametre);
			else if (!strcmp(codeLut, "DIMCON")) image->listLUT = dimCon(parametre);
			else if (!strcmp(codeLut, "ADDCON")) image->listLUT = addCon(parametre);
			else if (!strcmp(codeLut, "INVERT")) image->listLUT = invert();
		
		
			
			appliquerLut(image);
		}

		i = i + 2;
	}

	fusionCalques(image);
	printf("Fin du traitement. \n");

	/*for(int i = 0; i < image->largeur * image->hauteur; i ++) {
			printf("Pixel %d : %d %d %d\n", i, image->pixels[i].r, image->pixels[i].g, image->pixels[i].b);
	}*/

	ecritureImage(image, nomNouvelleImage);

	return 0;
}
