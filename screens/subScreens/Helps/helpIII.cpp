#include "helpIII.h"

helpIII::helpIII()
{
    widgetBase* backButton=new button ((vFunctionCall)terminateSub, makeCoor(30,WINDOW_Y-80),makeCoor(150,WINDOW_Y-30),"Back",30);
    widgets.push_back(backButton);
    widgets.push_back(new lButton([](){newSub=screen::HELPIV;},makeCoor(WINDOW_X-100,WINDOW_Y-55),120,50,"Next"));

    draw();
}

void helpIII::draw()
{
    helpBase::draw();
    addTitle("How to play III");
    addParagraph("Some definitions: ");
    addParagraph("Connection: object A is connected to object B if you can walk from one of A's "
                 "edges to one of B's edges on roads (neighbours are always connected). If A is a barracks"
                 " and B is a stronghold/stronghold base, friendly strongholds count as full roads. ");

    addParagraph("Barracks-strength: a barracks' strength is the number of villages connected to the barracks");
    addParagraph("Stronghold-strength: a stronghold's strength is the sum of barracks-strengths of barracks"
                 " connected to the stronghold. ");
    addParagraph("Undefended barracks: a barracks is undefended if it is outside friendly territory. ");
}
