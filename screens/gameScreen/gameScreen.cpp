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
            newField=0;
            delete newField;
            /*if (newField->getType()==field::BLANK&&rand()%10<1)
                newField->addPart(fieldObject::VILLAGE);
            if (newField->getType()==field::BLANK&&rand()%10<1)
                newField->addPart(fieldObject::STRONGHOLD);
            if (newField->getType()==field::BLANK&&rand()%10<1)
                newField->addPart(fieldObject::BARRACK);*/
        }
        fields.push_back(newRow);
    }
    fields[5][3]->addPart(fieldObject::STRONGHOLD);
    fields[5][3]->activateStronghold(currentPlayer);
    fields[4][0]->addPart(fieldObject::BARRACK);
    nextPlayer();
    fields[2][6]->addPart(fieldObject::STRONGHOLD);
    fields[2][6]->activateStronghold(currentPlayer);
    fields[4][6]->addPart(fieldObject::BARRACK);
    nextPlayer();
    isConnected(*fields[5][3],*fields[5][3]);
}

void gameScreen::initPressedButtons() const
{

}

void gameScreen::fieldClicked(field* f)
{
    cout<<f->getType()<<endl;
    cout<<"Strength: "<<strongholdStrength(fields[5][3],currentPlayer)<<" "<<currentPlayer->name<<endl;
    selectedField=f;
    if (f->canAct(currentPlayer))
    {
        subToBuildChooserScreen(); //open build options
    }
    else
        cout<<"enemy territory"<<f->owners[0]->name;
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

void gameScreen::newStronghold(coor coordinate, player* owner)
{
    for (int i=coordinate.X-3;i<=coordinate.X+3;i++)
        for (int j=coordinate.Y-3;j<=coordinate.Y+3;j++)
            if (inFields(makeCoor(i,j)))
                if (abs(coordinate.X-i)+abs(coordinate.Y-j)<=stronghold::RADIUS)
                    fields[i][j]->addOwner(owner);
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
                    if (abs(i-to.coordinate.X)+abs(j-to.coordinate.Y)==3) //border field
                        if (helperF(from,*fields[i][j], fields, false, *this))
                            return true;
    return false;
}
