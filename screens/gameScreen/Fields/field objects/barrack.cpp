#include "barrack.h"
#include "../../player.h"

barrack::barrack(coor origo, player* owner)
: fieldObject(origo,"pics/game objects/nations/"+owner->nation+"/Barrack.kep"), owner(owner)
{
    type=BARRACK;
}

barrack::~barrack()
{
    //dtor
}

void barrack::draw()
{
    fieldObject::draw();
}
