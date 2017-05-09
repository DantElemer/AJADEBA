#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "../screen.h"
#include "../gameScreen/Fields/field objects/fieldObject.h"
#include "../gameScreen/Fields/field.h"

#include <fstream>


class mapEditor : public screen
{
    public:
        mapEditor();
        void draw();
        void save();

        static const int FIELD_WIDTH=field::WIDTH; //=field height as well
        static const coor MAP_OFFSET;
        int currOwner=-1;
        string currPart;
    private:
        void generateFields();

        static const int MAX_WIDTH=40;
        static const int MAX_HEIGHT=25;

};

#endif // MAPEDITOR_H
