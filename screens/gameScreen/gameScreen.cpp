#include "gameScreen.h"

gameScreen::gameScreen()
{
    initPressedButtons();
}

void gameScreen::initPressedButtons() const
{

}

void gameScreen::onTick()
{
    screen::onTick();
}

void gameScreen::keyDown(event kE)
{
    screen::keyDown(kE);
}

void gameScreen::keyUp(event kE)
{
    screen::keyUp(kE);
}

void gameScreen::switchToGameOverScreen()
{
    switchTo=screen::GAME_OVER_SCREEN;
}

void gameScreen::switchToVictoryScreen()
{
    switchTo=screen::VICTORY_SCREEN;
}

/*void gameScreen::subToAtStart()
{
    newSub=screen::AT_START;
}

void gameScreen::subToAlphaDone()
{
    newSub=screen::ALPHA_DONE;
}

void gameScreen::subToHeightDone()
{
    newSub=screen::HEIGHT_DONE;
}

void gameScreen::subToEndScene()
{
    newSub=screen::END_SCENE;
}*/
