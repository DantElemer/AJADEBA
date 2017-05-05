#ifndef FIELD_H
#define FIELD_H

#include "../../../coor.h"
#include "../../../graphicsPlus.h"
#include "../../../widgets/lButton.h"

class gameScreen;

class field
{
    public:
        field(gameScreen* gS, coor origo);
        virtual ~field();
        void draw();

        static const int WIDTH=50; //=height
        coor origo;
    protected:
        gameScreen* myGameScreen;
    private:
};

#endif // FIELD_H
