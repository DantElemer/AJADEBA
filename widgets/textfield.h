#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "widgetBase.h"

#include <string>


class textfield : public widgetBase
{
    public:
        textfield(coor upperLeftCorner, coor downerRightCorner, int fontSize=12, string text="");
        virtual ~textfield();

        string myText;

    protected:

        int fontSize;
        bool cursorIn;
        static const int DIST_FROM_EDGE=3;

        void mouseUp();
        void keyDown(event kE);
        void draw();
        void update();
        //virtual void mouseDown();
    private:
};

#endif // TEXTFIELD_H
