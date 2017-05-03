#include "specIndicator.h"


doubleIndicator::doubleIndicator(coor uLC, coor dLC, string texty, double &value, int fSize, int accuracy)
: indicator(uLC, dLC, texty, fSize), value(&value), accuracy(accuracy)
{

}

void doubleIndicator::draw()
{
    indicator::draw(); //name

    printText(numToString((float)egyRohadtRendesKerekites(*value*pow(10,accuracy))/(float)pow(10,accuracy)));
}

/*void specIndicator::redraw()
{

}*/

/*void specIndicator::update()
{

}*/
