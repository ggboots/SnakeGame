#ifndef __SNAKE__
#define __SNAKE__
#include "Point2d.h"
#include "textpixels_enums.h"
using textpixels::Point2d;
using textpixels::Direction;

class Snake
{
public:

  short colour = 0x0;
  
  // Position and speed use data types/enums are defined in textpixels_enums.h
  Point2d location { 1,1 };
  int xSpeed = Direction::NONE;
  int ySpeed = Direction::NONE;

  
  

};



#endif

