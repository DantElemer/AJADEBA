#include "mButton.h"


mButton::mButton(memberFunctionCall fire, void* object, coor origo, double width, double height, string texty, int fontSize)
:button(NULL, origo, width, height, texty, fontSize), object(object), memFunCall(fire)
{

}

mButton::mButton(memberFunctionCall fire, void* object, coor upperLeftCorn, coor downerRightCorn, string texty, int fontSize)
: button(NULL, upperLeftCorn, downerRightCorn, texty, fontSize),
memFunCall(fire),
object(object)
{

}



void mButton::fireFunction()
{
    memFunCall(object);
}

