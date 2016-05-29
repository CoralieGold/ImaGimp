#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/pixel.h"
#include "include/calque.h"
#include "include/lut.h"
#include "include/fichier.h"
#include "include/dessin.h"

int main(int argc, char** argv)
{
  // Vérification des paramètres de départ
	if(argc < 5 && argc%2 == 0)
  {
		printf("Vous devez donner un paramètre pour chaque code LUT.\n");
		return 1;
	}

	Calque * image = lireImage(argv[1]);

  // Vérification de la taille de l'image
	if(image->hauteur * image->largeur >= 490000)
  {
		printf("L'image est trop grande pour être traitée. \n");
		return 1;
	}
	
	char nomImageFinale[100];
	char dossier[100];
	memset(nomImageFinale, 0, sizeof(nomImageFinale));
	memset(dossier, 0, sizeof(dossier));
	strcat(nomImageFinale, argv[2]);
	strcat(nomImageFinale, ".ppm");
	strcat(dossier, "images/");
	strcat(dossier, nomImageFinale);
 
	char codeLut[9];
	float parametre;	


	/*** TRAITEMENT ***/

	printf("Début du traitement.\n");
	int i = 3;
	while(argc > i)
  {
		
		strcpy(codeLut,argv[i]);
		parametre = atof(argv[i+1]);

		addCalque(image);

    // Cas d'une modification de calque
		if(!strcmp(codeLut, "SEPIA") || !strcmp(codeLut, "NB") || !strcmp(codeLut, "ROUGE") || !strcmp(codeLut, "VERT") || !strcmp(codeLut, "BLEU") || !strcmp(codeLut, "JAUNE") || !strcmp(codeLut, "MAGENTA") || !strcmp(codeLut, "CYAN"))
    {
			if (!strcmp(codeLut, "SEPIA")) sepia(image);
			else if (!strcmp(codeLut, "NB")) nb(image);
			else if (!strcmp(codeLut, "ROUGE")) rouge(image);
			else if (!strcmp(codeLut, "VERT")) vert(image);
			else if (!strcmp(codeLut, "BLEU")) bleu(image);
			else if (!strcmp(codeLut, "CYAN")) cyan(image);
			else if (!strcmp(codeLut, "MAGENTA")) magenta(image);
			else if (!strcmp(codeLut, "JAUNE")) jaune(image);
		}
		else
    {
      // Cas d'un ajout de lut
			if(!strcmp(codeLut, "ADDLUM"))
			image->listLUT = addLum(parametre);
			else if (!strcmp(codeLut, "DIMLUM")) image->listLUT = dimLum(parametre);
			else if (!strcmp(codeLut, "DIMCON")) image->listLUT = dimCon(parametre);
			else if (!strcmp(codeLut, "ADDCON")) image->listLUT = addCon(parametre);
			else if (!strcmp(codeLut, "INVERT")) image->listLUT = invert();
			appliquerLut(image);
		}
		i = i + 2;
	}

	fusionCalques(image);
	printf("Fin du traitement. \n");

	ecritureImage(image, dossier);


	/*** IHM ***/

	glutInit(&argc, argv);

	unsigned int windowWidth  = 800;
	unsigned int windowHeight = 500;

	// Initialisation de la SDL
	if(-1 == SDL_Init(SDL_INIT_VIDEO))
  {
	fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
	    return EXIT_FAILURE;
	}

  // Ouverture d'une fenetre et creation d'un contexte OpenGL
  setVideoMode(windowWidth, windowHeight);
  reshape(windowWidth,windowHeight);
  
  // Titre de la fenêtre
  SDL_WM_SetCaption("ImaGimp", NULL);

	/** Creation d'une texture pour l'image de base **/

  SDL_Surface* imageDeBase = IMG_Load(argv[1]);
  if(imageDeBase == NULL)
  {
    fprintf(stderr, "Impossible de charger l'image %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  GLuint textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  GLenum format;
  switch(imageDeBase->format->BytesPerPixel)
  {
    case 1:
    format = GL_RED;
    break;
    case 3:
    format = GL_RGB;
    break;
    case 4:
    format = GL_RGBA;
    break;
    default:
    fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", argv[1]);
    return EXIT_FAILURE;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageDeBase->w, imageDeBase->h, 0, format, GL_UNSIGNED_BYTE, imageDeBase->pixels);

  glBindTexture(GL_TEXTURE_2D, 0);

  SDL_FreeSurface(imageDeBase);

  /** Creation d'une texture pour l'image finale **/
  SDL_Surface* imageFinale = IMG_Load(dossier);
  if(imageDeBase == NULL)
  {
    fprintf(stderr, "Impossible de charger l'image %s\n", dossier);
    return EXIT_FAILURE;
  }

  GLuint textureId2;
  glGenTextures(2, &textureId2);
  glBindTexture(GL_TEXTURE_2D, textureId2);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  GLenum format2;
  switch(imageFinale->format->BytesPerPixel)
  {
    case 1:
    format2 = GL_RED;
    break;
    case 3:
    format2 = GL_RGB;
    break;
    case 4:
    format2 = GL_RGBA;
    break;
    default:
    fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", dossier);
    return EXIT_FAILURE;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageFinale->w, imageFinale->h, 0, format2, GL_UNSIGNED_BYTE, imageFinale->pixels);

  glBindTexture(GL_TEXTURE_2D, 0);

  SDL_FreeSurface(imageFinale);

  // Boucle d'affichage
  printf("Affichage du résultat : \n");
  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();
    SDL_Delay(100);
    
    ecrireTexte(10, windowHeight - 60, GLUT_BITMAP_HELVETICA_18, argv[1]);
    ecrireTexte(windowWidth/2 + 10, windowHeight - 60, GLUT_BITMAP_HELVETICA_18, dossier);

    /** Affichage image de base **/

    // on affiche une texture 2D ici
    glEnable(GL_TEXTURE_2D);
    // à partir de maintenant, on parle de cette texture
    glBindTexture(GL_TEXTURE_2D, textureId);
    glBegin(GL_QUADS);
    glColor3f(1,1,1);

    glTexCoord2f(0, 1);
    glVertex2f(0, 0);

    glTexCoord2f(1, 1);
    glVertex2f(windowWidth/2, 0);

    glTexCoord2f(1, 0);
    glVertex2f(windowWidth/2, windowHeight-100);

    glTexCoord2f(0, 0);
    glVertex2f(0, windowHeight-100);
    glEnd();

    // on a fini avec la texture
    glBindTexture(GL_TEXTURE_2D, 0);
    // on affiche plus de texture
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /** Affichage image finale **/

    // on affiche une texture 2D ici
    glEnable(GL_TEXTURE_2D);
    // à partir de maintenant, on parle de cette texture
    glBindTexture(GL_TEXTURE_2D, textureId2);
    glBegin(GL_QUADS);
    glColor3f(1,1,1);

    glTexCoord2f(0, 1);
    glVertex2f(windowWidth/2, 0);

    glTexCoord2f(1, 1);
    glVertex2f(windowWidth, 0);

    glTexCoord2f(1, 0);
    glVertex2f(windowWidth, windowHeight-100);

    glTexCoord2f(0, 0);
    glVertex2f(windowWidth/2, windowHeight-100);
    glEnd();

    // on a fini avec la texture
    glBindTexture(GL_TEXTURE_2D, 0);
    // on affiche plus de texture
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    // Echange du front et du back buffer //
    SDL_GL_SwapBuffers();

    // Boucle traitant les evenements
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      // L'utilisateur ferme la fenetre //
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }
      switch(e.type) {
        case SDL_VIDEORESIZE:
        windowWidth  = e.resize.w;
        windowHeight = e.resize.h;
        setVideoMode(windowWidth, windowHeight);
        reshape(windowWidth, windowHeight);
        break;

        default:
        break;
      }
    }

    Uint32 elapsedTime = SDL_GetTicks() - startTime;

    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  glDeleteTextures(1, &textureId);
  glDeleteTextures(2, &textureId2);
  SDL_Quit();

	return 0;
}
