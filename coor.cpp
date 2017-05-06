#include "coor.h"
#include "graphics.hpp"

using namespace std;
using namespace genv;


void coor::operator= (coor to)
{
    X=to.X;
    Y=to.Y;
}

void coor::operator+= (coor ezt)
{
    X+=ezt.X;
    Y+=ezt.Y;
}

coor coor::operator+ (coor ezt) const
{
    coor v=*this;
    v.X+=ezt.X;
    v.Y+=ezt.Y;
    return v;
}

coor coor::operator* (double ezzel) const
{
    coor v=*this;
    v.X*=ezzel;
    v.Y*=ezzel;
    return v;
}

coor coor::operator/ (double ezzel) const
{
    return *this*(1/ezzel);
}

void coor::operator-= (coor ezt)
{
    X-=ezt.X;
    Y-=ezt.Y;
}

coor coor::operator- (coor ezt) const
{
    coor v=*this;
    v.X-=ezt.X;
    v.Y-=ezt.Y;
    return v;
}

void coor::operator/= (coor ezzel)
{
    X/=ezzel.X;
    Y/=ezzel.Y;
}

void coor::operator*= (double ezzel)
{
    X*=ezzel;
    Y*=ezzel;
}

bool coor::operator> (coor ezzel) const
{
    if (X>ezzel.X&&Y>ezzel.Y)
        return true;
    return false;
}

bool coor::operator< (coor ezzel) const
{
    if (X<ezzel.X&&Y<ezzel.Y)
        return true;
    return false;
}

bool coor::operator== (coor ezzel) const
{
    if (X==ezzel.X&&Y==ezzel.Y)
        return true;
    return false;
}

coor coor::operator- (double ezt) const
{
    coor v=*this;
    v.X-=ezt;
    v.Y-=ezt;
    return v;
}

coor coor::operator+ (double ezt) const
{
    coor v=*this;
    v.X+=ezt;
    v.Y+=ezt;
    return v;
}

void coor::movePoint(coor xy) //adds @xy to @point (you can do the same by using the coor + operator)
{
    *this+=xy;
}

void coor::origonizePoint(coor origo)
{
    *this-=origo;
}

void coor::deOrigonizePoint(coor origo)
{
    *this+=origo;
}

void coor::rotatePoint(coor origo, double alpha) //global, rotates @point's coordinates around @origo by @alpha (based on complex numbers)
{
    origonizePoint(origo); //as we rotate around @origo, not around the upper-left corner
    double i=sin(alpha); //imaginary
    double r=cos(alpha); //real

    double newX=r*X-i*Y; //believe, or do some math
    double newY=r*Y+i*X;
    *this=makeCoor(newX,newY);
    deOrigonizePoint(origo); //needed to "undo" first line
}

void coor::growPoint(coor origo, double lambda)
{
    origonizePoint(origo);
    *this*=lambda;
    deOrigonizePoint(origo);
}

bool coor::inRect(coor upLeftCorn, coor downRightCorn) //is in the rectangle (defined by it's up-left and down-right corners)
{
    if (*this>upLeftCorn&&*this<downRightCorn)
        return true;
    return false;
}

bool coor::inWindow()
{
    return this->inRect(makeCoor(0,0),WINDOW_ORIGO*2);
}
//=============================================================================================

coor makeCoor(double x, double y) //converts to coor
{
    coor newCoor={x,y};
    return newCoor;
}

void readCoordinatesIntoVector(string fName, vector<coor>& co) //into a coor vector (assuming whitespace )
{
    ifstream iF (fName);
    double i,j;
    while (iF>>i && iF>>j)
    {
        co.push_back(makeCoor(i,j));
    }
    iF.close();
}

void putPoint(coor c/*, char wc*/) //prints a @wc char to the given coordinates (@c)
{
    if (c.inRect(makeCoor(0,0),makeCoor(WINDOW_X,WINDOW_Y)))
        gout<<color(255,255,255)<<move_to(c.X,c.Y)<<box(2,2);
}

//from here there are some "useless" fuctions, they are exist because of historical reasons and because their name can help understand the codeparts which use them
void putPoints(const vector<coor> co/*, char wc*/) //prints @wc chars to the given coordinates
{
    for (coor c:co)
    {
        putPoint(c/*,wc*/);
    }
}

void movePoints(vector<coor> &v, coor xy) //adds @xy to the coors in the vector
{
    for (coor &c:v)
    {
        c.movePoint(xy);
    }
}

void origonize(coor origo, vector<coor> &co)
{
    for (coor &c:co)
    {
        c.origonizePoint(origo);
    }
}

void deOrigonize(coor origo, vector<coor> &co)
{
    for (coor &c:co)
    {
        c.deOrigonizePoint(origo);
    }
}
//end of "useless" functions

void rotatePoints(coor origo, vector<coor> &co, double alpha) //global, rotatePoint(...), on a vector
{
    for (coor &c:co)
    {
        c.rotatePoint(origo,alpha);
    }
}

void affinite(coor origo, vector<coor>& v,coor dirVector,double lambda) //affinites points, affinity-axis is defined by @dirVector (aff-axis is perpendicular to it, sample: dirVector is (0,1), then it's an affinity to x axis)
{
    origonize(origo,v); //as we affinite to an axis going through @origo (which is not necessarily the upper-left corner)
    if (dirVector.X*dirVector.Y==0) //affinity to axis x or y
    {
        for (coor &p:v)
        {
            if (dirVector.X==0)
                p/=makeCoor(1.0/lambda,1);
            else
                p/=makeCoor(1, 1.0/lambda);
        }
    }
    else //math...
    {
        for (coor &p:v)
        {
            double marci = dirVector.Y/dirVector.X;
            double xHelp= (p.Y + 1.0/marci * p.X)/(marci+1.0/marci);
            double yHelp= marci*xHelp;
            p.X=xHelp*(1-lambda)+p.X*lambda;
            p.Y=yHelp*(1-lambda)+p.Y*lambda;
        }
    }
    deOrigonize(origo,v); //needed to "undo" first line
}

void growPoints(coor origo, vector<coor>& v, double lambda)
{
    for (coor &c:v)
        c.growPoint(origo,lambda);
}


