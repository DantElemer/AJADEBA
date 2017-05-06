#include "gameScreen.h"

gameScreen::gameScreen()
{
    initPressedButtons();

    for (int i=2;i<10;i++)
    {
        fields.push_back(new field(this,makeCoor(i*field::WIDTH,100)));
    }
}

void gameScreen::initPressedButtons() const
{

}

void gameScreen::onTick()
{
    screen::onTick();
    for (field* f:fields)
        f->draw();
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
