#include "fCutscene.h"

fCutscene::fCutscene()
{
    generatePics();
    const int WIDTH=95;
    const int HEIGHT=130;
    widgetBase* ani=new animation(WINDOW_ORIGO+makeCoor(-100-WIDTH/2,-HEIGHT/2+30),WINDOW_ORIGO+makeCoor(-100+WIDTH/2,HEIGHT/2+30),pics);
    widgets.push_back(ani);
    draw();
}

void fCutscene::generatePics()
{
    canvas nPic;
    generateCanvas(nPic,"pics/flugi2.kep",true);
    pics.push_back(nPic);
    canvas nPic2;
    generateCanvas(nPic2,"pics/flugi2b.kep",true);
    pics.push_back(nPic2);
}

void fCutscene::draw()
{
    cutscene::draw();
    addTitle("HQ message");
}




