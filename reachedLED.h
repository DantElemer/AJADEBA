#ifndef REACHEDLED_H
#define REACHEDLED_H

#include "widgetBase.h"
#include "../graphicsPlus.h"

//a LED which glows if a given variable's value is "correct"
class reachedLED : public widgetBase
{
    public:
        bool reached=false;

        reachedLED(coor upperLeftCorner, double &value, double aimValue, string minMaxAbs="abs");
        ~reachedLED();
        void update();
        void draw();
    protected:
    private:
        double *value;
        const double AIM_VALUE;
        string minMaxAbs;
        canvas onPic;
        canvas offPic;

        void generateCanvases(canvas &onP);
        void check();
};

#endif // REACHEDLED_H
