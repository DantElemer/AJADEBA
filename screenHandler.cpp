#include "screenHandler.h"

void screenHandler::exitGame()
{
    exitAwesomeness=true;
}

void screenHandler::switchScreen(screen *&currScr)
{
    delete currScr;
    clearScreen();
    if (screen::switchTo==screen::GAME_SCREEN)
        currScr=new gameScreen();
    else if (screen::switchTo==screen::MENU_SCREEN)
        currScr=new menuScreen();
    else if (screen::switchTo==screen::GAME_OVER_SCREEN)
        currScr=new gameOverScreen();
    else if (screen::switchTo==screen::VICTORY_SCREEN)
        currScr=new victoryScreen();
    else if (screen::switchTo==screen::DIFFICULTY_SETTING_SCREEN)
        currScr=new difficultySettingScreen();
    if (screen::switchTo==screen::WIDGET_TEST_SCREEN)
        currScr=new widgetTestScreen();
    else if (screen::switchTo==screen::TERMINATED)
    {
        screensAlive.pop_back();
        exitReqested=false;
        for (screen* s:screensAlive) //drawing screens
        {
            s->draw();
            s->onTick(); //for drawing nonstatic objects
        }
    }
    else if (screen::switchTo==screen::EXIT)
        exitGame();
    if (screen::switchTo!=screen::TERMINATED)
    {
        for (int i=screensAlive.size()-1;i>=1;i--)
        {
            delete screensAlive[i];
            screensAlive.pop_back();
        }
        screensAlive.pop_back(); //takes out "current screen", which was deleted above
        screensAlive.push_back(currScr);
    }
    screen::switchTo=screen::STAY;

}

void screenHandler::addSub(string newSubName)
{
    screen* currScr;
    if (newSubName==screen::CONFIRM_EXIT)
    {
        if (exitReqested)
            exitGame();
        else
        {
            currScr=new confirmExitScreen();
            exitReqested=true;
        }
    }
    else if (screen::newSub==screen::HOW_TO_PLAY_SCREEN)
        currScr=new howToPlayScreen();
    else if (screen::newSub==screen::BUILD_CHOOSER_SCREEN)
        currScr=new buildChooserScreen((gameScreen*)screensAlive[screensAlive.size()-1]);
    /*else if (screen::newSub==screen::AT_START)
        currScr=new atStart();
    else if (screen::newSub==screen::ALPHA_DONE)
        currScr=new alphaDone();
    else if (screen::newSub==screen::HEIGHT_DONE)
        currScr=new heightDone();
    else if (screen::newSub==screen::END_SCENE)
        currScr=new endScene();*/
    screensAlive.push_back(currScr);
    screen::newSub=screen::STAY;
}

void screenHandler::soul() //the soul of the whole game
{
    gout.open(WINDOW_X,WINDOW_Y);
    screensAlive.push_back(new menuScreen());
    while (!exitAwesomeness)
    {
        event ev;
        gin.timer(1000.0/FPS);
        screen* currentScreen=screensAlive[screensAlive.size()-1];
        while (gin>>ev&&screen::switchTo==screen::STAY&&screen::newSub==screen::STAY)
        {
            screensAlive[screensAlive.size()-1]->soul(ev);
        }
        if (screen::switchTo!=screen::STAY)
            switchScreen(currentScreen);
        if (screen::newSub!=screen::STAY)
            addSub(screen::newSub);
    }
}
