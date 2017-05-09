#include "settingsScreen.h"

settingsScreen::settingsScreen()
{
    widgets.push_back(new sliderSetter(makeCoor(200,200), makeCoor(400,250),thinkingTime,120,0,"Time(s)"));
    vector<string> nations={"Ancient 1","Ancient 2"};
    widgets.push_back(new chooser(makeCoor(100,300),makeCoor(400,350),nations,player1Nation,200,"Player 1's nation"));
    widgets.push_back(new chooser(makeCoor(600,300),makeCoor(900,350),nations,player2Nation,200,"Player 2's nation"));
    widgets.push_back(new lButton([](){screen::switchTo=screen::GAME_SCREEN;},makeCoor(WINDOW_X-150,WINDOW_Y-50),200,50,"Start game",20));
    widgets.push_back(new lButton([](){screen::switchTo=screen::MENU_SCREEN;},makeCoor(150,WINDOW_Y-50),200,50,"Menu",20));
    draw();
}

void settingsScreen::draw()
{
    addTitle("Settings");
}
