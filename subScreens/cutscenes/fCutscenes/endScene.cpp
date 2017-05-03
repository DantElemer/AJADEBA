#include "endScene.h"

endScene::endScene()
{
    draw();
}

void endScene::draw()
{
    fCutscene::draw();
    coor messageStart=WINDOW_ORIGO-makeCoor(40,40);
    int lineDist=20;
    //writeText(messageStart,"Congratulations!",15);
    writeText(messageStart+makeCoor(0,lineDist)*0,"You have finished all the tests!",15);
    writeText(messageStart+makeCoor(0,lineDist)*1,"However... we have a problem.",15);
    writeText(messageStart+makeCoor(0,lineDist)*2,"An euforistic fantasy dimension gate",15);
    writeText(messageStart+makeCoor(0,lineDist)*3,"has just opened nearby.",15);
    writeText(messageStart+makeCoor(0,lineDist)*4,"It seems that our technology has",15);
    writeText(messageStart+makeCoor(0,lineDist)*5,"caused some side effects in other",15);
    writeText(messageStart+makeCoor(0,lineDist)*6,"dimensions. We are under attack.",15);
}

void endScene::terminateSub()
{
    switchTo=MENU_SCREEN;
}

void endScene::keyDown(event kE)
{
    screen::keyDown(kE);
    if (kE.keycode!=key_escape)
        terminateSub();
}
