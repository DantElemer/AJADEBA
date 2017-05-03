#include "reachedLED.h"
#include <fstream>

reachedLED::reachedLED(coor upperLeftCorner, double &value, double aimValue, string minMaxAbs)
: widgetBase(upperLeftCorner,upperLeftCorner+makeCoor(15,15)), value(&value), minMaxAbs(minMaxAbs), AIM_VALUE(aimValue)
{
    generateCanvas(onPic, "pics/led_on.kep"/*"pics/flell.kep"*/);
    generateCanvas(offPic, "pics/led_off.kep"/*"pics/flugi2.kep"*/);
    draw();
}

reachedLED::~reachedLED()
{
    //dtor
}

void reachedLED::check()
{
    if (minMaxAbs=="min"&&*value>=AIM_VALUE)
        reached=true;
    else if (minMaxAbs=="max"&&*value<=AIM_VALUE)
        reached=true;
    else if (minMaxAbs=="abs"&&fabs(*value)<=AIM_VALUE)
        reached=true;
    else
        reached=false;
}

void reachedLED::update()
{
    check();
    redraw();
}

void reachedLED::draw()
{
    if (reached)
        gout<<stamp(onPic,upperLeftCorner.X,upperLeftCorner.Y);
    else
        gout<<stamp(offPic,upperLeftCorner.X,upperLeftCorner.Y);
}
