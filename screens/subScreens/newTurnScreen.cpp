#include "newTurnScreen.h"
#include "../gameScreen/gameScreen.h"

newTurnScreen::newTurnScreen(gameScreen* gS)
: myGS(gS)
{
    widgets.push_back(new button((vFunctionCall)terminateSub,WINDOW_ORIGO,100,40,"Ok",30));
    draw();
}

void newTurnScreen::draw()
{
    clearScreen();
    mWriteText(WINDOW_ORIGO-makeCoor(0,50),myGS->currentPlayer->name+"'s turn",30);
    screen::draw();
}
