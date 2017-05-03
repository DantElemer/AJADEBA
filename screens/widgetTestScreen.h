#ifndef WIDGETTESTSCREEN_H
#define WIDGETTESTSCREEN_H

#include "screen.h"

//for testing widgets...
class widgetTestScreen : public screen
{
    public:
        widgetTestScreen();
        void draw();
        void keyDown(event kE);
    protected:
    private:
        static void sIzelj(widgetTestScreen* wTS);
        void izelj();

        double num=10;
        string izeke;
        bool isNum=true;
};

#endif // WIDGETTESTSCREEN_H
