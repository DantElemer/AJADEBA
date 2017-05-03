#ifndef MENUSCREEN_H_INCLUDED
#define MENUSCREEN_H_INCLUDED

#include "../screen.h"

struct menuScreen : screen
{
    private:
        static void switchToDifficultySettingScreen();

    public:
        menuScreen();
        void draw();
        void onTick();

        /*void test();
        static void stest(menuScreen* menu);*/
};

#endif // MENUSCREEN_H_INCLUDED
