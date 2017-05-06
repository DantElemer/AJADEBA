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
        bool inFields(coor coordinate);

        static void switchToGameOverScreen();
        static void switchToVictoryScreen();
        static void subToBuildChooserScreen();
        /*static void subToAtStart();
        static void subToAlphaDone();
        static void subToHeightDone();
        static void subToEndScene();*/

        vector<vector<field*>> fields;

    public:
        void onTick();
        gameScreen();
        void keyDown(event kE);
        void keyUp(event kE);
        void fieldClicked(field* f);
        void newStronghold(coor coordinate, player* owner);

        player* currentPlayer;
        vector<player*> players;

        //for building
        string whatToBuild;
        field* selectedField;
        bool justBuilt=false; //at least opened and closed build options
};

#endif // GAMESCREEN_H_INCLUDED
