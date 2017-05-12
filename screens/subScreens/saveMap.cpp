#include "saveMap.h"
#include "../others/mapEditor.h"

saveMap::saveMap(mapEditor* myEditor)
: tField(WINDOW_ORIGO-makeCoor(70,160),WINDOW_ORIGO-makeCoor(-70,130),20,"map name")
{
    int wid=200;
    int hei=40;
    int start=130;
    int dist=50;
    int fSize=30;
    widgets.push_back(&tField);
    widgets.push_back(new lButton([myEditor,this](){myEditor->save(this->tField.myText);switchToMenuScreen();},WINDOW_ORIGO-makeCoor(0,start-dist),wid,hei,"Save&Quit",fSize));
    widgets.push_back(new lButton([myEditor,this](){myEditor->save(this->tField.myText);terminateSub();},WINDOW_ORIGO-makeCoor(0,start-2*dist),wid,hei,"Save",fSize));
    widgets.push_back(new lButton([myEditor,this](){switchToMenuScreen();},WINDOW_ORIGO-makeCoor(0,start-3*dist),wid,hei,"Quit",fSize));
    widgets.push_back(new lButton([myEditor,this](){terminateSub();},WINDOW_ORIGO-makeCoor(0,start-4*dist),wid,hei,"Cancel",fSize));
    widgets.push_back(new checkbox(WINDOW_ORIGO-makeCoor(20,start-5*dist+10),WINDOW_ORIGO-makeCoor(-20,start-5*dist-30),myEditor->generateDescFile));
    draw();
}

void saveMap::draw()
{
    darkening();
    coor uLC=WINDOW_ORIGO-makeCoor(130,170);
    coor dRC=WINDOW_ORIGO+makeCoor(130,170);
    clearScreen(uLC,dRC);
    addFrame(uLC,dRC);

    screen::draw();
    //addTitle("Saving...");
}
