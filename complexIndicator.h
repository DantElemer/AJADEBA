#ifndef COMPLEXINDICATOR_H
#define COMPLEXINDICATOR_H

#include "widgetBase.h"
#include "needleIndicator.h"
#include "specIndicator.h"
#include "reachedLED.h"

//needle, LED, doubleIndicator
class complexIndicator : public widgetBase
{
    public:
        complexIndicator(coor origo, double &value, double minValue, double maxValue, int accuracy=2, string title="", bool ledded=false, double aimValue=0, string minMaxAbs="abs", double radius=90, int fSize=12);
        void update();
    protected:
    private:
        needleIndicator needly;
        doubleIndicator doubly;
        reachedLED ledy;
        bool ledded;

};

#endif // COMPLEXINDICATOR_H
