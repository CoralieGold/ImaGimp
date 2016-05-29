#ifndef PIXEL_H_
#define PIXEL_H_

#include <stdio.h>
#include <stdlib.h>

/** Structure Pixel **/
typedef struct pixel{
    int r;
  int g;
  int b;
  int alpha;
}Pixel;

// Creation d'un pixel
Pixel createPixel(int r,int g,int b,int alpha);

#endif