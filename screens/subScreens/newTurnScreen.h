#ifndef NEWTURNSCREEN_H
#define NEWTURNSCREEN_H

#include "subScreen.h"

class gameScreen;

class newTurnScreen : public subScreen
{
    public:
        newTurnScreen(gameScreen* gS);
        void draw();
    protected:
    private:
        gameScreen* myGS;
};

#endif // NEWTURNSCREEN_H
