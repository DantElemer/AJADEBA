#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "../coor.h"
#include "../randomFuncs.h"
#include "../graphicsPlus.h"
#include "widgetBase.h"
#include "../Picture.h"

typedef void (* vFunctionCall)();
//Well, it's a button.
class button : public widgetBase
{
    public:
        button(vFunctionCall fire, coor upperLeftCorner, coor downerRightCorner, string texty="", int fontSize=40);
        button(vFunctionCall fire, coor origo, double width, double height, string texty="", int fontSize=40);
        virtual ~button(){};
        void check();
        void redraw();
        void mouseDown();
        void mouseUp();
        void update();
        void addText(string text);

        void addPicture(string picName, double scaleX=1, double scaleY=1);

    protected:
        vFunctionCall funcToStart;
        string myText;
        Picture myPic;
        bool hasPic=false;
        bool mouseAbove=false;
        bool mouseChosen=false;
        int borderDiff=4;
        int fontSize;
        double const MAX_TIMES=1.2; //how many times bigger it can be
        double const GROW_RATE=1.05; //how fast it grows
        double currentTimes=1.0; //how many times it's bigger currently


        void draw();
        virtual void fireFunction();
        void growEffect();
        void nullGrowEffect();
};

#endif // BUTTON_H_INCLUDED
