#include "field.h"
#include "../gameScreen.h"

const string field::BLANK="blank";

field::field(gameScreen* gS, coor origo)
: myGameScreen(gS), origo(origo), type(BLANK)
{
    gS->widgets.push_back(new lButton([this](){this->myGameScreen->fieldClicked(this);},origo,WIDTH,WIDTH));
}

field::~field()
{
    //dtor
}

void field::draw()
{
    drawRectangle(origo-makeCoor(WIDTH/2,WIDTH/2),origo+makeCoor(WIDTH/2,WIDTH/2));
}
