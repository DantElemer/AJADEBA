#include "victoryScreen.h"

victoryScreen::victoryScreen()
{
    widgetBase* playButton=new button((vFunctionCall)switchToGameScreen, WINDOW_ORIGO,300.0,100.0,"Next level",50);
    widgets.push_back(playButton);
    widgetBase* menuButton=new button((vFunctionCall)switchToMenuScreen, WINDOW_ORIGO+makeCoor(0,120),200.0,80.0,"Menu",40);
    widgets.push_back(menuButton);
    draw();
}

void victoryScreen::draw()
{
    clearScreen();
    addTitle("Victory!");
    mWriteText(makeCoor(WINDOW_X/2,WINDOW_Y-30),"(Press any key to start next level.)",20);
}

void victoryScreen::onTick()
{
    screen::onTick();
}

void victoryScreen::keyDown(event kE)
{
    screen::keyDown(kE);
    if (kE.keycode!=key_escape)
        switchToGameScreen();
}
