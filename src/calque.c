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
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			List->pixels[i][j]= createPixel(255,255,255,1);
		}
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
	for(int i = 0; i < new->hauteur; i ++) {
		for(int j = 0; j < new->largeur; j ++) {
			new->pixels[i][j] = createPixel(255, 255, 255, 1);
		}
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
         for(int i = 0; i < c_base->hauteur; i ++) {
            for(int j = 0; j < c_base->largeur; j ++) {
                c_res->pixels[i][j].r = c_res->pixels[i][j].r + c_tmp->alpha * c_tmp->pixels[i][j].r * c_tmp->pixels[i][j].alpha;
                c_res->pixels[i][j].g = c_res->pixels[i][j].g + c_tmp->alpha * c_tmp->pixels[i][j].g * c_tmp->pixels[i][j].alpha;
                c_res->pixels[i][j].b = c_res->pixels[i][j].b + c_tmp->alpha * c_tmp->pixels[i][j].b * c_tmp->pixels[i][j].alpha;
            }
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
	printf("test Lut\n");
	Calque tmp;
	tmp = *image;
	while(tmp.listLUT->next != NULL) {
		for(int i = 0; i < 256;i++){
			tmp.listLUT->LUT[i] = tmp.listLUT->LUT[tmp.listLUT->next->LUT[i]];
		}
		//image->listLUT = image->listLUT->next;
	}
	for (int i = 0; i < image->hauteur; i++) {
		for (int j = 0; j < image->largeur; j++) {
	 		tmp.pixels[i][j].r = tmp.listLUT->LUT[tmp.pixels[i][j].r];
	 		tmp.pixels[i][j].g = tmp.listLUT->LUT[tmp.pixels[i][j].g];
	 		tmp.pixels[i][j].b = tmp.listLUT->LUT[tmp.pixels[i][j].b];
	 	}
	}
	*image = tmp;
}
