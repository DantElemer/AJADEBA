#ifndef GAMEOVERSCREEN_H_INCLUDED
#define GAMEOVERSCREEN_H_INCLUDED

#include "../screen.h"
#include "../../data.h"

struct gameOverScreen : screen
{
    public:
        gameOverScreen();
        void draw();
        void onTick();
    protected:
        void keyDown(event kE);

};

#endif // GAMEOVERSCREEN_H_INCLUDED
