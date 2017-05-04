#include "lButton.h"

lButton::lButton(function<void()> fire, coor origo, int width, int height, string texty, int fontSize)
:button(NULL, origo,width,height,texty,fontSize), fire(fire)
{
    //ctor
}

lButton::~lButton()
{
    //dtor
}

void lButton::fireFunction()
{
    fire();
}
