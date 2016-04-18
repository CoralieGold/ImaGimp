#include "include/lut.h"

//Initialiser une liste
LUT * initListeLUT(){
	LUT *List = malloc(sizeof(LUT));
	List->previous = NULL;
	List->next = NULL;
	return List;
}

//Regarde si la liste est vide
int isListNull(LUT *List){
	return NULL == List->next;
	//équivalent à
	// if (List->next == NULL) {
	// 	return 1;
	// }
	// else{
	// 	return 0;
	// }
}

//Ajout d'un LUT
void addLUT(LUT *List, int LUT[256]){
	//Si la n'existe pas
	if (NULL == List) {
		return;
	}

	//Si la liste est vide
	if (isListNull(List) == 1) {
		List->next = List;
		List->previous = List;
		for (int i = 0; i < 256; i++) {
			List->LUT[i]=LUT[i];
		}
		return;
	}

	//Si la liste contient un seul noeud
	if (List->next = List) {//elle pointe sur elle même)
		LUT *new = malloc(sizeof(LUT));
		new->previous = List;
		new->next = List;
		List->next = new;
		List->previous = new;
		for (int i = 0; i < 256; i++) {
			new->LUT[i]=LUT[i];
		}
		return;
	}

	//Sinon c'est qu'il y a déjà plein de noeud
	LUT *new = malloc(sizeof(LUT));
	new->next = List;
	new->previous = List->previous;
	List->previous->next = new;
	List->previous = new;
	for (int i = 0; i < 256; i++) {
		new->LUT[i]=LUT[i];
	}
}

//Supression d'un noeud
void removeNode(LUT *List){
	if (NULL == List) {
		return;
	}

	if (isListNull(List)) {
		return;
	}

	if (List->next == List) {
		List->next = NULL;
		List->previous = NULL;
		return;
	}

	LUT *tmp = List->previous;
	tmp->previous = List;
	List->previous = tmp->previous;
	free(tmp);
}


/*****FONCTION LUT*****/

//INVERT
LUT invert(){
	int i;
	for (i = 0; i < 256; i++) {
		LUT[i]=255-i;
	}
}

//ADDLUM
LUT addLum(){
	int i;
	for (i = 0; i < 256; i++) {
		LUT[i]=i+n;
	}
}

//DIMLUM
LUT dimLum(){
	int i;
	for (i = 0; i < 256; i++) {
		LUT[i]=i-n;
	}
}

//ADDCON
//255/2=127
//C -> valeur de l'ajout contraste
LUT addCon(){
	int i;
	for (i = 0; i < 256; i++) {
		LUT[i]=(-(127-i)*c)+127;
	}
}

//DIMCON
//Verifier que C =! 0
LUT dimCon(){
	int i;
	for (i = 0; i < 256; i++) {
		if (c !=0) {
			LUT[i]=(-(127-i)*(1/c))+127;
		}
	}
}

//APPLIQUER UN LUT
/*1- on fusionne tous les LUT 1 et 2 ensemble dans LU3
LUT3 = LUT2[LUT1]
2- On applique le LUT à chaque pixel*/

//w = largeur
//h = hauteur
// for (i = 0; i < w; i++) {
// 	for (j = 0; j < h; j++) {
// 		calque.pixel[i][j].r = LUT[calque.pixel[i][j].r]
// 		calque.pixel[i][j].v = LUT[calque.pixel[i][j].r]
// 		calque.pixel[i][j].b = LUT[calque.pixel[i][j].r]
// 	}
// }