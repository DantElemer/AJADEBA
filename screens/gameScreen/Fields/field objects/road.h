#ifndef ROAD_H
#define ROAD_H

#include "fieldObject.h"
#include "../../../../coor.h"
#include "../../../../graphicsPlus.h"

class road : public fieldObject
{
    public:
        road(coor origo, string direction);
        virtual ~road();
        void draw();

        static const string NORTH;
        static const string EAST;
        static const string SOUTH;
        static const string WEST;
    protected:
        string direction;
    private:
};

#endif // ROAD_H
