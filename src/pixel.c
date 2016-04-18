#include "include/pixel.h"

Pixel createPixel(int red,int green,int blue,int alpha){
  Pixel pixels = malloc(sizeof(Pixel));
  pixels.r = red;
  pixels.g = green;
  pixels.b = blue;
  pixels.alpha = alpha;
  return pixels
}
