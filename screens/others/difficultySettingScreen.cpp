#include "difficultySettingScreen.h"

difficultySettingScreen::difficultySettingScreen()
{
    widgetBase* easyButton=new button((vFunctionCall)startEasyGame, WINDOW_ORIGO+makeCoor(0,-100),200.0,70.0,"Easy",30);
    widgets.push_back(easyButton);
    widgetBase* normalButton=new button((vFunctionCall)startNormalGame, WINDOW_ORIGO+makeCoor(0,50),200.0,70.0,"Normal",30);
    widgets.push_back(normalButton);
    widgetBase* hardButton=new button((vFunctionCall)startHardGame, WINDOW_ORIGO+makeCoor(0,200),200.0,70.0,"Hard",30);
    widgets.push_back(hardButton);

    draw();
}

void difficultySettingScreen::draw()
{
    clearScreen();
    addTitle("Difficulty");
}

void difficultySettingScreen::startEasyGame()
{
    /*skillfulness=0;
    setMaxValues(0);
    levelToReach=5;*/
    switchToGameScreen();
}

void difficultySettingScreen::startNormalGame()
{
    /*skillfulness=3;
    setMaxValues(0);
    levelToReach=8;*/
    switchToGameScreen();
}

void difficultySettingScreen::startHardGame()
{
    /*skillfulness=6;
    setMaxValues(0);
    levelToReach=10;*/
    switchToGameScreen();
}




