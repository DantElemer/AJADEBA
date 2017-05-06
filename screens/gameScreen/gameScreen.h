#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED


#include "../../data.h"
#include "../screen.h"
#include "Fields/field.h"
#include "Fields/field objects/road.h"


struct gameScreen : screen
{
    private:
        void initPressedButtons() const;

        static void switchToGameOverScreen();
        static void switchToVictoryScreen();
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
};

#endif // GAMESCREEN_H_INCLUDED
