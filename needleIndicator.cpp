#include "needleIndicator.h"

needleIndicator::needleIndicator(coor origo, double &value, double minValue, double maxValue, double radius)
: widgetBase(origo-makeCoor(radius,radius), origo+makeCoor(radius,radius)), origo(origo), value(&value), MIN_VALUE(minValue), MAX_VALUE(maxValue), radius(radius)
{
    value=0;
    draw();
}

void needleIndicator::drawMarkers()
{
    gout<<color(255,255,255);
    int numOfMs=15;
    double r1=radius-5;
    double r2=r1-10;
    double alpha=2.3;
    double deltaAlpha=2*alpha/(double)(numOfMs-1);
    for (int i=0;i<numOfMs;i++)
    {
        double currAlp=-alpha+deltaAlpha*i-1.57;
        gout<<move_to(origo.X+cos(currAlp)*r1,origo.Y+sin(currAlp)*r1)<<line_to(origo.X+cos(currAlp)*r2,origo.Y+sin(currAlp)*r2);
    }
}

void needleIndicator::drawNeedle()
{
    double helper=(*value-MIN_VALUE)/(MAX_VALUE-*value);
    double currAlpha=helper*2*alpha/(1.0+helper)-alpha-1.57;
    double r=radius-10;
    gout<<color(255,0,0)<<move_to(origo.X,origo.Y)<<line_to(origo.X+r*cos(currAlpha),origo.Y+r*sin(currAlpha));
}

void needleIndicator::draw()
{
    drawCircle(origo,radius);
    drawMarkers();
    drawCircle(origo,5,100);
    drawNeedle();
}

void needleIndicator::update()
{
    redraw();
}
