#include <stdio.h>
#include <stdlib.h>

#include "src/include/pixel.h"
#include "src/include/calque.h"
#include "src/include/variables.h"
#include "src/include/lut.h"

Calque * lireImage(char nomImage[]) {
	if(NULL == image) exit(EXIT_FAILURE);

	FILE *image = NULL;
	image = fopen(nomImage, "r");
	char chaine[262144]; // 512 * 512 pixels dans l'image

	if (image == NULL) exit(EXIT_FAILURE);
	fgets(chaine, 262144, image);

	Calque * imageDeBase = initListCalque();

	int k = 0;
	for(int i; i < 512; i ++) {
		for(int j; j < 512; j ++) {
			imageDeBase->pixels[i][j] = chaine[k];
			k ++;
		}
	}
	return imageDeBase;
}

int main(int argc, char** argv) {
	if(argc != 4) return 1;

	char codeLut[] = argv[2];
	int parametre = argv[3];

	Calque * image = lireImage(argv[1]);
	
	switch(codeLut) {
		case "ADDLUM":
			image->listLUT = addLum(parametre);
			break;
		case "DIMLUM":
			image->listLUT = dimLum(parametre);
			break;
		case "ADDCON":
			image->listLUT = addCon(parametre);
			break;
		case "DIMCON":
			image->listLUT = dimCon(parametre);
			break;
		case "INVERT":
			image->listLUT = invert(parametre);
			break;
		case "SEPIA":
			image->listLUT = sepia(parametre);
			break;
		default :

			break;
	}
	return 0;
}
