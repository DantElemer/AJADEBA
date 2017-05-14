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
    addParagraph("In this turn-based game two medieval kingdoms under the command of the two players try to "
                 "overpower each other. As it was invented on boring lectures, it's played on a sqare grid. Your"
                 " final objective is to destroy all stongholds of your opponent. To achieve that each turn"
                 " you can either build something or start an assault. Let's see what objects you can build! ");
    addParagraph("Barracks: they provide soldiers for your "
                 "strongholds. Marker: rhombus with the owner player's pattern. ");
    addParagraph("Stronghold bases: they can be built into strongholds later. Marker: square. ");
    addParagraph("Roads: connect objects by using roads. You can "
                 "build north, east, south, and west roads. Marker: blue line from middle to edge. ");
    addParagraph("In one turn you can build: 1 barrack/1 stronghold base/4 roads. You cannot build on enemy"
                 "  territory, with one exception: in the first turn, the second player can build an extra 2 roads. ");
}

