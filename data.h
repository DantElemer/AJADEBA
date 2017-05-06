//There is nothing important here...






































#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "coor.h"


struct coor;

//COORDINATES
extern const int WINDOW_X; //width of the console
extern const int WINDOW_Y; //height of the console in general, but in the game, the height of playArea (console height-dashboard height)
extern const coor WINDOW_ORIGO; //...

extern int mouseX; //x coordinate of mouse
extern int mouseY; //y coordinate of mouse
extern coor mouse; //...

//KEYS

//FONT
extern int loadedFontSize;



#endif // DATA_H_INCLUDED
