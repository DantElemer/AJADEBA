#include "confirmExitScreen.h"

confirmExitScreen::confirmExitScreen()
{
    darkening();
    clearScreen(WINDOW_ORIGO-makeCoor(200,150),WINDOW_ORIGO+makeCoor(200,150));
    drawRectangle(WINDOW_ORIGO-makeCoor(200,150),WINDOW_ORIGO+makeCoor(200,150));
    mWriteText(WINDOW_ORIGO-makeCoor(0,80),"Are you sure you want to exit?",25);
    widgetBase* exitButton=new button((vFunctionCall)exitRequest, makeCoor(WINDOW_X/2+100,370),150,50,"Yes :(",20);
    widgets.push_back(exitButton);
    widgetBase* nopeButton=new button((vFunctionCall)terminateSub, makeCoor(WINDOW_X/2-100,370),150,50,"No!",20);
    widgets.push_back(nopeButton);
}

void confirmExitScreen::onTick()
{
    screen::onTick();
    double xDist=(double)(WINDOW_X/2-100)-(double)mouseX;
    double yDist=370.0-(double)mouseY;
    double totDist=sqrt(xDist*xDist+yDist*yDist);
    double speed=5.0;
    if (totDist>speed)
        gout.movemouse(mouseX+speed*xDist/totDist,mouseY+speed*yDist/totDist);
}
