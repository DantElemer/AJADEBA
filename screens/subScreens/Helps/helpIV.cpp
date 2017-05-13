#include "helpIV.h"

helpIV::helpIV()
{
    widgetBase* backButton=new button ((vFunctionCall)terminateSub, makeCoor(30,WINDOW_Y-80),makeCoor(150,WINDOW_Y-30),"Back",30);
    widgets.push_back(backButton);
    draw();
}

void helpIV::draw()
{
    helpBase::draw();
    addTitle("How to play IV");
    addParagraph("Finally conquering and assaults: ");
    addParagraph("Conquering a stronghold base: basically if a barrack -whose strength is not zero- gets "
                 "connected to a base, the base becomes the barrack's owner's stronghold. ");
}
