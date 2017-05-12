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
    clearScreen();
    addTitle("How to play");
    coor startPoint=makeCoor(50,150);
    int fSize=18;
    int height=0;
    int bekezdDist=30;
    int lines;
    lines=lWriteText(startPoint,"It's a turn-based game, where two medieval kingdoms (the two player) try to "
                     "overpower each other. As it was on boring lessons, it's played on a sqare grid?????. Your final aim "
                     "is to destroy all the stongholds of your opponent. To achieve that in each turn you "
                     "can either build or start an assault. Let's see what objects can be in a game! ",WINDOW_X-2*startPoint.X,fSize);
    height+=lines*countTextHeight("I",fSize)+bekezdDist;

    lines=lWriteText(startPoint+makeCoor(0,height),"Villages: they are on the map from start to end, can't be built or be destroyed."
                     " They provide people for your barracks, and for your opponent's barracks, as they never belong to one"
                     " specific player. Marker: circle.",WINDOW_X-2*startPoint.X,fSize);
    height+=lines*countTextHeight("I",fSize)+bekezdDist;
    lines=lWriteText(startPoint+makeCoor(0,height),"Barracks: some can be on the map at start, but most of them is built by the players, and"
                     "they can be destroyed. Their point is to provide soldiers for your strongholds. Marker: rombus"
                     " with the owner player's pattern.",WINDOW_X-2*startPoint.X,fSize);
    height+=lines*countTextHeight("I",fSize)+bekezdDist;
    lines=lWriteText(startPoint+makeCoor(0,height),"Strongholds: some can be on the map at start, but most of them is built by the players, and"
                     "they can be destroyed. They have territory, where enemy cannot build, "
                     "you can start assaults from them. Marker: square"
                     " with the owner player's pattern. ",WINDOW_X-2*startPoint.X,fSize);
    height+=lines*countTextHeight("I",fSize)+bekezdDist;

    screen::draw();
}

