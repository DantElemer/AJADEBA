#include "village.h"

village::village(coor origo)
: fieldObject(origo,"pics/game objects/village.kep")
{
    type=VILLAGE;
}

village::~village()
{
    //dtor
}

void village::draw()
{
    fieldObject::draw();
}
