#include "widgetBase.h"

using namespace genv;

const string widgetBase::DATA_FILE_NAME="data.txt";

widgetBase::widgetBase(coor upperLeftCorn, coor downerRightCorn)
: upperLeftCorner(upperLeftCorn), downerRightCorner(downerRightCorn), width(downerRightCorn.X-upperLeftCorn.X), height(downerRightCorn.Y-upperLeftCorn.Y), origo((downerRightCorner+upperLeftCorner)/2.0)
{

}

widgetBase::~widgetBase()
{

}

void widgetBase::draw()
{
    for (widgetBase* &sW:subWidgets)
        sW->draw();
}

void widgetBase::redraw()
{
    clearWid();
    draw();
}

void widgetBase::clearWid()
{
    clearScreen(upperLeftCorner,downerRightCorner);
}

void widgetBase::mouseDown()
{
    for (widgetBase* &sW:subWidgets)
        sW->mouseDown();
}

void widgetBase::mouseUp()
{
    for (widgetBase* &sW:subWidgets)
        sW->mouseUp();
}

void widgetBase::mouseWheelUp(event mE)
{
    for (widgetBase* &sW:subWidgets)
        sW->mouseWheelUp(mE);
}

void widgetBase::mouseWheelDown(event mE)
{
    for (widgetBase* &sW:subWidgets)
        sW->mouseWheelDown(mE);
}

void widgetBase::keyUp(event kE)
{
    for (widgetBase* &sW:subWidgets)
        sW->keyUp(kE);
}

void widgetBase::keyDown(event kE)
{
    for (widgetBase* &sW:subWidgets)
        sW->keyDown(kE);
}

void widgetBase::update()
{
    for (widgetBase* &sW:subWidgets)
        sW->update();
}

void widgetBase::addFrame()
{
    drawRectangle(upperLeftCorner,downerRightCorner);
}
