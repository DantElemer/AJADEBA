#include "howToPlayScreen.h"

howToPlayScreen::howToPlayScreen()
{
    widgetBase* backButton=new button ((vFunctionCall)terminateSub, makeCoor(30,WINDOW_Y-80),makeCoor(150,WINDOW_Y-30),"Back",30);
    widgets.push_back(backButton);
    widgets.push_back(new lButton([](){newSub=screen::HELPII;},makeCoor(WINDOW_X-100,WINDOW_Y-55),120,50,"Next"));

    draw();
}

void howToPlayScreen::draw()
{
    helpBase::draw();
    addTitle("How to play");
    addParagraph("It's a turn-based game, where two medieval kingdoms (the two player) try to "
                 "overpower each other. As it was invented on boring lessons, it's played on a sqare grid. Your"
                 " final aim is to destroy all the stongholds of your opponent. To achieve that in each turn"
                 " you can either build or start an assault. Let's see what objects can you build! ");
    addParagraph("Barracks: their point is to provide soldiers for your "
                 "strongholds. Marker: rombus with the owner player's pattern. ");
    addParagraph("Stronghold bases: they can be strongholds later... Marker: square. ");
    addParagraph("Roads: you can connect objects, by using roads. You can "
                 "build north-, east-, south-, and west roads. Marker: blue line from middle to edge. ");
    addParagraph("In one turn you can build: 1 barrack/1 stronghold base/4 roads. You can't build to enemy"
                 "  territory. Exception: in the first turn, the second player can build plus 2 roads. ");
}

