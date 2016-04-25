#include "include/calque.h"

Calque * initListCalque(){
	Calque *List = malloc(sizeof(Calque));
	List->next = NULL;
	List->previous = NULL;
	List->fusion = 0;
	List->alpha =0;
	List->listLUT = NULL;
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
	new->listLUT = initListeLUT();
	 for(int i = 0; i <= h; i ++) {
			 for(int j = 0; j <= w; j ++) {
					 new->pixels[i][j] = createPixel(255, 255, 255, 1);
			 }
	 }
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
         for(int i = 0; i < h; i ++) {
            for(int j = 0; j < w; j ++) {
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
