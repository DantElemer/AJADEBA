#include "fieldObject.h"

const string fieldObject::NORTH_ROAD="north road";
const string fieldObject::SOUTH_ROAD="south road";
const string fieldObject::EAST_ROAD="east road";
const string fieldObject::WEST_ROAD="west road";
const string fieldObject::BARRACK="barrack";
const string fieldObject::VILLAGE="village";
const string fieldObject::STRONGHOLD="stronghold";

const vector<string> fieldObject::EVERY_OBJECT={fieldObject::NORTH_ROAD,fieldObject::SOUTH_ROAD,
                                                fieldObject::EAST_ROAD,fieldObject::WEST_ROAD,
                                                fieldObject::BARRACK, fieldObject::VILLAGE,
                                                fieldObject::STRONGHOLD};

fieldObject::fieldObject(coor origo)
: origo(origo)
{
    //ctor
}

fieldObject::~fieldObject()
{
    //dtor
}