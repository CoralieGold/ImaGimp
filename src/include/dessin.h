#ifndef DESSIN_H_
#define DESSIN_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Redimensionne la taille de la fenêtre
void reshape(unsigned int windowWidth, unsigned int windowHeight);

// Lance la fenêtre
void setVideoMode(unsigned int windowWidth, unsigned int windowHeight);

// Ecrit du texte dans la fenêtre
void ecrireTexte(float x, float y, void* font, const char* s);

/** Nombre de bits par pixel de la fenêtre **/
static const unsigned int BIT_PER_PIXEL = 32;

/** Nombre minimal de millisecondes separant le rendu de deux images **/
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/** Nombre max de points dessines **/
static const unsigned int NB_MAX_PT = 50;

#endif
