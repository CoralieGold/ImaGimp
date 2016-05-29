#include "include/pixel.h"

// Creation d'un pixel
Pixel createPixel(int red,int green,int blue,int alpha)
{
  Pixel pixels;
  pixels.r = red;
  pixels.g = green;
  pixels.b = blue;
  pixels.alpha = alpha;
  return pixels;
}
