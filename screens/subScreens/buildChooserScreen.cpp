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
    screen::draw();
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
    /*int delta=50;
    coor startPoint=gS->selectedField->origo+makeCoor(70,-(double)(options.size()-1)/2.0*delta);
    for (int i=0;i<options.size();i++)
        widgets.push_back(new lButton([this,i]()
                                      {
                                          this->gS->whatToBuild=this->options[i];
                                          this->terminateSub();
                                          this->gS->justBuilt=true;
                                       },
                                       startPoint+makeCoor(0,i*delta),100,40,options[i],20));*/
    int radius=80;
    double pi=3.14159265;
    double deltaAlpha=2*pi/(double)options.size();
    coor middle=gS->selectedField->origo;
    for (int i=0;i<options.size();i++)
    {
        double picWidth=50.0;
        lButton* option=new lButton([this,i]()
                                      {
                                          this->gS->whatToBuild=this->options[i];
                                          this->terminateSub();
                                          this->gS->justBuilt=true;
                                       },
                                       middle+makeCoor(cos(i*deltaAlpha),sin(i*deltaAlpha))*radius,picWidth,picWidth);
        widgets.push_back(option);
        Picture pic("pics/game objects/"+options[i]+".kep",option->origo);
        double scX=picWidth/pic.NORMAL_WIDTH;
        double scY=picWidth/pic.NORMAL_HEIGHT;
        option->addPicture("pics/game objects/"+options[i]+".kep",scX,scY);
    }

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
