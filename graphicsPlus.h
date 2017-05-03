//A set of useful functions (for graphics).

#ifndef GRAPHICSPLUS_H_INCLUDED
#define GRAPHICSPLUS_H_INCLUDED

#include "graphics.hpp"

#include "coor.h"
#include "randomFuncs.h"

#include <string>


extern int titleFontSize;
extern int titleFromWindow;

void clearScreen(coor uLC=makeCoor(0,0), coor dRC=WINDOW_ORIGO*2); //clears the given rectangle, the whole screen by default
void darkening(int rate=2); //a simple effect
void drawRectangle(coor upperLeftCorn,coor downerRightCorn, bool filled=false); //...
void drawCircle(coor origo, double radius, int accuracy=1000);//...
void setFont(int fontSize); //...
void lWriteText(coor startPoint, string texty, int lineLength, int fontSize=0); //prints @texty using multiple lines, its ULC is given (@startPoint), 0 fontSize means no font change, cannot handle "too long" words
void writeText(coor startPoint, string texty, int fontSize=0); //prints @texty, its ULC is given (@startPoint), 0 fontSize means no font change
void mWriteText(coor origo, string texty, int fontSize=0); //prints @texty, its middle is given (@origo), 0 fontSize means no font change
void printText(string texty, int fontSize=0); //no movement before printing
void addTitle(string title); //prints @title on the top of the screen (in the middle), it has two global parameters (line 9,10)
int countTextWidth(string texty, int fontSize=loadedFontSize);//...
int countTextHeight(string texty, int fontSize=loadedFontSize);//...
int countTextBaseline(string texty, int fontSize);//approximately
coor countTextMiddle(string texty, int fontSize=loadedFontSize); //more accurately counts the text's baseline's middle point
void generateCanvas(canvas &can, string fileName, bool blackAndWhite=false, bool transp=true); //width means how wide the pic can be if 0, no scaling will be done can't create greater than that
#endif // GRAPHICSPLUS_H_INCLUDED
