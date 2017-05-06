#include "field.h"
#include "../gameScreen.h"

const string field::BLANK="blank";
const string field::ROAD="road";
const string field::BARRACK="barrack";
const string field::VILLAGE="village";
const string field::STRONGHOLD="stronghold";



field::field(gameScreen* gS, coor origo)
: myGameScreen(gS), origo(origo), type(BLANK)
{
    gS->widgets.push_back(new lButton([this](){this->myGameScreen->fieldClicked(this);},origo,WIDTH,WIDTH));
}

field::~field()
{
    //dtor
}

void field::draw()
{
    drawRectangle(origo-makeCoor(WIDTH/2,WIDTH/2),origo+makeCoor(WIDTH/2,WIDTH/2));
    for (fieldObject* fO:myParts)
        fO->draw();
}

void field::addPart(string part)
{
    if (part==fieldObject::NORTH_ROAD)
    {
        myParts.push_back(new road(origo,road::NORTH));
        type=ROAD;
    }
    else if (part==fieldObject::SOUTH_ROAD)
    {
        myParts.push_back(new road(origo,road::SOUTH));
        type=ROAD;
    }
    else if (part==fieldObject::EAST_ROAD)
    {
        myParts.push_back(new road(origo,road::EAST));
        type=ROAD;
    }
    else if (part==fieldObject::WEST_ROAD)
    {
        myParts.push_back(new road(origo,road::WEST));
        type=ROAD;
    }
    else if (part==fieldObject::BARRACK)
    {
        myParts.push_back(new barrack(origo,myGameScreen->currentPlayer->name));
        type=BARRACK;
    }
    else if (part==fieldObject::VILLAGE)
    {
        myParts.push_back(new village(origo));
        type=VILLAGE;
    }
    else if (part==fieldObject::STRONGHOLD)
    {
        myParts.push_back(new stronghold(origo,myGameScreen->currentPlayer->name));
        type=STRONGHOLD;
    }
    else
        cout<<"NINCS ILYEN!!!";
}

bool field::hasPart(string part)
{
    for (fieldObject* fO:myParts)
        if (fO->getType()==part)
            return true;
    return false;
}

bool field::canAct(player* who)
{
    for (player* p:owners)
        if (p!=who)
            return false;
    return true;
}

bool field::canBuild(string part)
{
    if (type==BLANK)
        return true;
    else if (type==ROAD
             && (part==fieldObject::NORTH_ROAD || part==fieldObject::SOUTH_ROAD || part==fieldObject::EAST_ROAD || part==fieldObject::WEST_ROAD)
             && !hasPart(part))
        return true;
    return false;
}