#include "village.h"

village::village(coor origo)
: fieldObject(origo)
{
    //ctor
}

village::~village()
{
    //dtor
}

void village::draw()
{
    drawCircle(origo,10);
}
