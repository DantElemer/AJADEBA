#include "complexIndicator.h"

complexIndicator::complexIndicator(coor origo, double &value, double minValue, double maxValue, int accuracy, string title, bool ledded, double aimValue, string minMaxAbs, double radius, int fSize)
: widgetBase(origo-makeCoor(radius,radius), origo+makeCoor(radius,radius)),
needly(origo, value, minValue, maxValue, radius),
doubly(origo+makeCoor(-50,50), origo+makeCoor(50,70), title, value, fSize, accuracy),
ledy(downerRightCorner+makeCoor(-15,-15), value, aimValue, minMaxAbs),
ledded(ledded)
{

}

void complexIndicator::update()
{
    needly.update();
    doubly.update();
    if (ledded)
        ledy.update();
}

