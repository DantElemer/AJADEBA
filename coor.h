#ifndef COOR_H_INCLUDED
#define COOR_H_INCLUDED

int egyRohadtRendesKerekites(double pusztuljMeg);

#include "data.h"

#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <iostream>


using namespace std;

//A pair of doubles.
struct coor
{
    double X;
    double Y;
    void operator= (coor to);
    void operator+= (coor ezt);
    coor operator+ (coor ezt) const;
    coor operator* (double ezzel) const;
    coor operator/ (double ezzel) const;
    void operator-= (coor ezt);
    coor operator- (coor ezt) const;
    coor operator+ (double ezt) const;
    coor operator- (double ezt) const;
    void operator/= (coor ezzel); //"x/x, y/y"
    void operator*= (double ezzel);
    bool operator> (coor ezzel) const;
    bool operator< (coor ezzel) const;
    bool operator== (coor ezzel) const;

    void movePoint(coor xy); //adds @xy to coor (you can do the same by using the coor + operator)
    void origonizePoint(coor origo);
    void deOrigonizePoint(coor origo);
    void rotatePoint(coor origo, double alpha); //...
    void growPoint(coor origo, double lambda); //enlargement from point
    bool inRect(coor upLeftCorn, coor downRightCorn); //is out of the rectangle (defined by it's up-left and down-right corners)
    bool inWindow(); //is out of the window
};



coor makeCoor(double x, double y); //converts to coor
void readCoordinatesIntoVector(string fName, vector<coor>& co); //into a coor vector (assuming whitespace )
void putPoint(coor c/*, char wc='.'*/); //prints a @wc char to the given coordinates
//from here there are some "useless" fuctions, they are exist because of historical reasons and because their name can help understand the codeparts which use them
void putPoints(const vector<coor> co/*, char wc='.'*/); //prints @wc chars to the given coordinates
void movePoints(vector<coor> &v, coor xy); //adds @xy to the coors in the vector;
void origonize(coor origo, vector<coor> &co);
void deOrigonize(coor origo, vector<coor> &co);
//end of "useless" functions
 //global, rotates @point's coordinates around @origo by @alpha (based on complex numbers)
void rotatePoints(coor origo, vector<coor> &co, double alpha); //global, rotatePoint(...), on a vector
void affinite(coor origo, vector<coor>& v,coor dirVector,double lambda); //affinites points, axis is defined by @dirVector (axis is perpendicular to it)
void growPoints(coor origo, vector<coor>& v, double lambda); //...
#endif // COOR_H_INCLUDED
