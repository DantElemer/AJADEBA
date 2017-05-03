#ifndef SCREENHANDLER_H_INCLUDED
#define SCREENHANDLER_H_INCLUDED


#include "screens\screen.h"
#include "screens\widgetTestScreen.h"
#include "screens\others\menuScreen.h"
#include "screens\others\difficultySettingScreen.h"
#include "screens\others\gameOverScreen.h"
#include "screens\others\victoryScreen.h"
#include "screens\gameScreen\gameScreen.h"
#include "screens\subScreens\confirmExitScreen.h"
#include "screens\subScreens\howToPlayScreen.h"

#include "graphics.hpp"

//As you could guess, it handles screens...

/*
How to create a new (sub)screen:
1) add a new class for example: exampleScreen : public (sub)screen
2) in screen.h add a static const string variable: EXAMPLE_SCREEN
3) in screen.cpp add a value to it: "example screen"
4) in screenHadler.cpp find addSub/switchScreen and add a new brand (like the others)
5) in screenHandler.h include xyScreen.h
+1 if you want to add once-drawn pieces, do it by overriding draw() function

How to terminate subScreen:
fire terminateSub().

How to switch screen:
use switchToXYScreen() if it exist
otherwise create a function like that and fire it.

How to add sub:
use subToXYScreen() if it exist
otherwise create a function like that and fire it.
*/

class screenHandler
{
    public:
        void soul(); //the Core
    private:
        const int FPS=40;
        bool exitAwesomeness=false; //used for the exit-system (true means exit is confirmed)
        bool exitReqested=false; //used for the exit-system (true means exit was requested)
        vector<screen*> screensAlive; //current screens

        void exitGame(); //confirm exit
        void switchScreen(screen *&currScr); //...and kills all current ones
        void addSub(string newSubName); //adds a new screen, on the top of the current ones
};

#endif // SCREENHANDLER_H_INCLUDED
