#include "PonyScreen.h"

pony::pony(coor origo)
: MAX_SCALE(1+rand()%2), pic("pics/csillarmika.kep", origo), SCALE_SPEED((double)(6+rand()%8)/100.0)
{
    pic.setScaleX(MIN_SCALE);
    pic.setScaleY(MIN_SCALE);
}

bool pony::scaleYourself()
{
    if (growing)
    {
        double newScale=pic.getScaleX()+SCALE_SPEED;
        if (newScale>=MAX_SCALE)
            growing=false;
        else
        {
            pic.setScaleX(newScale);
            pic.setScaleY(newScale);
        }
    }
    else
    {
        double newScale=pic.getScaleX()-SCALE_SPEED;
        if (newScale<MIN_SCALE)
            return false;
        else
        {
            pic.setScaleX(newScale);
            pic.setScaleY(newScale);
        }
    }
    pic.draw();
    return true;
}

PonyScreen::PonyScreen()
{
    clearScreen();
    srand(time(NULL));
}

void PonyScreen::onTick()
{
    clearScreen();
    screen::onTick();
    mWriteText(WINDOW_ORIGO-makeCoor(0,250),"Click!", 50);
    for (int i=ponies.size()-1;i>=0;i--)
        if (!ponies[i].scaleYourself())
            ponies.erase(ponies.begin()+i,ponies.begin()+i+1);
}

void PonyScreen::keyDown(event kE)
{
    if (kE.keycode='q')
        terminateSub();
}

void PonyScreen::mouseUp(event mE)
{
    screen::mouseUp(mE);
    if (ponies.size()==0) //for more pony, it crashes sometimes :( don't have time to debug it :(
    {
        pony newPony(mouse);
        ponies.push_back(newPony);
    }
}
