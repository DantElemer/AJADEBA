#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED


#include "../../data.h"
#include "../screen.h"
#include "Fields/field.h"
#include "Fields/field objects/road.h"
#include "player.h"


struct gameScreen : screen
{
    private:
        void initPressedButtons() const;
        void nextPlayer();
        void build();
        bool isConnected(field from, field to);
        int barrackStrength(field* bField);
        int strongholdStrength(field* shField, player* who);
        void destroyStronghold(field* stronghold);
        void strongholdBaseConquerCheck();
        void drawFields();
        void maySwitchPlayer();
        void killDeadPlayers();
        void mayEnd();
        void mayBuild();
        void generateMap();
        void addTerritoryOwnership(field* stronghold, player* owner);
        void removeTerritoryOwnership(field* stronghold, player* owner);


        static void subToBuildChooserScreen();
        bool assaultMode=false;
        field* selectedStronghold;

    public:
        void onTick();
        gameScreen();
        void keyDown(event kE);
        void keyUp(event kE);
        void fieldClicked(field* f);
        void newStronghold(coor coordinate, player* owner);
        bool inFields(coor coordinate);
        void decreasePlayerTime();

        player* currentPlayer;
        vector<player*> players;
        vector<vector<field*>> fields;
        coor mapOffset;

        //for building
        string whatToBuild;
        field* selectedField;
        bool justBuilt=false; //at least opened and closed build options
};

#endif // GAMESCREEN_H_INCLUDED
