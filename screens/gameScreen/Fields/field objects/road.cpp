#include "road.h"

const string road::NORTH="north";
const string road::EAST="east";
const string road::SOUTH="south";
const string road::WEST="west";

road::road(coor origo, string direction)
: direction(direction), origo(origo)
{
    //ctor
}

road::~road()
{
    //dtor
}

void road::draw()
{
    int l=10;
    if (direction==NORTH)
        drawRectangle(origo-makeCoor(1,l),origo);
    else if (direction==EAST)
        drawRectangle(origo,origo+makeCoor(l,1));
    else if (direction==SOUTH)
        drawRectangle(origo,origo+makeCoor(1,l));
    else if (direction==WEST)
        drawRectangle(origo,origo-makeCoor(l,1));
}
