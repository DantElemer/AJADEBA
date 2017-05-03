#include "alphaDone.h"

alphaDone::alphaDone()
{
    draw();
}

void alphaDone::draw()
{
    fCutscene::draw();
    coor messageStart=WINDOW_ORIGO-makeCoor(40,40);
    int lineDist=20;
    writeText(messageStart,"Congratulations!",15);
    writeText(messageStart+makeCoor(0,lineDist),"You have successfully tested",15);
    writeText(messageStart+makeCoor(0,lineDist)*2,"rotation!",15);
    writeText(messageStart+makeCoor(0,lineDist)*3,"Keep up the good work!",15);
}
