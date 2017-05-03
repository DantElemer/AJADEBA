#ifndef INDICATOR_H_INCLUDED
#define INDICATOR_H_INCLUDED

#include "../graphicsPlus.h"
#include "../coor.h"
#include "widgetBase.h"

//Displays a variable's value.
class indicator : public widgetBase
{
    public:
        indicator(coor upperLeftCorner, coor downerRightCorner, string texty, int fSize=12);
        virtual ~indicator(){};
        void update();


    protected:
        string texty;
        int fontSize;

        virtual void draw();
        virtual void redraw();
};

#endif // INDICATOR_H_INCLUDED
