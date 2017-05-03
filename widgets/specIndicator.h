#ifndef SPECINDICATOR_H_INCLUDED
#define SPECINDICATOR_H_INCLUDED

#include "indicator.h"
#include "widgetBase.h"

//Displays a double variable's value.
class doubleIndicator : public indicator
{
    public:
        doubleIndicator(coor upperLeftCorner, coor downerRightCorner, string texty, double &value, int fSize=12, int accuracy=2);
        void draw();
    private:
        double* value;
        int accuracy;
};

#endif // SPECINDICATOR_H_INCLUDED
