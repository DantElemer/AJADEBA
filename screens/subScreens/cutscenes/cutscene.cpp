#include "cutscene.h"

cutscene::cutscene()
{
    draw();
    /*widgetBase* terminateButton=new button((vFunctionCall)terminateSub,WINDOW_ORIGO+makeCoor(160,-110),50,50,"X");
    widgets.push_back(terminateButton);*/
}

void cutscene::draw()
{
    darkening(2);
    clearScreen(WINDOW_ORIGO-makeCoor(200,150),WINDOW_ORIGO+makeCoor(200,150));
    drawRectangle(WINDOW_ORIGO-makeCoor(200,150),WINDOW_ORIGO+makeCoor(200,150));
    drawRectangle(WINDOW_ORIGO-makeCoor(203,153),WINDOW_ORIGO+makeCoor(203,153));
    drawRectangle(WINDOW_ORIGO+makeCoor(-100-95/2-5,-130/2-5+30),WINDOW_ORIGO+makeCoor(-100+95/2+5,130/2+5+30));
    mWriteText(WINDOW_ORIGO+makeCoor(0,130),"Press any key to continue",15);
}

void cutscene::addTitle(string title)
{
    writeText(WINDOW_ORIGO-makeCoor(190,140),title,40);
}

void cutscene::generatePics()
{

}

void cutscene::keyDown(event kE)
{
    screen::keyDown(kE);
    if (kE.keycode!=key_escape)
        terminateSub();
}
