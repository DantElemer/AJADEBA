#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "../screen.h"


class mapEditor : public screen
{
    public:
        mapEditor();
        void draw();
    private:
        static const int MAX_WIDTH=40;
        static const int MAX_HEIGHT=25;
        static const int FIELD_WIDTH=20; //=field height as well
};

#endif // MAPEDITOR_H
