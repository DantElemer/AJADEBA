#include "helpBase.h"

helpBase::helpBase()
{
    //ctor
}

helpBase::~helpBase()
{
    //dtor
}

void helpBase::draw()
{
    clearScreen();
    height=0;
    screen::draw();
}

void helpBase::addParagraph(string par)
{
    lines=lWriteText(startPoint+makeCoor(0,height), par,WINDOW_X-2*startPoint.X,fSize);
    height+=lines*countTextHeight("I",fSize)+bekezdDist;
}
