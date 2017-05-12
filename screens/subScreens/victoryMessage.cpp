#include "victoryMessage.h"
#include "../gameScreen/gameScreen.h"

victoryMessage::victoryMessage(gameScreen* gS)
: myGS(gS)
{
    int wid=140;
    int hei=40;
    widgets.push_back(new lButton([](){switchTo=screen::GAME_SCREEN;},WINDOW_ORIGO-makeCoor(0,30),wid,hei,"Restart",30));
    widgets.push_back(new lButton([](){switchTo=screen::MENU_SCREEN;},WINDOW_ORIGO+makeCoor(0,40),wid,hei,"Menu",30));
    draw();
}

void victoryMessage::draw()
{
    darkening();
    coor uLC=WINDOW_ORIGO-makeCoor(110,150);
    coor dRC=WINDOW_ORIGO+makeCoor(110,130);
    clearScreen(uLC,dRC);
    addFrame(uLC,dRC);
    mWriteText(WINDOW_ORIGO-makeCoor(0,100),myGS->currentPlayer->name+" won this time.");
}

