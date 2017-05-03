#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED


#include "../../data.h"
#include "../screen.h"


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

    public:
        void onTick();
        gameScreen();
        void keyDown(event kE);
        void keyUp(event kE);
};

#endif // GAMESCREEN_H_INCLUDED
