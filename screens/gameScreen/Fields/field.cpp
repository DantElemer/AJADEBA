#include "field.h"
#include "../gameScreen.h"

field::field(gameScreen* gS, coor origo)
: myGameScreen(gS), origo(origo)
{
    gS->widgets.push_back(new lButton([this](){cout<<this->origo.X;},origo,WIDTH/2,WIDTH/2));
}

field::~field()
{
    //dtor
}

void field::draw()
{
    drawRectangle(origo-makeCoor(WIDTH/2,WIDTH/2),origo+makeCoor(WIDTH/2,WIDTH/2));
}
