#include "include/fichier.h"

Calque * lireImage(char nomImage[]) {
	if(NULL == nomImage) exit(EXIT_FAILURE);

	FILE *image = NULL;
	image = fopen(nomImage, "r");
	char chaine[262144]; // 512 * 512 pixels dans l'image

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

	int k, l;
	char rouge[3];
	char vert[3];
	char bleu[3];
	// cas image couleur P3
	if(!strcmp(codePPM, "P3")) {
		fgets(chaine, (3*hauteur * 3*largeur) * 6 , image);
		printf("Image (couleurs) : %s", chaine);
		k = 0;
		l = 0;
		for(i = 0; i < largeur; i ++) {
			for(j = 0; j < hauteur; j ++) {

				while(chaine[k] != ' ') {
					rouge[l] = chaine[k];
					k ++;
					l ++;
				}
				imageDeBase->pixels[i][j].r = atol(rouge);

				k ++;
				l = 0;

				while(chaine[k] != ' ') {
					vert[l] = chaine[k];
					k ++;
					l ++;
				}
				imageDeBase->pixels[i][j].g = atol(vert);

				k ++;
				l = 0;

				while(chaine[k] != ' ') {
					bleu[l] = chaine[k];
					k ++;
					l ++;
				}
				imageDeBase->pixels[i][j].b = atol(bleu);

				k ++;
				l = 0;

				printf("Rouge : %d \n", imageDeBase->pixels[i][j].r);
				printf("Vert : %d \n", imageDeBase->pixels[i][j].g);
				printf("Bleu : %d \n", imageDeBase->pixels[i][j].b);
				printf("\n");

				for(int p = 0; p < 3; p ++) {
				rouge[p] = ' ';
				vert[p] = ' ';
				bleu[p] = ' ';
				}
			}
		}
	}
	// cas image n&b
	else if(!strcmp(codePPM, "P2")) {
		k = 0;
		l = 0;
		imageDeBase->codePPM[1] = '2';
		fgets(chaine, (3*hauteur * 3*largeur) * 2 , image);
		printf("Image (n&b) : %s", chaine);
		for(i = 0; i < largeur; i ++) {
			for(j = 0; j < hauteur; j ++) {
				while(chaine[k] != ' ') {
					rouge[l] = chaine[k];
					k ++;
					l ++;
					printf("k : %d, l : %d \n", k, l);
				}
				imageDeBase->pixels[i][j].r = atol(rouge);
				imageDeBase->pixels[i][j].g = atol(rouge);
				imageDeBase->pixels[i][j].b = atol(rouge);
				printf("\n");
				printf("Rouge : %d \n", imageDeBase->pixels[i][j].r);
				printf("Vert : %d \n", imageDeBase->pixels[i][j].g);
				printf("Bleu : %d \n", imageDeBase->pixels[i][j].b);
				printf("\n");
				k ++;
				l = 0;

				for(int p = 0; p < 3; p ++) {
					rouge[p] = ' ';
				}

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
		for(int i = 0; i < imageFinale->hauteur; i ++) {
			for(int j = 0; j < imageFinale->largeur; j ++) {
				if(strcmp(imageFinale->codePPM, "P3") == 0) fprintf(image, "%d %d %d ", imageFinale->pixels[i][j].r, imageFinale->pixels[i][j].g, imageFinale->pixels[i][j].b);
				else if(strcmp(imageFinale->codePPM, "P2") == 0) fprintf(image, "%d ", imageFinale->pixels[i][j].r);
			}
		}
	}
	fclose(image);
}
