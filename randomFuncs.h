//A set of useful functions.

#ifndef RANDOMFUNCS_H_INCLUDED
#define RANDOMFUNCS_H_INCLUDED

#include <time.h>
#include <math.h>
#include <sstream>
#include <string>

#include "coor.h"

#include "graphics.hpp"

using namespace genv;

int egyRohadtRendesKerekites(double pusztuljMeg); //uses normal math (probably it was written before me, but never mind)
void giveMeTime(double t); //waits for @t seconds
std::string numToString(double num); //converts number to string


#endif // RANDOMFUNCS_H_INCLUDED
