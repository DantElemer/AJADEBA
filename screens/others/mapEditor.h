#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "../screen.h"
#include "../gameScreen/Fields/field objects/fieldObject.h"
#include "../gameScreen/Fields/field.h"
#include "../../Picture.h"

#include <fstream>
#include <algorithm>


class mapEditor : public screen
{
    public:
        mapEditor();
        void draw();
        void save();
        void onTick();

        static const int FIELD_WIDTH=field::WIDTH; //=field height as well
        static const coor MAP_OFFSET;
        int currOwner=-1;
        string currPart="village";
    private:
        void generateFields();
        void drawMarkers();

        static const int MAX_WIDTH=40;
        static const int MAX_HEIGHT=25;


        int dist=30;
        int oDistFromEdgeY=50;
        int oDistFromEdgeX=60;
        int wid=100;
        int hei=30;
        int fSize=20;
        int cutDist=20;
        int cutNum=0;
        int obStart;
        int playerStart;
};

#endif // MAPEDITOR_H
