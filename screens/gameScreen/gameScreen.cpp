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
                    if (owner>-1) //TODO addOwnership to ALL in radius, then remove it
                    {
                        strongs.push_back(strong(makeCoor(i,j),owner));
                        newField->addOwner(players[owner]); //so it won't be killed if in range of an other
                    }
            }
        }
        fields.push_back(newRow);
    }
    for (strong s:strongs)
        addTerritoryOwnership(fields[s.coordinate.X][s.coordinate.Y],players[s.player]);
    for (strong s:strongs)
    {
        removeTerritoryOwnership(fields[s.coordinate.X][s.coordinate.Y],players[s.player]); //because it already owned itself, now it would be double ownership
        fields[s.coordinate.X][s.coordinate.Y]->activateStronghold(players[s.player]);
    }


    /*drawFields();
    gout<<refresh;
    giveMeTime(10);*/

    /*currentPlayer=players[0];

    for (int j=0;j<10;j++) //some fields
    {
        vector<field*> newRow;
        for (int i=0;i<7;i++)
        {
            field* newField=new field(this,makeCoor(j,i));
            newRow.push_back(newField);

            int r=1;
            if (rand()%10<r)
                newField->addPart(fieldObject::NORTH_ROAD);
            if (rand()%10<r)
                newField->addPart(fieldObject::SOUTH_ROAD);
            if (rand()%10<r)
                newField->addPart(fieldObject::WEST_ROAD);
            if (rand()%10<r)
                newField->addPart(fieldObject::EAST_ROAD);

            if (newField->getType()==field::BLANK&&rand()%10<r)
                newField->addPart(fieldObject::VILLAGE);
            if (newField->getType()==field::BLANK&&rand()%10<r)
                newField->addPart(fieldObject::MOUNTAIN);
            newField=0;
            delete newField;
        }
        fields.push_back(newRow);
    }
    fields[5][3]->addPart(fieldObject::STRONGHOLD);
    fields[5][3]->activateStronghold(currentPlayer);
    fields[4][0]->addPart(fieldObject::BARRACK);
    currentPlayer=players[1];
    fields[2][6]->addPart(fieldObject::STRONGHOLD);
    fields[2][6]->activateStronghold(currentPlayer);
    fields[4][6]->addPart(fieldObject::BARRACK);*/
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
    //cout<<f->getType()<<endl;
    //cout<<"Strength: "<<strongholdStrength(fields[5][3],currentPlayer)<<" "<<currentPlayer->name<<endl;
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
                            currentPlayer->steps=0;
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

void gameScreen::strongholdBaseConquerCheck()
{
    for (vector<field*> fRow:fields) //stronghold base check
        for (field* f:fRow)
            if (f->getType()==field::STRONGHOLD)
                if (f->objectOwner()==NULL)
                {
                    vector<int> strengths;
                    for (player* p:players)
                        strengths.push_back(strongholdStrength(f,p));
                    int maxStr=0;
                    vector<int> indexes={-1};
                    for (int i=0;i<players.size();i++)
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
                            f->activateStronghold(players[indexes[0]]);
                        else
                        {
                            bool oneMaxIsBuilder=false;
                            for (int i=0;i<indexes.size();i++)
                                if (players[indexes[i]]==f->strongholdBuilder()) //builder gets it
                                {
                                    f->activateStronghold(players[indexes[i]]);
                                    oneMaxIsBuilder=true;
                                }
                            if (!oneMaxIsBuilder) //if equality and none of them is builder, the one who connected it
                                f->activateStronghold(currentPlayer);
                        }
                    }
                }
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
    if (players.size()>1)
        newSub=NEW_TURN_SCREEN;
    //cout<<"==========================================================\n"<<currentPlayer->name<<"\n";
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
    addTerritoryOwnership(fields[coordinate.X][coordinate.Y],owner);
    for (int i=coordinate.X-3;i<=coordinate.X+3;i++)
        for (int j=coordinate.Y-3;j<=coordinate.Y+3;j++)
            if (inFields(makeCoor(i,j)))
                if (abs(coordinate.X-i)+abs(coordinate.Y-j)<=stronghold::RADIUS)
                {
                    //fields[i][j]->addOwner(owner);
                    //kill undefended ones
                    if (fields[i][j]->owners.size()==1) //it's undefended
                    {
                        if (fields[i][j]->getType()==field::BARRACK)
                            if (fields[i][j]->objectOwner()!=owner)
                                fields[i][j]->destroyObject();
                        if (fields[i][j]->getType()==field::STRONGHOLD)
                            if (fields[i][j]->objectOwner()==NULL) //its a str base, so basically must be killed, however in some really few cases more str base can be activated in each othrs range
                            {
                                cout<<"megpusztulsz";
                                bool beingActivated=false;
                                for (player* p:players)
                                    if (strongholdStrength(fields[i][j],p)>0)
                                        beingActivated=true;
                                if (!beingActivated)
                                    fields[i][j]->destroyObject();
                            }
                    }
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
        //switchToVictoryScreen();
        newSub=screen::VICTORY_MESSAGE;
    currentPlayer=players[0];
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
