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
    int radius=100;
    double picWidth=60.0;
    double pi=3.14159265;
    double deltaAlpha=2*pi/(double)options.size();
    coor middle=gS->selectedField->origo;
    middle.X=max(min(middle.X,WINDOW_X-radius-picWidth/2.0-5),radius+picWidth/2.0+5);
    middle.Y=max(min(middle.Y,WINDOW_Y-radius-picWidth/2.0-5),radius+picWidth/2.0+5);
    for (int i=-1;i<2;i++)
        drawCircle(middle,radius+i);
    for (int i=0;i<options.size();i++)
    {
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
