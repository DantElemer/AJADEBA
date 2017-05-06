#include "road.h"

const string road::NORTH="north";
const string road::EAST="east";
const string road::SOUTH="south";
const string road::WEST="west";

road::road(coor origo, string direction)
: fieldObject(origo,"pics/game objects/"+direction+" road.kep"), direction(direction)
{
    if (direction==NORTH)
        type=NORTH_ROAD;
    else if (direction==SOUTH)
        type=SOUTH_ROAD;
    else if (direction==EAST)
        type=EAST_ROAD;
    else if (direction==WEST)
        type=WEST_ROAD;
}

road::~road()
{
    //dtor
}

void road::draw()
{
    fieldObject::draw();
}
