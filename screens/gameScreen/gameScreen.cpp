#include "gameScreen.h"
#include <cstdlib>

gameScreen::gameScreen()
{
    initPressedButtons();
    srand(time(NULL));
    for (int j=1;j<10;j++)
    {
        vector<field*> newRow;
        for (int i=3;i<10;i++)
        {
            field* newField=new field(this,makeCoor(i*field::WIDTH,j*field::WIDTH));
            newRow.push_back(newField);
            if (rand()%10<2)
                newField->addPart(fieldObject::NORTH_ROAD);
            if (rand()%10<2)
                newField->addPart(fieldObject::SOUTH_ROAD);
            if (rand()%10<2)
                newField->addPart(fieldObject::WEST_ROAD);
            if (rand()%10<2)
                newField->addPart(fieldObject::EAST_ROAD);
            if (newField->getType()==field::BLANK&&rand()%10<3)
                newField->addPart(fieldObject::VILLAGE);
            if (newField->getType()==field::BLANK&&rand()%10<3)
                newField->addPart(fieldObject::STRONGHOLD);
            if (newField->getType()==field::BLANK)
                newField->addPart(fieldObject::BARRACK);
        }
        fields.push_back(newRow);
    }

}

void gameScreen::initPressedButtons() const
{

}

void gameScreen::fieldClicked(field* f)
{
    cout<<f->getType();
}

void gameScreen::onTick()
{
    screen::onTick();
    for (vector<field*> fRow:fields)
        for (field* f:fRow)
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
