#include "checkbox.h"

checkbox::checkbox(coor uLC, coor dRC, bool &var)
: widgetBase(uLC,dRC), currValue(&var)
{
    subWidgets.push_back(new lButton([this](){this->change();},origo,width,height));
}

checkbox::~checkbox()
{
    //dtor
}

void checkbox::change()
{
    *currValue=!*currValue;
}

void checkbox::update()
{
    widgetBase::update();
    redraw();
}

void checkbox::draw()
{
    widgetBase::draw();
    if (*currValue)
        mWriteText(origo,"pipa",12);
    else
        mWriteText(origo,"!pipa",12);
}
