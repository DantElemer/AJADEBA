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
    addParagraph("Conquering a stronghold base: basically if you connect your barrack -whose strength isn't zero-"
                 "to it, you get it as a stronghold. However, there are some more complicated cases...if it's get"
                 "connected to different players at once");

    addParagraph("Starting an assault: basically if you connect your barrack -whose strength isn't zero-"
                 "to it, you get it as a stronghold. However, there are some more complicated cases...");
}
