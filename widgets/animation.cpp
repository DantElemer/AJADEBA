#include "animation.h"

animation::animation(coor uLC, coor dRC, vector<canvas> pics, int frameTime)
: widgetBase(uLC,dRC), pics(pics), frameTime(frameTime), fTCounter(0), currFrame(0)
{

}

void animation::update()
{
    fTCounter++;
    if (fTCounter>=frameTime)
    {
        fTCounter=0;
        currFrame++;
        if (currFrame>=pics.size())
            currFrame=0;
        redraw();
    }
}

void animation::draw()
{
    gout<<stamp(pics[currFrame],upperLeftCorner.X,upperLeftCorner.Y);
}


