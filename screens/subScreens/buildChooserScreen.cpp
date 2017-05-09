#include "buildChooserScreen.h"
#include "../gameScreen/gameScreen.h"

buildChooserScreen::buildChooserScreen(gameScreen* gS)
: gS(gS)
{
    draw();
    generateOptions();
    showOptions();
}

void buildChooserScreen::draw()
{
    //darkening();
    //addTitle("Build chooser");
}

void buildChooserScreen::generateOptions()
{
    for (string object:fieldObject::EVERY_OBJECT)
        if (gS->selectedField->canBuild(object))
            options.push_back(object);
    options.push_back(CANCEL);
}

void buildChooserScreen::showOptions()
{
    for (int i=0;i<options.size();i++)
        widgets.push_back(new lButton([this,i]()
                                      {
                                          this->gS->whatToBuild=this->options[i];
                                          this->terminateSub();
                                          this->gS->justBuilt=true;
                                       },
                                       makeCoor(WINDOW_X-200,100+i*50),100,40,options[i],20));
}

void buildChooserScreen::onTick()
{
    screen::onTick();
    gS->decreasePlayerTime();
    if (gS->currentPlayer->timeLeft<=0)
    {
        gS->justBuilt=false; //it's not needed
        terminateSub();
    }
}
