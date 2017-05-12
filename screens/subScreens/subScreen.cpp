#include "subScreen.h"

const string subScreen::CANCEL="cancel";

subScreen::subScreen()
{

}

void subScreen::terminateSub()
{
    switchTo=TERMINATED;
}

void subScreen::addFrame(coor uLC, coor dRC)
{
    drawRectangle(uLC,dRC);
    drawRectangle(uLC+makeCoor(3,3),dRC-makeCoor(3,3));
}
