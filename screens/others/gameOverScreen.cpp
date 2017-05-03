#include "gameOverScreen.h"

gameOverScreen::gameOverScreen()
{
    widgetBase* playButton=new button((vFunctionCall)switchToGameScreen, WINDOW_ORIGO,300.0,100.0,"Try again!",50);
    widgets.push_back(playButton);
    widgetBase* menuButton=new button((vFunctionCall)switchToMenuScreen, WINDOW_ORIGO+makeCoor(0,120),200.0,80.0,"Menu",40);
    widgets.push_back(menuButton);
    widgetBase* howToPlayButton=new button((vFunctionCall)subToHowToPlayScreen, WINDOW_ORIGO+makeCoor(0,220),200.0,80.0,"Help",40);
    widgets.push_back(howToPlayButton);

    //setMaxValues(-1);
    draw();
}

void gameOverScreen::draw()
{
    clearScreen();
    addTitle("Test failed");
    mWriteText(makeCoor(WINDOW_X/2,WINDOW_Y-30),"(Press any key to restart.)",20);
    //mWriteText(makeCoor(WINDOW_X/2,WINDOW_Y/2-100),"Level: "+numToString(skillfulness),30);
}

void gameOverScreen::onTick()
{
    screen::onTick();
}

void gameOverScreen::keyDown(event kE)
{
    screen::keyDown(kE);
    if (kE.keycode!=key_escape)
        switchToGameScreen();
}
