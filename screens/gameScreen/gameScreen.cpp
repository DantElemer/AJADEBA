#include "gameScreen.h"
#include "../subScreens/subScreen.h"
#include "../../screenHandler.h"

#include <cstdlib>
#include <fstream>


gameScreen::gameScreen()
{
    initPressedButtons();

    srand(time(NULL));
    generateMap();
    currentPlayer=players[players.size()-1];
    currentPlayer->boosted=true;
    nextPlayer();
}

struct strong
{
    coor coordinate;
    int player;
    strong(coor c, int  p) : coordinate(c), player(p){}
};

void gameScreen::generateMap()
{
    players.push_back(new player("Player 1",player1Nation));
    players.push_back(new player("Player 2",player2Nation));

    vector<strong> strongs;
    int wid,hei;
    string mapFile="maps/";
    mapFile+=chosenMap;
    mapFile+=".txt";
    ifstream mapF(mapFile);
    mapF>>wid>>hei;
    mapOffset=makeCoor(WINDOW_X-(wid-1)*field::WIDTH,WINDOW_Y-(hei-1)*field::WIDTH)/2;
    for (int i=0;i<wid;i++)
    {
        vector<field*> newRow;
        for (int j=0;j<hei;j++)
        {
            field* newField=new field(this,makeCoor(i,j));
            newRow.push_back(newField);

            int owner, partNum;
            mapF>>owner>>partNum;
            if (owner>-1)
                currentPlayer=players[owner];
            else
                currentPlayer=NULL;
            for (int k=0;k<partNum;k++)
            {
                string newPart;
                getline(mapF,newPart,';');
                newField->addPart(newPart);
                if (newPart==fieldObject::STRONGHOLD)
                    if (owner>-1)
                        strongs.push_back(strong(makeCoor(i,j),owner));
            }
        }
        fields.push_back(newRow);
    }
    for (strong s:strongs)
        addTerritoryOwnership(fields[s.coordinate.X][s.coordinate.Y],players[s.player]);
    for (strong s:strongs)
        fields[s.coordinate.X][s.coordinate.Y]->activateStronghold(players[s.player]);
    for (strong s:strongs)
        newStronghold(s.coordinate,players[s.player]);
}

void gameScreen::initPressedButtons() const
{

}

void gameScreen::removeTerritoryOwnership(field* stronghold, player* owner)
{
    coor coordinate=stronghold->coordinate;
    for (int i=coordinate.X-3;i<=coordinate.X+3;i++)
        for (int j=coordinate.Y-3;j<=coordinate.Y+3;j++)
            if (inFields(makeCoor(i,j)))
                if (abs(coordinate.X-i)+abs(coordinate.Y-j)<=stronghold::RADIUS)
                    fields[i][j]->removeOwner(owner);
}

void gameScreen::destroyStronghold(field* stronghold)
{
    player* sadOne=stronghold->objectOwner();
    sadOne->changeStrongholdNumber(-1);
    removeTerritoryOwnership(stronghold,sadOne);
    coor coordinate=stronghold->coordinate;
    for (int i=coordinate.X-3;i<=coordinate.X+3;i++)
        for (int j=coordinate.Y-3;j<=coordinate.Y+3;j++)
            if (inFields(makeCoor(i,j)))
                if (abs(coordinate.X-i)+abs(coordinate.Y-j)<=stronghold::RADIUS)
                {
                    //fields[i][j]->removeOwner(sadOne);
                    if (fields[i][j]->getType()==field::BARRACK)
                        if (!fields[i][j]->isOwner(sadOne))
                            fields[i][j]->destroyObject();
                }
    stronghold->destroyObject();
}

void gameScreen::fieldClicked(field* f)
{
    selectedField=f;
    if (assaultMode)
    {
        assaultMode=false;
        if (selectedField->getType()==field::STRONGHOLD)
            if (selectedField->objectOwner()!=selectedStronghold->objectOwner())
                if (isConnected(*selectedStronghold, *selectedField))
                    if (strongholdStrength(selectedStronghold,currentPlayer) > strongholdStrength(selectedField, selectedField->objectOwner()))
                        {
                            destroyStronghold(selectedField);
                            currentPlayer->steps-=player::MAX_STEPS;
                        }
        selectedStronghold->assaultChange(false);
    }
    else if (f->getType()==field::STRONGHOLD)
    {
        if (currentPlayer->steps==currentPlayer->MAX_STEPS && f->objectOwner()==currentPlayer)
        {
            assaultMode=true;
            selectedStronghold=f;
            selectedStronghold->assaultChange(true);
        }
        cout<<"It's a stronghold";
    }
    else if (f->getType()==field::BARRACK)
    {
        cout<<"It's a barrack";
    }
    else if (f->getType()==field::MOUNTAIN)
    {
        cout<<"It's a mountain.";
    }
    else if (f->getType()==field::VILLAGE)
    {
        cout<<"It's a village.";
    }
    else if (f->getType()==field::ROAD&&f->hasPart(fieldObject::NORTH_ROAD)&&f->hasPart(fieldObject::SOUTH_ROAD)&&f->hasPart(fieldObject::EAST_ROAD)&&f->hasPart(fieldObject::WEST_ROAD))
    {
        cout<<"It's a full road";
    }
    else if (f->canAct(currentPlayer)) //build something?
    {
        subToBuildChooserScreen(); //open build options
    }
    else
        cout<<"Can't build to enemy territory."<<f->owners[0]->name;
}

struct strong2
{
    coor coordinate;
    player* p;
    strong2(coor c, player*  p) : coordinate(c), p(p){}
};

void gameScreen::strongholdBaseConquerCheck()
{
    vector<strong2> nowActivatedStrongs;
    for (vector<field*> fRow:fields)
        for (field* f:fRow)
            if (f->getType()==field::STRONGHOLD)
                if (f->objectOwner()==NULL) //so this field is a stronghold base, now check if someone gets it
                {
                    vector<int> strengths;
                    for (player* p:players)
                        strengths.push_back(strongholdStrength(f,p));
                    int maxStr=0;
                    vector<int> indexes={-1};
                    for (int i=0;i<players.size();i++) //find maxes
                    {
                        if (strengths[i]==maxStr)
                            indexes.push_back(i);
                        if (strengths[i]>maxStr)
                        {
                            maxStr=strengths[i];
                            indexes.clear();
                            indexes.push_back(i);
                        }
                    }
                    if (indexes[0]>-1) //someone gets it
                    {
                        if (indexes.size()==1) //1 player sent more soldiers than all the others
                        {
                            addTerritoryOwnership(f,players[indexes[0]]);
                            nowActivatedStrongs.push_back(strong2(f->coordinate,players[indexes[0]]));
                        }
                        else //in case more players sent more than all the others
                        {
                            bool oneMaxIsBuilder=false;
                            for (int i=0;i<indexes.size();i++)
                                if (players[indexes[i]]==f->strongholdBuilder()) //builder gets it
                                {
                                    addTerritoryOwnership(f,players[indexes[i]]);
                                    nowActivatedStrongs.push_back(strong2(f->coordinate,players[indexes[i]]));

                                    oneMaxIsBuilder=true;
                                }
                            if (!oneMaxIsBuilder) //if equality and none of them is builder, the one who connected it
                            {
                                addTerritoryOwnership(f,currentPlayer);
                                nowActivatedStrongs.push_back(strong2(f->coordinate,currentPlayer));
                            }
                        }
                    }
                }
    for (strong2 s:nowActivatedStrongs)
        fields[s.coordinate.X][s.coordinate.Y]->activateStronghold(s.p);
    for (strong2 s:nowActivatedStrongs)
        newStronghold(s.coordinate,s.p);
    if (nowActivatedStrongs.size()>0)
        strongholdBaseConquerCheck(); //as there can be strongholds which are connected using the new ones
}

void gameScreen::build()
{
    selectedField->addPart(whatToBuild);
    if (whatToBuild!=subScreen::CANCEL) //so he built something
    {
        if (selectedField->getType()==field::ROAD)
            currentPlayer->steps--;
        else
            currentPlayer->steps-=player::MAX_STEPS;
        strongholdBaseConquerCheck();
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
    currentPlayer->steps=currentPlayer->MAX_STEPS;
    currentPlayer->timeLeft=thinkingTime;
    if (currentPlayer->boosted)
    {
        currentPlayer->boosted=false;
        currentPlayer->steps+=2;
    }
    if (players.size()>1)
        newSub=NEW_TURN_SCREEN;
}

void gameScreen::addTerritoryOwnership(field* stronghold, player* owner)
{
    coor coordinate=stronghold->coordinate;
    for (int i=coordinate.X-3;i<=coordinate.X+3;i++)
        for (int j=coordinate.Y-3;j<=coordinate.Y+3;j++)
            if (inFields(makeCoor(i,j)))
                if (abs(coordinate.X-i)+abs(coordinate.Y-j)<=stronghold::RADIUS)
                    fields[i][j]->addOwner(owner);
}

void gameScreen::newStronghold(coor coordinate, player* owner)
{
    owner->changeStrongholdNumber(1);
    for (int i=coordinate.X-3;i<=coordinate.X+3;i++)
        for (int j=coordinate.Y-3;j<=coordinate.Y+3;j++)
            if (inFields(makeCoor(i,j)))
                if (abs(coordinate.X-i)+abs(coordinate.Y-j)<=stronghold::RADIUS)
                {
                    if (fields[i][j]->owners.size()==1) //it's undefended, so must be killed
                        if (fields[i][j]->getType()==field::BARRACK)
                            if (fields[i][j]->objectOwner()!=owner)
                                fields[i][j]->destroyObject();
                    if (fields[i][j]->getType()==field::STRONGHOLD)
                        if (fields[i][j]->objectOwner()==NULL) //its a str base, so must be killed
                                fields[i][j]->destroyObject();
                }

}

bool gameScreen::inFields(coor coordinate)
{
    if (coordinate.X<0)
        return false;
    if (coordinate.Y<0)
        return false;
    if (coordinate.X>=fields.size())
        return false;
    if (coordinate.Y>=fields[0].size())
        return false;
    return true;
}

int gameScreen::barrackStrength(field* bField)
{
    int strength=0;
    for (vector<field*> fRow:fields)
        for (field* f:fRow)
            if (f->getType()==field::VILLAGE)
                if (isConnected(*f,*bField))
                    strength++;
    return strength;
}

int gameScreen::strongholdStrength(field* shField, player* who)
{
    int strength=0;
    for (vector<field*> fRow:fields)
        for (field* f:fRow)
            if (f->getType()==field::BARRACK)
                if (f->objectOwner()==who)
                    if (isConnected(*f,*shField))
                        strength+=barrackStrength(f);
    return strength;
}

void gameScreen::drawFields()
{
    for (vector<field*> fRow:fields)
        for (field* f:fRow)
            if (f->getType()!=field::STRONGHOLD)
                f->draw();
    for (vector<field*> fRow:fields)
        for (field* f:fRow)
            if (f->getType()==field::STRONGHOLD)
                f->draw();
}

void gameScreen::maySwitchPlayer()
{
    if (currentPlayer->steps==0 || currentPlayer->timeLeft<=0)
        nextPlayer();
}

void gameScreen::killDeadPlayers()
{
    int i=0;
    for (player* p:players)
    {
        if (p->dead)
        {
            cout<<"meghaltam "<<p->name;
            delete p;
            players.erase(players.begin()+i,players.begin()+i+1);
        }
        i++;
    }
}

void gameScreen::mayEnd()
{
    if (players.size()==1)
    {
        newSub=screen::VICTORY_MESSAGE;
        currentPlayer=players[0];
    }
}

void gameScreen::mayBuild()
{
    if (justBuilt)
    {
        build();
        justBuilt=false;
    }
}

void gameScreen::decreasePlayerTime()
{
    coor uLC=makeCoor(0,0);
    string text="Time left: "+numToString(currentPlayer->timeLeft);
    int fSize=20;
    clearScreen(uLC,uLC+makeCoor(countTextWidth(text,fSize),countTextHeight(text,fSize)));
    currentPlayer->timeLeft-=1.0/(double)screenHandler::FPS;
    writeText(uLC,text,fSize);
}

void gameScreen::onTick()
{
    clearScreen();
    drawFields();
    decreasePlayerTime();

    mayBuild();
    killDeadPlayers();
    maySwitchPlayer();

    mayEnd();

    screen::onTick();
}

void gameScreen::keyDown(event kE)
{
    screen::keyDown(kE);
    if (kE.keycode=='n')
        currentPlayer->steps=0;
    if (kE.keycode=='g')
        currentPlayer->dead=true;
}

void gameScreen::keyUp(event kE)
{
    screen::keyUp(kE);
}

void gameScreen::subToBuildChooserScreen()
{
    newSub=screen::BUILD_CHOOSER_SCREEN;
}














//GATE OF HELL













//DO NOT GO ON















//YOU HAVE BEEN WARNED













struct point
{ //meet: from middle you can reach neighbour's edge
  //strong: the neighbour can reach your edge
    bool northMeet=false;
    bool northStrong=false;
    bool southMeet=false;
    bool southStrong=false;
    bool eastMeet=false;
    bool eastStrong=false;
    bool westMeet=false;
    bool westStrong=false;
    bool checked=false;
    coor coordinate;

    point (coor coordinate, bool useStrongs, player* who, gameScreen gS)
    : coordinate(coordinate)
    {
        if (gS.inFields(coordinate+makeCoor(0,1)))
        {
            if (gS.fields[coordinate.X][coordinate.Y]->hasPart(fieldObject::SOUTH_ROAD))
                southMeet=true;
            if (gS.fields[coordinate.X][coordinate.Y+1]->hasPart(fieldObject::NORTH_ROAD))
                southStrong=true;
        }
        if (gS.inFields(coordinate+makeCoor(0,-1)))
        {
            if (gS.fields[coordinate.X][coordinate.Y]->hasPart(fieldObject::NORTH_ROAD))
                northMeet=true;
            if (gS.fields[coordinate.X][coordinate.Y-1]->hasPart(fieldObject::SOUTH_ROAD))
                northStrong=true;
        }
        if (gS.inFields(coordinate+makeCoor(1,0)))
        {
            if (gS.fields[coordinate.X][coordinate.Y]->hasPart(fieldObject::EAST_ROAD))
                eastMeet=true;
            if (gS.fields[coordinate.X+1][coordinate.Y]->hasPart(fieldObject::WEST_ROAD))
                eastStrong=true;
        }
        if (gS.inFields(coordinate+makeCoor(-1,0)))
        {
            if (gS.fields[coordinate.X][coordinate.Y]->hasPart(fieldObject::WEST_ROAD))
                westMeet=true;
            if (gS.fields[coordinate.X-1][coordinate.Y]->hasPart(fieldObject::EAST_ROAD))
                westStrong=true;
        }

        if (useStrongs)
        {
            if (gS.inFields(coordinate+makeCoor(0,1)))
                if (gS.fields[coordinate.X][coordinate.Y+1]->hasPart(fieldObject::STRONGHOLD) && gS.fields[coordinate.X][coordinate.Y+1]->objectOwner()==who)
                    southStrong=true;
            if (gS.inFields(coordinate+makeCoor(0,-1)))
                if (gS.fields[coordinate.X][coordinate.Y-1]->hasPart(fieldObject::STRONGHOLD) && gS.fields[coordinate.X][coordinate.Y-1]->objectOwner()==who)
                    northStrong=true;
            if (gS.inFields(coordinate+makeCoor(1,0)))
                if (gS.fields[coordinate.X+1][coordinate.Y]->hasPart(fieldObject::STRONGHOLD) && gS.fields[coordinate.X+1][coordinate.Y]->objectOwner()==who)
                    eastStrong=true;
            if (gS.inFields(coordinate+makeCoor(-1,0)))
                if (gS.fields[coordinate.X-1][coordinate.Y]->hasPart(fieldObject::STRONGHOLD) && gS.fields[coordinate.X-1][coordinate.Y]->objectOwner()==who)
                    westStrong=true;
            if (gS.fields[coordinate.X][coordinate.Y]->hasPart(fieldObject::STRONGHOLD) && gS.fields[coordinate.X][coordinate.Y]->objectOwner()==who)
            {
                northMeet=true;
                southMeet=true;
                eastMeet=true;
                westMeet=true;
            }
        }
    }
    bool isAimPoint(point* aimPoint, vector<vector<point*>> points) //recursion
    {
     if (checked)
            return false;
        checked=true;
        if (northMeet)
            if (coordinate+makeCoor(0,-1)==aimPoint->coordinate)
                return true;
            else if (northStrong)
                if (points[coordinate.X][coordinate.Y-1]->isAimPoint(aimPoint, points))
                    return true;
        if (southMeet)
            if (coordinate+makeCoor(0,1)==aimPoint->coordinate)
                return true;
            else if (southStrong)
                if (points[coordinate.X][coordinate.Y+1]->isAimPoint(aimPoint, points))
                    return true;
        if (eastMeet)
            if (coordinate+makeCoor(1,0)==aimPoint->coordinate)
                return true;
            else if (eastStrong)
                if (points[coordinate.X+1][coordinate.Y]->isAimPoint(aimPoint, points))
                    return true;
        if (westMeet)
            if (coordinate+makeCoor(-1,0)==aimPoint->coordinate)
                return true;
            else if (westStrong)
                if (points[coordinate.X-1][coordinate.Y]->isAimPoint(aimPoint, points))
                    return true;
        return false;
    }
};

bool helperF(field from, field to, vector<vector<field*>> fields, bool useFriendlyStrongholds, gameScreen gS)
{
    if (abs(from.coordinate.X-to.coordinate.X)+abs(from.coordinate.Y-to.coordinate.Y)==1) //next to
        return true;

    player* who=0;
    if (useFriendlyStrongholds) //barrack to strongh
        who=from.objectOwner();

    vector<vector<point*>> points;
    for (int i=0;i<fields.size();i++) //inicializing points
    {
        vector<point*> newRow;
        for (int j=0;j<fields[0].size();j++)
        {
            point* newPoint=new point(makeCoor(i,j),useFriendlyStrongholds,who, gS);
            newRow.push_back(newPoint);
            newPoint=0;
            delete newPoint;
        }
        points.push_back(newRow);
    }
    who=0;
    delete who;
    points[from.coordinate.X][from.coordinate.Y]->northMeet=true;
    points[from.coordinate.X][from.coordinate.Y]->southMeet=true;
    points[from.coordinate.X][from.coordinate.Y]->eastMeet=true;
    points[from.coordinate.X][from.coordinate.Y]->westMeet=true;
    return points[from.coordinate.X][from.coordinate.Y]->isAimPoint(points[to.coordinate.X][to.coordinate.Y],points);
}

bool gameScreen::isConnected(field from, field to)
{
    if (from.getType()==field::VILLAGE
        && to.getType()==field::BARRACK) //can use only roads
        return helperF(from, to, fields, false, *this);
    else if (from.getType()==field::BARRACK //can use roads and friendly strongholds
          && to.getType()==field::STRONGHOLD)
        return helperF(from, to, fields, true, *this);
    else if (from.getType()==field::STRONGHOLD //assault
          && to.getType()==field::STRONGHOLD) //can use only roads, to target(to)'s territory
        for (int i=to.coordinate.X-3;i<=to.coordinate.X+3;i++)
            for (int j=to.coordinate.Y-3;j<=to.coordinate.Y+3;j++)
                if (inFields(makeCoor(i,j)))
                    if (abs(i-to.coordinate.X)+abs(j-to.coordinate.Y)<=3) //border field
                        if (helperF(from,*fields[i][j], fields, false, *this))
                            return true;
    return false;
}
