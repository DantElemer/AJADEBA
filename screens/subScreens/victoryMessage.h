#ifndef VICTORYMESSAGE_H
#define VICTORYMESSAGE_H

#include "subScreen.h"
class gameScreen;

class victoryMessage : public subScreen
{
    public:
        victoryMessage(gameScreen* gS);
        void draw();
    private:
        gameScreen* myGS;
};

#endif // VICTORYMESSAGE_H
