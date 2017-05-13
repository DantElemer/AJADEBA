#include "fieldObject.h"
#include "../field.h"

const string fieldObject::NORTH_ROAD="north road";
const string fieldObject::SOUTH_ROAD="south road";
const string fieldObject::EAST_ROAD="east road";
const string fieldObject::WEST_ROAD="west road";
const string fieldObject::BARRACK="barrack";
const string fieldObject::VILLAGE="village";
const string fieldObject::STRONGHOLD="stronghold";
const string fieldObject::MOUNTAIN="mountain";

const vector<string> fieldObject::EVERY_OBJECT={fieldObject::NORTH_ROAD,fieldObject::SOUTH_ROAD,
                                                fieldObject::EAST_ROAD,fieldObject::WEST_ROAD,
                                                fieldObject::BARRACK, fieldObject::VILLAGE,
                                                fieldObject::STRONGHOLD, fieldObject::MOUNTAIN};

fieldObject::fieldObject(coor origo, string picFileName)
: origo(origo), pic(picFileName, origo)
{
    pic.setScaleX((double)field::WIDTH/(double)pic.NORMAL_WIDTH);
    pic.setScaleY((double)field::WIDTH/(double)pic.NORMAL_HEIGHT);
    //pic.origo=pic.origo+1;
}

fieldObject::~fieldObject()
{
    //dtor
}

void fieldObject::draw()
{
    pic.draw();
}
