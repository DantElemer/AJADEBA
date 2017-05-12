#ifndef MENUSCREEN_H_INCLUDED
#define MENUSCREEN_H_INCLUDED

#include "../screen.h"

struct menuScreen : screen
{
    private:

    public:
        menuScreen();
        void draw();
        void onTick();
};

#endif // MENUSCREEN_H_INCLUDED
