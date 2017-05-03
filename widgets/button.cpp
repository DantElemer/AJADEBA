#include "button.h"
using namespace genv;

button::button(vFunctionCall fire, coor upperLeftCorn, coor downerRightCorn, string texty, int fontSize)
: widgetBase(upperLeftCorn, downerRightCorn),
funcToStart(fire),
myText(texty),
fontSize(fontSize)
{

}

button::button(vFunctionCall fire, coor origo, double width, double height, string texty, int fontSize)
: widgetBase(origo-makeCoor(width,height)/2, origo+makeCoor(width,height)/2),
funcToStart(fire),
myText(texty),
fontSize(fontSize)
{

}

void button::fireFunction()
{
    funcToStart();
}

void button::check()
{
    if (mouse.inRect(upperLeftCorner,downerRightCorner))
        mouseAbove=true;
    else
        mouseAbove=false;

}

void button::growEffect()
{
    if (currentTimes<MAX_TIMES)
    {
        clearWid();
        upperLeftCorner.growPoint(origo,GROW_RATE);
        downerRightCorner.growPoint(origo,GROW_RATE);
        width=downerRightCorner.X-upperLeftCorner.X;
        height=downerRightCorner.Y-upperLeftCorner.Y;
        currentTimes*=GROW_RATE;
    }
}

void button::nullGrowEffect()
{
    if (currentTimes!=1.0)
    {
        clearWid();
        upperLeftCorner.growPoint(origo,1.0/currentTimes);
        downerRightCorner.growPoint(origo,1.0/currentTimes);
        width=downerRightCorner.X-upperLeftCorner.X;
        height=downerRightCorner.Y-upperLeftCorner.Y;
        currentTimes=1.0;
    }
}

void button::draw()
{
    setFont(fontSize);//for correctly counting text-startPoint

    if (mouseAbove)
    {
        //growEffect();
        for (int i=1;i<borderDiff;i++)
            drawRectangle(upperLeftCorner+i,downerRightCorner-i);
        if (mouseChosen)
            drawRectangle(upperLeftCorner+7,downerRightCorner-7);
    }
    else
    {
        nullGrowEffect();
    }
    drawRectangle(upperLeftCorner,downerRightCorner);
    drawRectangle(upperLeftCorner+borderDiff,downerRightCorner-borderDiff);

    if (hasCanvas)
        gout<<stamp(myPic,upperLeftCorner.X,upperLeftCorner.Y);
    if (myText.length()>0)
        mWriteText((upperLeftCorner+downerRightCorner)/2,myText,fontSize);
}

void button::mouseUp()
{
    if (mouseChosen&&mouseAbove)
        fireFunction();
    mouseChosen=false;
}

void button::mouseDown()
{
    if (mouseAbove)
        mouseChosen=true;
}

void button::redraw()
{
    widgetBase::redraw();
}

void button::update()
{
    check();
    redraw();
}

void button::addText(string text)
{
    myText=text;
}

void button::addCanvas(string picName)
{
    hasCanvas=true;
    generateCanvas(myPic,picName);
}
