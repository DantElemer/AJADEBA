#ifndef NEEDLEINDICATOR_H
#define NEEDLEINDICATOR_H

#include "widgetBase.h"
#include "../coor.h"
#include "../graphicsPlus.h"

//displaying a value with a needle
class needleIndicator : public widgetBase
{
    public:
        needleIndicator(coor origo,  double &value, double minValue, double maxValue, double radius=90);
        void update();
    //protected:
    private:
        double* value;
        double const MAX_VALUE;
        double const MIN_VALUE;
        double radius;
        coor origo;
        double alpha=2.3;

        void draw();
        void drawMarkers();
        void drawNeedle();
};

#endif // NEEDLEINDICATOR_H
