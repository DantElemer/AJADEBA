#include "stronghold.h"
#include "../../player.h"
#include "../field.h"

stronghold::stronghold(coor origo, player* builder)
: fieldObject(origo,"pics/game objects/stronghold.kep"), builder(builder)
//"pics/game objects/nations/"+owner->nation+"/Stronghold.kep
{
    type=STRONGHOLD;
}

stronghold::~stronghold()
{
    //dtor
}

void stronghold::draw()
{
    fieldObject::draw();
    if (assaultChosen)
        for (int i=0;i<4;i++)
            drawRectangle(origo-makeCoor(field::WIDTH/2-i,field::WIDTH/2-i), origo+makeCoor(field::WIDTH/2-i,field::WIDTH/2-i),false,255,0,0);
    if (hasOwner)
        territory.draw();
}

void stronghold::gotOwner(player* bowner)
{
    owner=bowner;
    pic.addNewPic("pics/game objects/nations/"+owner->nation+"/stronghold.kep", origo);
    hasOwner=true;
    pic.setScaleX((double)field::WIDTH/(double)pic.getWidth());
    pic.setScaleY((double)field::WIDTH/(double)pic.getHeight());
    territory.addNewPic("pics/game objects/nations/"+owner->nation+"/Territory"+numToString(RADIUS)+".kep",origo);
    territory.setScaleX((double)(field::WIDTH*7)/(double)territory.NORMAL_WIDTH);
    territory.setScaleY((double)(field::WIDTH*7)/(double)territory.NORMAL_HEIGHT);

}
