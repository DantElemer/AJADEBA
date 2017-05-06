#ifndef FIELD_H
#define FIELD_H

#include "../../../coor.h"
#include "../../../graphicsPlus.h"
#include "../../../widgets/lButton.h"
#include "field objects/road.h"
#include "field objects/barrack.h"
#include "field objects/village.h"
#include "field objects/stronghold.h"

class gameScreen;

class field
{
    public:
        field(gameScreen* gS, coor origo);
        virtual ~field();
        void draw();
        string getType(){return type;};
        void addPart(string part);
        bool hasPart(string part);

        static const int WIDTH=50; //=height
        coor origo;
        static const string BLANK;
        static const string ROAD;
        static const string BARRACK;
        static const string VILLAGE;
        static const string STRONGHOLD;

        /*bool northConnection=false;
        bool southConnection=false;
        bool eastConnection=false;
        bool westConnection=false;*/
    protected:
        gameScreen* myGameScreen;
        string type;
        vector<fieldObject*> myParts;
    private:
};

#endif // FIELD_H
