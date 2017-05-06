#include "subScreen.h"

const string subScreen::CANCEL="cancel";

subScreen::subScreen()
{

}

void subScreen::terminateSub()
{
    switchTo=TERMINATED;
}
