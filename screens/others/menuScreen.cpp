#include "menuScreen.h"

menuScreen::menuScreen()
{
     int buttonWidth=200;
    int buttonHeight=80;
    int startY=200;
    //widgetBase* playButton=new button((vFunctionCall)switchToDifficultySettingScreen, makeCoor(WINDOW_X/2,240),buttonWidth,buttonHeight/*makeCoor((windowX-buttonWidth)/2,200),makeCoor((windowX+buttonWidth)/2,200+buttonHeight)*/,"Play");
    //widgetBase* playButton=new button((vFunctionCall)switchToGameScreen, makeCoor(WINDOW_X/2,240),buttonWidth,buttonHeight,"Play");

    widgets.push_back(new lButton([](){screen::switchTo=screen::SETTINGS_SCREEN;},makeCoor(WINDOW_X/2,240),buttonWidth,buttonHeight,"Play"));

    widgetBase* howToPlayButton=new button((vFunctionCall)subToHowToPlayScreen, makeCoor(WINDOW_X/2,390),buttonWidth,buttonHeight/*makeCoor((windowX-buttonWidth)/2,350),makeCoor((windowX+buttonWidth)/2,350+buttonHeight)*/,"Help");
    widgets.push_back(howToPlayButton);
    //widgetBase* exitButton=new button((vFunctionCall)exitRequest, makeCoor(WINDOW_X/2,540),buttonWidth,buttonHeight/*makeCoor((windowX-buttonWidth)/2,500),makeCoor((windowX+buttonWidth)/2,500+buttonHeight)*/,"Exit");
    //widgets.push_back(exitButton);
    widgets.push_back(new lButton([](){switchTo=screen::MAP_EDITOR;}, makeCoor(WINDOW_X/2,540),buttonWidth,buttonHeight,"Editor"));

    draw();
}

void menuScreen::draw()
{
    clearScreen();
    drawFatLine(makeCoor(560,20), makeCoor(550,40),4); //ékezet...
    addTitle("AJADEBA");
    mWriteText(WINDOW_ORIGO-makeCoor(0,150),"(A Jatek, Amit Domonkos Es Balazs Alkotott)",12);
    //ékezetek -_-
    drawLine(makeCoor(405,143),makeCoor(404,145));
    drawLine(makeCoor(415,143),makeCoor(414,145));
    drawLine(makeCoor(521,140),makeCoor(520,142));
    drawLine(makeCoor(555,143),makeCoor(554,145));

    screen::draw();
}

void menuScreen::onTick()
{
    screen::onTick();
}


