#ifndef DESSIN_H_
#define DESSIN_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void reshape(unsigned int windowWidth, unsigned int windowHeight);

void setVideoMode(unsigned int windowWidth, unsigned int windowHeight);

/** Nombre de bits par pixel de la fenêtre **/
static const unsigned int BIT_PER_PIXEL = 32;

/** Nombre minimal de millisecondes separant le rendu de deux images **/
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/** Nombre max de points dessines **/
static const unsigned int NB_MAX_PT = 50;

//void afficheImage(GLuint textureId, int image);

//Gluint creationTexture(char nomImage[]);

void ecrireTexte(float x, float y, void* font, const char* s);
#endif
