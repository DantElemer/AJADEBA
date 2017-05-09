#ifndef FIELDOBJECT_H
#define FIELDOBJECT_H

#include <string>

#include "../../../../coor.h"
#include "../../../../Picture.h"

using namespace std;

class fieldObject
{
    public:
        fieldObject(coor origo, string picFileName);
        virtual ~fieldObject();
        virtual void draw();
        string getType(){return type;};

        static const string NORTH_ROAD;
        static const string SOUTH_ROAD;
        static const string EAST_ROAD;
        static const string WEST_ROAD;
        static const string BARRACK;
        static const string VILLAGE;
        static const string STRONGHOLD;
        static const string MOUNTAIN;

        static const vector<string> EVERY_OBJECT;
    protected:
        string type;
        coor origo;
        Picture pic;
    private:
};

#endif // FIELDOBJECT_H
