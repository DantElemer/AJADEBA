#include "road.h"

const string road::NORTH="north";
const string road::EAST="east";
const string road::SOUTH="south";
const string road::WEST="west";

road::road(coor origo, string direction)
: fieldObject(origo), direction(direction)
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
    int l=20;
    if (direction==NORTH)
        drawRectangle(origo-makeCoor(1,l),origo);
    else if (direction==EAST)
        drawRectangle(origo,origo+makeCoor(l,1));
    else if (direction==SOUTH)
        drawRectangle(origo,origo+makeCoor(1,l));
    else if (direction==WEST)
        drawRectangle(origo,origo-makeCoor(l,1));
}
