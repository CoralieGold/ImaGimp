#include "include/dessin.h"

void reshape(unsigned int windowWidth, unsigned int windowHeight)
{
  glViewport(0, 0, windowWidth, windowHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, windowWidth, 0, windowHeight);
}

void setVideoMode(unsigned int windowWidth, unsigned int windowHeight)
{
  if(NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE))
  {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
}

/** Ecriture d'un texte sur l'ecran **/
void ecrireTexte(float x, float y, void* font, const char* s)
{
  glColor3f(1, 1, 1);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glRasterPos2f(x, y);
  while(*s)
  {
    glutBitmapCharacter(font, *s);
    s++;
  }
}
