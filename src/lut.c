#include "include/lut.h"

// Initialise une liste
LUT * initListeLUT()
{
	LUT * List = malloc(sizeof(LUT));
	List->previous = NULL;
	List->next = NULL;
	return List;
}

// Retourne 1 si la liste est vide, 0 sinon
int isListNull(LUT *List){
	return NULL == List->next;
}

// Ajout d'un LUT -- Ne fonctionne pas à la compilation
/*void addLUT(LUT *List, int LUT[256])
{
	//Si la n'existe pas
	if (NULL == List)
	{
		return;
	}

	//Si la liste est vide
	if (isListNull(List) == 1)
	{
		List->next = List;
		List->previous = List;
		for (int i = 0; i < 256; i++)
		{
			List->LUT[i]=LUT[i];
		}
		return;
	}

	// Si la liste contient un seul noeud
	if (List->next == List) {//elle pointe sur elle même)
		LUT * nouveau = malloc(sizeof(LUT));
		nouveau->previous = List;
		nouveau->next = List;
		List->next = nouveau;
		List->previous = nouveau;
		for (int i = 0; i < 256; i++)
		{
			nouveau->LUT[i]=LUT[i];
		}
		return;
	}

	// Sinon c'est qu'il y a déjà plein de noeud
	LUT * new = malloc(sizeof(LUT));
	new->next = List;
	new->previous = List->previous;
	List->previous->next = new;
	List->previous = new;
	for (int i = 0; i < 256; i++)
	{
		new->LUT[i]=LUT[i];
	}
}*/

// Supression d'un lut
void removeLut(LUT *List)
{
	if (NULL == List)
	{
		return;
	}

	if (isListNull(List))
	{
		return;
	}

	if (List->next == List)
	{
		List->next = NULL;
		List->previous = NULL;
		return;
	}

	LUT * tmp = List->previous;
	tmp->previous = List;
	List->previous = tmp->previous;
	free(tmp);
}

/** MODIFICATION DE L'IMAGE **/

// INVERT : inverse les couleurs
LUT * invert()
{
    LUT * nouveau = malloc(sizeof(LUT));
	int i;
	for (i = 0; i < 256; i++)
	{
		nouveau->LUT[i]=255-i;
	}
	printf("Inversion des couleurs : fait. \n");
	return nouveau;	
}

// ADDLUM : augmente la luminosite
LUT * addLum(float lum)
{
    LUT * nouveau = malloc(sizeof(LUT));
	int i;
	float lumiere;
	if(lum > 0)
	{
		for (i = 0; i < 256; i++)
		{
			lumiere = i + lum;
			if(lumiere < 255) nouveau->LUT[i] = lumiere;
			else nouveau->LUT[i] = 255;
		}
		printf("Ajout de lumière : fait. \n");
	}
	else printf("Ajout de lumière : impossible (paramètre incorrect). \n");
	return nouveau;
}

// DIMLUM : diminue la luminosite
LUT * dimLum(float lum)
{
    LUT * nouveau = malloc(sizeof(LUT));
	int i;
	float lumiere;
	if(lum > 0)
	{
		for (i = 0; i < 256; i++)
		{
			lumiere = i - lum;
			if(lumiere > 0) nouveau->LUT[i] = lumiere;
			else nouveau->LUT[i] = 0;
		}
		printf("Diminution de lumière : fait. \n");
	}
	else printf("Diminution de lumière : impossible (paramètre incorrect). \n");
	return nouveau;
}

// ADDCON : augmente le contraste
LUT * addCon(float c)
{
	LUT * nouveau = malloc(sizeof(LUT));
	int i;
	float contraste;
	if (c > 1)
	{
		for (i = 0; i < 256; i++)
		{
			contraste = (-(127-i)*c)+127;
			if(contraste >= 255) nouveau->LUT[i] = 255;
			else if(contraste <= 0) nouveau->LUT[i] = 0;
			else nouveau->LUT[i]=contraste;
		}
		printf("Ajout de contraste : fait. \n");
	}
	else printf("Ajout de contraste : impossible (paramètre incorrect). \n");
	return nouveau;
}

// DIMCON : diminue le contraste
LUT * dimCon(float c)
{
	int i;
	float contraste;
	LUT * nouveau = malloc(sizeof(LUT));
	if (c > 1)
	{
		for (i = 0; i < 256; i++)
		{
			contraste = (-(127-i)*(1/c))+127;
			if(contraste >= 255) nouveau->LUT[i] = 255;
			else if(contraste <= 0) nouveau->LUT[i] = 0;
			else nouveau->LUT[i]=contraste;
		}
		printf("Diminution de contraste : fait. \n");
	}
	else printf("Diminution de contraste : impossible (paramètre incorrecte). \n");
	return nouveau;
}


