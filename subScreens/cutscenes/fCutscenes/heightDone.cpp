#include "heightDone.h"

heightDone::heightDone()
{
    draw();
}

void heightDone::draw()
{
    fCutscene::draw();
    coor messageStart=WINDOW_ORIGO-makeCoor(40,40);
    int lineDist=20;
    writeText(messageStart,"Congratulations!",15);
    writeText(messageStart+makeCoor(0,lineDist),"You have successfully reached test",15);
    writeText(messageStart+makeCoor(0,lineDist)*2,"height!",15);
    writeText(messageStart+makeCoor(0,lineDist)*3,"Keep up the good work!",15);
}
