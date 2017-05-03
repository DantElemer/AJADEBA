#ifndef HOWTOPLAYSCREEN_H_INCLUDED
#define HOWTOPLAYSCREEN_H_INCLUDED

#include "subScreen.h"

struct howToPlayScreen : subScreen
{
    public:
        howToPlayScreen();
        void draw();
        void onTick();
};

#endif // HOWTOPLAYSCREEN_H_INCLUDED
