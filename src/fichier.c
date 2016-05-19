#include "include/fichier.h"

Calque * lireImage(char nomImage[]) {
	if(NULL == nomImage) exit(EXIT_FAILURE);

	FILE *image = NULL;
	image = fopen(nomImage, "r");

	if (image == NULL) exit(EXIT_FAILURE);

	char codePPM[3];
	char taille[12];
	char largeurC[5];
	int largeur;
	char hauteurC[5];
	int hauteur;
	char maxCouleurC[3];
	int maxCouleur;

	Calque * imageDeBase = initListCalque();

	fgets(codePPM, 3, image);
	fseek(image, 1, SEEK_CUR);
	fgets(taille, 10, image);
	fseek(image, 1, SEEK_CUR);
	fgets(maxCouleurC, 4, image);

	int i = 0;
	int j = 0;
	while(i < 4) {
		largeurC[j] = taille[i];
		i ++;
		j ++;
	}
	i ++;
	j = 0;
	while(i < 9) {
		hauteurC[j] = taille[i];
		i ++;
		j ++;
	}

	largeur = atoi(largeurC);
	hauteur = atoi(hauteurC);
	maxCouleur = atoi(maxCouleurC);


	printf("Code ppm : %s \n", codePPM);
	printf("Largeur : %d \n", largeur);
	printf("Hauteur : %d \n", hauteur);
	printf("Couleur : %d \n", maxCouleur);

	imageDeBase->hauteur = hauteur;
	imageDeBase->largeur = largeur;

fseek(image, 1, SEEK_CUR);

	char rouge[4];
	char vert[4];
	char bleu[4];
	// cas image couleur P3
	if(!strcmp(codePPM, "P3")) {
		for(i = 0; i < largeur * hauteur; i ++) {

				//fseek(image, 0, SEEK_CUR);
				fgets(rouge, 5, image);
				imageDeBase->pixels[i].r = atol(rouge);
				//fseek(image, 0, SEEK_CUR);
				fgets(vert, 5, image);
				imageDeBase->pixels[i].g = atol(vert);
				//fseek(image, 0, SEEK_CUR);
				fgets(bleu, 5, image);
				imageDeBase->pixels[i].b = atol(bleu);

				printf("Rouge : %d \n", imageDeBase->pixels[i].r);
				printf("Vert : %d \n", imageDeBase->pixels[i].g);
				printf("Bleu : %d \n", imageDeBase->pixels[i].b);
				printf("\n");

				for(int p = 0; p < 4; p ++) {
				rouge[p] = ' ';
				vert[p] = ' ';
				bleu[p] = ' ';
				}
			
		}
	}
	// cas image n&b
	else if(!strcmp(codePPM, "P2")) {
		imageDeBase->codePPM[1] = '2';
		for(i = 0; i < largeur * hauteur; i ++) {
				fgets(rouge, 5, image);
				imageDeBase->pixels[i].r = atol(rouge);
			imageDeBase->pixels[i].g = atol(vert);
			imageDeBase->pixels[i].b = atol(bleu);
				printf("Rouge : %d \n", imageDeBase->pixels[i].r);
				printf("Vert : %d \n", imageDeBase->pixels[i].g);
				printf("Bleu : %d \n", imageDeBase->pixels[i].b);
				printf("\n");

				for(int p = 0; p < 4; p ++) {
				rouge[p] = ' ';
				}
			
		}
	}

	fclose(image);
	return imageDeBase;
}

void ecritureImage(Calque * imageFinale, char nomImage[]) {
	int i = 0;
	char nomImageFinale[100];
	char dossier[100];
	while(nomImage[i] != '.') {
		nomImageFinale[i] = nomImage[i];
		i++;
	}
	strcat(nomImageFinale, "New.ppm");
	strcat(dossier, "images/");
	strcat(dossier, nomImageFinale);

	FILE * image = NULL;
	image = fopen(nomImageFinale, "w");
	if(image != NULL) {
		fprintf(image, "%s \n%d    %d   \n255 \n", imageFinale->codePPM, imageFinale->largeur, imageFinale->hauteur);
		for(int i = 0; i < imageFinale->hauteur * imageFinale->largeur; i ++) {

				if(strcmp(imageFinale->codePPM, "P3") == 0) fprintf(image, "%d %d %d ", imageFinale->pixels[i].r, imageFinale->pixels[i].g, imageFinale->pixels[i].b);
				else if(strcmp(imageFinale->codePPM, "P2") == 0) fprintf(image, "%d ", imageFinale->pixels[i].r);
			
		}
	}
	fclose(image);
}
