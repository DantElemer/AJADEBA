#include "atStart.h"

atStart::atStart()
{
    draw();
}

void atStart::draw()
{
    fCutscene::draw();
    coor messageStart=WINDOW_ORIGO-makeCoor(40,40);
    int lineDist=20;
    //writeText(messageStart+makeCoor(0,lineDist)*3,"An euforistic fantasy dimension gate",15);
    writeText(messageStart,"Pilot! Your task is to test the",15);
    writeText(messageStart+makeCoor(0,lineDist),"helikoffer. As you know its rotor has",15);
    writeText(messageStart+makeCoor(0,lineDist)*2,"a quark continuity-based quantum",15);
    writeText(messageStart+makeCoor(0,lineDist)*3,"reactored quadrocuspidal",15);
    writeText(messageStart+makeCoor(0,lineDist)*4,"hypocyloid transformer. ",15);
    writeText(messageStart+makeCoor(0,lineDist)*5,"So you can fly in space -in theory",15);
    writeText(messageStart+makeCoor(0,lineDist)*6,"at least-. Good luck!",15);
    //Quantum-based Quark continuity reactor quad kuszpidális hypocycloid transformer
}


