#include "howToPlayScreen.h"

howToPlayScreen::howToPlayScreen()
{
    clearScreen();
    widgetBase* backButton=new button ((vFunctionCall)terminateSub, makeCoor(30,WINDOW_Y-80),makeCoor(150,WINDOW_Y-30),"Back",30);
    widgets.push_back(backButton);
    /*widgetBase* playButton= new button((vFunctionCall)switchToGameScreen, makeCoor(WINDOW_X-150,WINDOW_Y-80),makeCoor(WINDOW_X-30,WINDOW_Y-30),"Play",30);
    widgets.push_back(playButton);*/

    draw();
}

void howToPlayScreen::draw()
{
    clearScreen();
    addTitle("How to play");
    writeText(makeCoor(50,150),"Aim:",40);
    writeText(makeCoor(100,210),"Make successfull tests. First lift the helicoffer up to test height, then test rotation.",20);
    writeText(makeCoor(100,240),"After that, land safely: make sure all the LEDs glow when you land.",20);
    writeText(makeCoor(50,290),"Controls:",40);
    writeText(makeCoor(100,350),"Up/Down Arrow: Increase/decrease rotor's RPM.",20);
    writeText(makeCoor(100,380),"Left/Right Arrow: Rotate helicopter.",20);
    writeText(makeCoor(50,430),"Recommended music:",40);
    writeText(makeCoor(100,490),"Helikoffer (https://www.youtube.com/watch?v=HNjWhBa1_qU)",20);
}//Make successfull tests. First lift up your helicopter to test height, then test if the helikoffer can rotate.

void howToPlayScreen::onTick()
{
    screen::onTick();
}
