#include "gameScreen.h"
#include "../subScreens/subScreen.h"

#include <cstdlib>


gameScreen::gameScreen()
{
    initPressedButtons();

    srand(time(NULL));
    players.push_back(new player("Player 1","Ancient 1"));
    players.push_back(new player("Player 2","Ancient 2"));
    currentPlayer=players[0];
    for (int j=1;j<10;j++) //some fields
    {
        vector<field*> newRow;
        for (int i=3;i<10;i++)
        {
            field* newField=new field(this,makeCoor(i*field::WIDTH,j*field::WIDTH));
            newRow.push_back(newField);
            if (newField->getType()==field::BLANK&&rand()%10<1)
                newField->addPart(fieldObject::VILLAGE);
            /*if (rand()%10<2)
                newField->addPart(fieldObject::NORTH_ROAD);
            if (rand()%10<2)
                newField->addPart(fieldObject::SOUTH_ROAD);
            if (rand()%10<2)
                newField->addPart(fieldObject::WEST_ROAD);
            if (rand()%10<2)
                newField->addPart(fieldObject::EAST_ROAD);
            if (newField->getType()==field::BLANK&&rand()%10<1)
                newField->addPart(fieldObject::VILLAGE);
            if (newField->getType()==field::BLANK&&rand()%10<1)
                newField->addPart(fieldObject::STRONGHOLD);
            if (newField->getType()==field::BLANK&&rand()%10<1)
                newField->addPart(fieldObject::BARRACK);*/
        }
        fields.push_back(newRow);
    }
    fields[3][0]->addPart(fieldObject::STRONGHOLD);
    fields[3][0]->activateStronghold(currentPlayer);
    fields[4][0]->addPart(fieldObject::BARRACK);
    nextPlayer();
    fields[3][6]->addPart(fieldObject::STRONGHOLD);
    fields[3][6]->activateStronghold(currentPlayer);
    fields[4][6]->addPart(fieldObject::BARRACK);
    nextPlayer();
}

void gameScreen::initPressedButtons() const
{

}

void gameScreen::fieldClicked(field* f)
{
    cout<<f->getType()<<endl;
    selectedField=f;
    if (f->canAct(currentPlayer))
    {
        subToBuildChooserScreen(); //open build options
    }
    else
        cout<<"enemy territory";
}

void gameScreen::build()
{
    selectedField->addPart(whatToBuild);
    if (whatToBuild!=subScreen::CANCEL) //so he built something
    {
        if (selectedField->getType()==field::ROAD)
            currentPlayer->steps--;
        else
            currentPlayer->steps=0;

        if (currentPlayer->steps==0)
            currentPlayer->finishedTurn=true;
    }
}

void gameScreen::nextPlayer()
{
    bool newTurn=true;
    for (int i=players.size()-2;i>=0;i--)
        if (players[i]==currentPlayer)
        {
            currentPlayer=players[i+1];
            newTurn=false;
        }
    if (newTurn)
    {
        currentPlayer=players[0];
    }
    currentPlayer->finishedTurn=false;
    currentPlayer->steps=currentPlayer->MAX_STEPS;
    cout<<"==========================================================\n"<<currentPlayer->name<<"\n";
}

void gameScreen::onTick()
{
    screen::onTick();
    for (vector<field*> fRow:fields)
        for (field* f:fRow)
            f->draw();
    if (currentPlayer->finishedTurn)
        nextPlayer();
    if (justBuilt)
    {
        build();
        justBuilt=false;
    }
}

void gameScreen::keyDown(event kE)
{
    screen::keyDown(kE);
    if (kE.keycode=='n')
        currentPlayer->finishedTurn=true;
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

void gameScreen::subToBuildChooserScreen()
{
    newSub=screen::BUILD_CHOOSER_SCREEN;
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
