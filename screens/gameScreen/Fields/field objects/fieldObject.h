#ifndef FIELDOBJECT_H
#define FIELDOBJECT_H

#include <string>

#include "../../../../coor.h"

using namespace std;

class fieldObject
{
    public:
        fieldObject(coor origo);
        virtual ~fieldObject();
        virtual void draw()=0;
        string getType(){return type;};

        static const string NORTH_ROAD;
        static const string SOUTH_ROAD;
        static const string EAST_ROAD;
        static const string WEST_ROAD;
        static const string BARRACK;
        static const string VILLAGE;
        static const string STRONGHOLD;
    protected:
        string type;
        coor origo;
    private:
};

#endif // FIELDOBJECT_H
