#ifndef PONYSCREEN_H
#define PONYSCREEN_H

#include "subScreen.h"
#include "../../Picture.h"

#include <cstdlib>

struct pony
{
    pony (coor origo);
    bool scaleYourself();
    Picture pic;
    double MAX_SCALE;
    double SCALE_SPEED;
    bool growing=true;
    double MIN_SCALE=0.2;
};

class PonyScreen : public subScreen
{
    public:
        PonyScreen();
        void onTick();
        void keyDown(event kE);
        void mouseUp(event mE);
    private:
        vector<pony> ponies;
};

#endif // PONYSCREEN_H
