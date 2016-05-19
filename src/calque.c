#include "include/calque.h"

Calque * initListCalque(){
	Calque *List = malloc(sizeof(Calque));
	List->next = NULL;
	List->previous = NULL;
	List->fusion = 0;
	List->alpha = 0;
	List->listLUT = NULL;
	List->largeur = 0;
	List->hauteur = 0;
	List->codePPM[0] = 'P';
	List->codePPM[1] = '3';
	for (int i = 0; i < 490000; i++) {
		List->pixels[i] = createPixel(255,255,255,1);
	}
	return List;
}

int isListCalqueNull(Calque *List){
	return NULL == List->listLUT; //retourne soit 0 soit 1
}

void addCalque(Calque *List){
	if (NULL == List) {
		return;
	}

	if (isListCalqueNull(List)==1) {
		List->listLUT = initListeLUT();
	}
	Calque *tmp = List;
	while (tmp->next !=NULL) {
		tmp = tmp->next; //On va jusqu'au dernier pour ajouter new à la fin de la liste
	}
	Calque *new = malloc(sizeof(Calque));
	new->next = NULL;
	new->previous = tmp;
	tmp->next = new;
	new->fusion = 0;
	new->hauteur = List->hauteur;
	new->largeur = List->largeur;
	//strcat(new->codeLUT, List->codeLUT);
	new->listLUT = initListeLUT();
	for(int i = 0; i < new->hauteur * new->largeur; i ++) {
		new->pixels[i] = createPixel(255, 255, 255, 1);
	}
	List->next = new;
}

void removeCalque(Calque *List){
	if (NULL==List || isListCalqueNull(List)) {
		return;
	}
	Calque *tmp = List;
	if (NULL == tmp->next) {
		free(tmp->listLUT);
		return;
	}
	while (NULL != tmp->next->next) {
		tmp = tmp->next;
	}
	free(tmp->next);
	tmp->next = NULL;
}

void fusionCalques(Calque * c_base){
    Calque * c_res = c_base;
    Calque * c_tmp = c_base;
    while(c_tmp->next != NULL) {
         for(int i = 0; i < c_base->largeur * c_base->hauteur; i ++) {
                c_res->pixels[i].r = c_res->pixels[i].r + c_tmp->alpha * c_tmp->pixels[i].r * c_tmp->pixels[i].alpha;
                c_res->pixels[i].g = c_res->pixels[i].g + c_tmp->alpha * c_tmp->pixels[i].g * c_tmp->pixels[i].alpha;
                c_res->pixels[i].b = c_res->pixels[i].b + c_tmp->alpha * c_tmp->pixels[i].b * c_tmp->pixels[i].alpha;
        }
        c_tmp = c_tmp->next;
    }
}


//Naviguer entre les calques
// choix > 0 : on navigue vers la droite (next)
// choix < 0 : on navigue vers la gauche (previous)
Calque * naviguate(Calque * cActif, int choix){
	if (choix>0) {
		if (NULL != cActif->next) {
			return cActif->next;
		}
		return cActif;
	}
	else{
		if (NULL != cActif->previous) {
			return cActif->previous;
		}
		return cActif;
	}
}

//APPLIQUER UN LUT
/*1- on fusionne tous les LUT 1 et 2 ensemble dans LU3
LUT3 = LUT2[LUT1]
2- On applique le LUT à chaque pixel*/
void appliquerLut(Calque * image) {
	Calque tmp;
	tmp = *image;
	while(tmp.listLUT->next != NULL) {
		for(int i = 0; i < 256;i++){
			tmp.listLUT->LUT[i] = tmp.listLUT->LUT[tmp.listLUT->next->LUT[i]];
		}
		//image->listLUT = image->listLUT->next;
	}
	for (int i = 0; i < image->largeur * image->hauteur; i++) {
	 		tmp.pixels[i].r = tmp.listLUT->LUT[tmp.pixels[i].r];
	 		tmp.pixels[i].g = tmp.listLUT->LUT[tmp.pixels[i].g];
	 		tmp.pixels[i].b = tmp.listLUT->LUT[tmp.pixels[i].b];
	}
	*image = tmp;
}
void gris(Calque * image) {
	//addCalque(image);
	int moyenne;
	for(int i = 0; i < image->hauteur * image->largeur; i ++) {
		moyenne = (image->pixels[i].r + image->pixels[i].g + image->pixels[i].b) / 3;
		if(moyenne < 0) moyenne = 0;
		else if(moyenne > 255) moyenne = 255;
		image->pixels[i].r = moyenne;
		image->pixels[i].g = moyenne;
		image->pixels[i].b = moyenne;
	}
	image->codePPM[1] = '2';
}

void sepia(Calque * image) {
	gris(image);
	image->codePPM[1] = '3';
	for(int i = 0; i < image->hauteur * image->largeur; i ++) {
		image->pixels[i].r = image->pixels[i].r + 60;
		image->pixels[i].g = image->pixels[i].g + 20;
		if(image->pixels[i].r > 255) image->pixels[i].r = 255;
		if(image->pixels[i].g > 255) image->pixels[i].g = 255;
	}
}
