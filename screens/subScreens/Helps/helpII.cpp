#include "helpII.h"

helpII::helpII()
{
    widgetBase* backButton=new button ((vFunctionCall)terminateSub, makeCoor(30,WINDOW_Y-80),makeCoor(150,WINDOW_Y-30),"Back",30);
    widgets.push_back(backButton);
    //widgets.push_back(new lButton([](){newSub=screen::HELPII;},makeCoor(WINDOW_X-100,WINDOW_Y-55),120,50,"Next"));

    draw();
}

void helpII::draw()
{
    clearScreen();
    addTitle("How to play II");
}

