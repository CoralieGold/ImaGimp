#include <stdio.h>
#include <stdlib.h>

typedef struct pixel{
	int r;
  int g;
  int b;
  int alpha;
}Pixel;

Pixel createPixel(int r,int g,int b,int alpha);
