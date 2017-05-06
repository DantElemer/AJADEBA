#include "barrack.h"

barrack::barrack(coor origo, string owner)
: fieldObject(origo), owner(owner)
{
    //ctor
}

barrack::~barrack()
{
    //dtor
}

void barrack::draw()
{
    drawCircle(origo,5);
}
