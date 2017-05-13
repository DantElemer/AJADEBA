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
    addParagraph("Connection: basically object A is connected to object B, if you can walk from one of A's "
                 "edges middle to one of B's edges on roads (neighbours are connected for sure). If A is a "
                 "barrack and B is a stronghold/strongholdBase, friendly strongholds count as full roads. ");

    addParagraph("Barrack-strength: a barrack's strength is the number of villages, connected to the barrack");
    addParagraph("Stronghold-strength: a stronghold's strength is the sum of barrack-strengths of barracks"
                 " connected to the stronghold. ");
}
