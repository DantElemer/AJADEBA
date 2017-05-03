#include "randomFuncs.h"

using namespace genv;


int egyRohadtRendesKerekites(double pusztuljMeg) //uses normal math...
{
    int paraszt;
    if (pusztuljMeg-(int)pusztuljMeg<0.5)
    {
        paraszt=(int) pusztuljMeg;
    }
    else
    {
        paraszt=(int) pusztuljMeg +1;
    }
    return paraszt;
}

void giveMeTime(double t) //waits for @t seconds
{
    int tim=clock();
    while (clock()<=tim+t*1000);
}

char setSymbol(double alpha) //returns the appropriate symbol based on the (rotor's) @alpha (addvice for @alpha: atan2(deltaY,deltaX) )
{
    double pi=atan(1)*4;
    double piPerNyoc=pi/8.0;

    if ((alpha>=7.0 * piPerNyoc) || ((alpha >= -piPerNyoc)&&(alpha <= piPerNyoc)) || (alpha <= -7.0 * piPerNyoc))
        return '_';
    else if ( ( (alpha < 7.0 * piPerNyoc) && (alpha > 5.0 * piPerNyoc) ) || ( (alpha < -piPerNyoc) && (alpha > -3.0 * piPerNyoc) ) )
        return '/';
    else if ( ( (alpha <= 5.0 * piPerNyoc) && (alpha >= 3.0 * piPerNyoc) ) || ( (alpha >= -5.0 * piPerNyoc) && (alpha <= -3.0 * piPerNyoc) ) )
        return '|';
    else
        return '\\'; // it's a simple backslash
}

string numToString(double num)
{
    string ret;
    stringstream ss;
    ss<<num;
    ss>>ret;
    return ret;
}
