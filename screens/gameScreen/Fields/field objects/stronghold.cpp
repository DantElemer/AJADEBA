#include "stronghold.h"

stronghold::stronghold(coor origo, string owner)
: fieldObject(origo), owner(owner)
{
    //ctor
}

stronghold::~stronghold()
{
    //dtor
}

void stronghold::draw()
{
    drawRectangle(origo-makeCoor(10,10),origo+makeCoor(10,10));
}
