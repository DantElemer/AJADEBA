#ifndef VICTORYSCREEN_H_INCLUDED
#define VICTORYSCREEN_H_INCLUDED

#include "../screen.h"
#include "../../data.h"

struct victoryScreen : screen
{
    public:
        victoryScreen();
        void draw();
        void onTick();
    protected:
        void keyDown(event kE);
};

#endif // VICTORYSCREEN_H_INCLUDED
