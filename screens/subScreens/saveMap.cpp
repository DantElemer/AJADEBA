#include "saveMap.h"
#include "../others/mapEditor.h"

saveMap::saveMap(mapEditor* myEditor)
: tField(WINDOW_ORIGO-makeCoor(50,120),WINDOW_ORIGO-makeCoor(-50,80),20,"map name")
{
    int wid=100;
    int hei=40;
    int start=100;
    int dist=50;
    widgets.push_back(&tField);
    widgets.push_back(new lButton([myEditor,this](){myEditor->save("maps/"+this->tField.myText+".txt");},WINDOW_ORIGO-makeCoor(0,start-dist),wid,hei,"Save&Quit"));
    draw();
}

void saveMap::draw()
{
    darkening();
    clearScreen(WINDOW_ORIGO-makeCoor(100,150),WINDOW_ORIGO+makeCoor(100,150));
    //addTitle("Saving...");
}
