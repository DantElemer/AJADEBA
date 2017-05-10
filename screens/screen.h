#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "../widgets/widgetBase.h"
#include "../widgets/button.h"
#include "../widgets/indicator.h"
#include "../widgets/specIndicator.h"
#include "../widgets/reachedLED.h"
#include "../widgets/sliderSetter.h"
#include "../widgets/chooser.h"
#include "../widgets/textfield.h"
#include "../widgets/checkbox.h"
#include "../widgets/lButton.h"
#include "../Picture.h"
#include "../coor.h"
#include "../randomFuncs.h"
#include "../data.h"

#include <vector>

//You can put widgets onto it, it can handle events...a simple screen kills the current one(s).
class screen
{
    public:
        static const string WIDGET_TEST_SCREEN;
        static const string MENU_SCREEN;
        static const string GAME_SCREEN;
        static const string GAME_OVER_SCREEN;
        static const string VICTORY_SCREEN;
        static const string MAP_EDITOR;
        static const string SETTINGS_SCREEN;
        static const string DIFFICULTY_SETTING_SCREEN;
        //subScreens
        static const string CONFIRM_EXIT;
        static const string HOW_TO_PLAY_SCREEN;
        static const string BUILD_CHOOSER_SCREEN;
        static const string NEW_TURN_SCREEN;
        static const string SAVE_MAP;
        //changing
        static const string TERMINATED;
        static const string STAY;
        static const string EXIT;

        static string switchTo;
        static string newSub;

        screen();
        virtual ~screen(){};
        void soul(event ev);
        virtual void onTick();
        virtual void draw();


        vector<widgetBase*> widgets;
    protected:

        void mouseMoved(event mE);
        void mouseUp(event mE);
        void mouseDown(event mE);
        void mouseWheelUp(event mE);
        void mouseWheelDown(event mE);
        virtual void keyDown(event kE);
        virtual void keyUp(event kE);


        static void exitRequest();
        static void ponyEffect();
        static void switchToGameScreen();
        static void subToHowToPlayScreen();
        static void switchToMenuScreen();

    private:
};

#endif // SCREEN_H_INCLUDED
