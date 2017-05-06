#ifndef FIELD_H
#define FIELD_H

#include "../../../coor.h"
#include "../../../graphicsPlus.h"
#include "../../../widgets/lButton.h"
#include "field objects/road.h"

class gameScreen;

class field
{
    public:
        field(gameScreen* gS, coor origo);
        virtual ~field();
        void draw();
        string getType(){return type;};

        static const int WIDTH=50; //=height
        coor origo;
        static const string BLANK;
    protected:
        gameScreen* myGameScreen;
        string type;
        vector<fieldObject*> myParts;
    private:
};

#endif // FIELD_H
