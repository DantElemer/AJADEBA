#include "helpII.h"

helpII::helpII()
{
    widgetBase* backButton=new button ((vFunctionCall)terminateSub, makeCoor(30,WINDOW_Y-80),makeCoor(150,WINDOW_Y-30),"Back",30);
    widgets.push_back(backButton);
    widgets.push_back(new lButton([](){newSub=screen::HELPIII;},makeCoor(WINDOW_X-100,WINDOW_Y-55),120,50,"Next"));

    draw();
}

void helpII::draw()
{
    helpBase::draw();
    addTitle("How to play II");

    addParagraph("There are objects you cannot build: ");
    addParagraph("Villages: they are on the map from the start and cannot be destroyed. "
                 " They provide people for barracks, both yours and those of your opponent. They never "
                 "belong to one specific player. Marker: circle. ");
    addParagraph("Strongholds: you get at least one at the start and you can get more by conquering stronghold "
                 "bases. They claim territory. Marker: square with the owner player's flag. ");
    addParagraph("Mountains: they don't do anything other than existing: you can't build on them. "
                 "Marker: full square. ");
}

