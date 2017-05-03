#include "indicator.h"

indicator::indicator(coor uLC, coor dLC, string texty, int fSize)
: widgetBase(uLC,dLC), texty(texty), fontSize(fSize)
{
    draw();
}

void indicator::draw()
{
    drawRectangle(upperLeftCorner,downerRightCorner);
    writeText(upperLeftCorner+makeCoor(5,height/2-countTextBaseline(texty, fontSize)),texty,fontSize);
}

void indicator::redraw()
{
    widgetBase::redraw();
}

void indicator::update()
{
    redraw();
}
