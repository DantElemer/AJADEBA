#include "field.h"
#include "../gameScreen.h"

const string field::BLANK="blank";
const string field::ROAD="road";
const string field::BARRACK="barrack";
const string field::VILLAGE="village";
const string field::STRONGHOLD="stronghold";
const string field::MOUNTAIN="mountain";


field::field(gameScreen* gS, coor coordinate)
: myGameScreen(gS), coordinate(coordinate), type(BLANK), origo(coordinate*WIDTH+gS->mapOffset)
{
    gS->widgets.push_back(new lButton([this](){this->myGameScreen->fieldClicked(this);},origo,WIDTH,WIDTH,"",0,false));
}

field::~field()
{
    //dtor
}

void field::draw()
{
    //drawRectangle(origo-makeCoor(WIDTH/2,WIDTH/2),origo+makeCoor(WIDTH/2,WIDTH/2));
    for (fieldObject* fO:myParts)
        fO->draw();
}

void field::addOwner(player* owner)
{
    owners.push_back(owner);
}

void field::removeOwner(player* owner)
{
    int i=0;
    for (player* p:owners)
    {
        if (p==owner)
        {
            owners.erase(owners.begin()+i,owners.begin()+i+1);
            return;
        }
        i++;
    }
}

bool field::isOwner(player* owner)
{
    for (player* p:owners)
        if (p==owner)
            return true;
    return false;
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
        myParts.push_back(new barrack(origo,myGameScreen->currentPlayer));
        type=BARRACK;
    }
    else if (part==fieldObject::VILLAGE)
    {
        myParts.push_back(new village(origo));
        type=VILLAGE;
    }
    else if (part==fieldObject::STRONGHOLD)
    {
        if (myGameScreen->justBuilt)
            myParts.push_back(new stronghold(origo,myGameScreen->currentPlayer));
        else //it wasn't built by a player
            myParts.push_back(new stronghold(origo,NULL));
        type=STRONGHOLD;
    }
    else if (part==fieldObject::MOUNTAIN)
    {
        myParts.push_back(new mountain(origo));
        type=MOUNTAIN;
    }
    else
        cout<<"NINCS ILYEN!!!";
}

void field::activateStronghold(player* owner)
{
    for (fieldObject* fO:myParts)
        if (fO->getType()==fieldObject::STRONGHOLD)
        {
            ((stronghold*)fO)->gotOwner(owner);
            //myGameScreen->newStronghold(coordinate,owner);
        }
}

void field::assaultChange(bool changeTo)
{
    for (fieldObject* fO:myParts)
        if (fO->getType()==fieldObject::STRONGHOLD)
            static_cast<stronghold*>(fO)->assaultChosen=changeTo;
}

bool field::hasPart(string part)
{
    for (fieldObject* fO:myParts)
        if (fO->getType()==part)
            return true;
    return false;
}

player* field::objectOwner()
{
    for (fieldObject* fO:myParts)
    {
        if (fO->getType()==fieldObject::BARRACK)
            return static_cast<barrack*>(fO)->owner;
        else if (fO->getType()==fieldObject::STRONGHOLD)
            if (static_cast<stronghold*>(fO)->hasOwner)
                return static_cast<stronghold*>(fO)->owner;
    }
    return NULL;
}

player* field::strongholdBuilder()
{
    for (fieldObject* fO:myParts)
        if (fO->getType()==fieldObject::STRONGHOLD)
            return static_cast<stronghold*>(fO)->builder;
    return NULL;
}

void field::destroyObject()
{
    int i=0;
    for (fieldObject* fO:myParts)
    {
        if (fO->getType()==fieldObject::BARRACK || fO->getType()==fieldObject::STRONGHOLD)
        {
            delete fO;
            myParts.erase(myParts.begin()+i,myParts.begin()+i+1);
        }
        i++;
    }
    if (myParts.size()==0)
        type=BLANK;
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
    if (part==fieldObject::VILLAGE|| part==fieldObject::MOUNTAIN)
        return false;
    if (part==fieldObject::STRONGHOLD && owners.size()>0)
        return false;
    if (type==BLANK)
        if (part==fieldObject::STRONGHOLD || part==fieldObject::BARRACK)
            if (myGameScreen->currentPlayer->steps==player::MAX_STEPS)
                return true;
            else
                return false;
        else //it's a road
            return true;
    else if (type==ROAD
             && (part==fieldObject::NORTH_ROAD || part==fieldObject::SOUTH_ROAD || part==fieldObject::EAST_ROAD || part==fieldObject::WEST_ROAD)
             && !hasPart(part))
        return true;
    return false;
}
