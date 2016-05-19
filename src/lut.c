#include "include/lut.h"

//Initialiser une liste
LUT * initListeLUT(){
	LUT * List = malloc(sizeof(LUT));
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
/*void addLUT(LUT *List, int LUT[256]) {
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
	if (List->next == List) {//elle pointe sur elle même)
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
}*/

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

	LUT * tmp = List->previous;
	tmp->previous = List;
	List->previous = tmp->previous;
	free(tmp);
}


/*****FONCTION LUT*****/

//INVERT
LUT * invert(){
    LUT * nouveau = malloc(sizeof(LUT));
	int i;
	for (i = 0; i < 256; i++) {
		nouveau->LUT[i]=255-i;
	}
	return nouveau;
}

//ADDLUM
LUT * addLum(int lum){
    LUT * nouveau = malloc(sizeof(LUT));
	int i, lumiere;
	for (i = 0; i < 256; i++) {
		lumiere = i + lum;
		if(lumiere < 255) nouveau->LUT[i] = lumiere;
		else nouveau->LUT[i] = 255;
	}
	return nouveau;
}

//DIMLUM
LUT * dimLum(int lum){
    LUT * nouveau = malloc(sizeof(LUT));
	int i, lumiere;
	for (i = 0; i < 256; i++) {
		lumiere = i - lum;
		if(lumiere > 0) nouveau->LUT[i] = lumiere;
		else nouveau->LUT[i] = 0;
	}
	return nouveau;
}

//ADDCON
//255/2=127
//C -> valeur de l'ajout contraste
LUT * addCon(int c){
    LUT * nouveau = malloc(sizeof(LUT));
	int i, contraste;
	for (i = 0; i < 256; i++) {
		contraste = (-(127-i)*c)+127;
		if(contraste >= 255) nouveau->LUT[i] = 255;
		else if(contraste <= 0) nouveau->LUT[i] = 0;
		else nouveau->LUT[i]=contraste;
	}
	return nouveau;
}

//DIMCON
//Verifier que C =! 0
LUT * dimCon(int c){
	int i, contraste;
	LUT * nouveau = malloc(sizeof(LUT));
	if (c > 0) {
		for (i = 0; i < 256; i++) {
			contraste = (-(127-i)*(1/c))+127;
			if(contraste >= 255) nouveau->LUT[i] = 255;
			else if(contraste <= 0) nouveau->LUT[i] = 0;
			else nouveau->LUT[i]=contraste;
		}
	}
	return nouveau;
}

LUT * sepia(int p) {
	LUT * nouveau = malloc(sizeof(LUT));
	return nouveau;
}


