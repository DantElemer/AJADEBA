#include "saveMap.h"
#include "../others/mapEditor.h"

saveMap::saveMap(mapEditor* myEditor)
: tField(WINDOW_ORIGO-makeCoor(50,140),WINDOW_ORIGO-makeCoor(-50,100),20,"map name")
{
    int wid=200;
    int hei=40;
    int start=100;
    int dist=50;
    widgets.push_back(&tField);
    widgets.push_back(new lButton([myEditor,this](){myEditor->save(this->tField.myText);switchToMenuScreen();},WINDOW_ORIGO-makeCoor(0,start-dist),wid,hei,"Save&Quit"));
    widgets.push_back(new lButton([myEditor,this](){myEditor->save(this->tField.myText);terminateSub();},WINDOW_ORIGO-makeCoor(0,start-2*dist),wid,hei,"Save"));
    widgets.push_back(new lButton([myEditor,this](){switchToMenuScreen();},WINDOW_ORIGO-makeCoor(0,start-3*dist),wid,hei,"Quit"));
    widgets.push_back(new lButton([myEditor,this](){terminateSub();},WINDOW_ORIGO-makeCoor(0,start-4*dist),wid,hei,"Cancel"));

    draw();//TODO other options
}

void saveMap::draw()
{
    darkening();
    clearScreen(WINDOW_ORIGO-makeCoor(130,150),WINDOW_ORIGO+makeCoor(130,150));
    //addTitle("Saving...");
}
