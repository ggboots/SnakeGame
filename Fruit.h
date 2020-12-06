#ifndef __FRUIT__
#define __FRUIT__
#include "Point2d.h"
#include "textpixels_enums.h"
using textpixels::Point2d;
using namespace textpixels;

class Fruit
{
// makes it public for project
public:

  short colour = 0x0;
  wchar_t symbol = Pixel::PIXEL_SOLID; 
 
 
  // Position and speed use data types/enums are defined in textpixels_enums.h
  Point2d location { 1,1 }; //x and y location
};

#endif

