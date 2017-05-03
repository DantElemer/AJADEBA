#include "checkbox.h"

checkbox::checkbox(coor uLC, coor dRC, bool &var)
: widgetBase(uLC,dRC), currValue(&var)
{
    subWidgets.push_back(new mButton((memberFunctionCall)sChange,this,uLC,dRC));
}

checkbox::~checkbox()
{
    //dtor
}

void checkbox::sChange(checkbox* c)
{
    c->change();
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
