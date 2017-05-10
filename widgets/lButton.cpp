#include "lButton.h"

lButton::lButton(function<void()> fire, coor origo, int width, int height, string texty, int fontSize, bool pSelfClear)
:button(NULL, origo,width,height,texty,fontSize), fire(fire)
{
    selfClear=pSelfClear;
}

lButton::~lButton()
{
    //dtor
}

void lButton::fireFunction()
{
    fire();
}
