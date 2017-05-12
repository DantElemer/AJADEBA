#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include "../screen.h"
#include "../../data.h"

#include <fstream>

class settingsScreen : public screen
{
    public:
        settingsScreen();
        void draw();
        void onTick();
    private:
        string loadedDesc;
        void loadNewDesc();
};

#endif // SETTINGSSCREEN_H
