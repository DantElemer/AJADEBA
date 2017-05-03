#ifndef DIFFICULTYSETTINGSCREEN_H
#define DIFFICULTYSETTINGSCREEN_H

#include "../screen.h"


class difficultySettingScreen : public screen
{
    public:
        difficultySettingScreen();
        void draw();
    protected:

    private:
        static void startEasyGame();
        static void startNormalGame();
        static void startHardGame();
};

#endif // DIFFICULTYSETTINGSCREEN_H
