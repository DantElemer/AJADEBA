#include "settingsScreen.h"

settingsScreen::settingsScreen()
{
    widgets.push_back(new sliderSetter(makeCoor(WINDOW_X/2-100,200), makeCoor(WINDOW_X/2+100,280),thinkingTime,120,0,"Time(s)"));
    vector<string> nations={"Ancient 1","Ancient 2", "Mordor"};
    widgets.push_back(new chooser(makeCoor(100,300),makeCoor(400,350),nations,player1Nation,200,"Player 1's nation"));
    widgets.push_back(new chooser(makeCoor(100,400),makeCoor(400,450),nations,player2Nation,200,"Player 2's nation"));
    widgets.push_back(new lButton([](){screen::switchTo=screen::GAME_SCREEN;},makeCoor(WINDOW_X-150,WINDOW_Y-50),200,50,"Start game",20));
    widgets.push_back(new lButton([](){screen::switchTo=screen::MENU_SCREEN;},makeCoor(150,WINDOW_Y-50),200,50,"Menu",20));

    ifstream mapList("maps/mapList.txt");
    vector<string> mList;
    string newMap;
    while (getline(mapList,newMap))
        mList.push_back(newMap);
    mapList.close();
    widgets.push_back(new chooser(makeCoor(600,300), makeCoor(800,400),mList,chosenMap,200,"Map"));
    loadNewDesc();
    draw();
}

void settingsScreen::mouseUp(event mE)
{
    screen::mouseUp(mE);
    clearScreen();
    draw();
}

void settingsScreen::draw()
{
    addTitle("Settings");
    loadNewDesc();
    screen::draw();
}

void settingsScreen::loadNewDesc()
{
    string description;
    string fileName="maps/descriptions/"+chosenMap+".txt";
    ifstream desc(fileName);
    getline(desc,description);
    desc.close();
    lWriteText(makeCoor(600,400),description,200,12);
    //loadedDesc=chosenMap;

    screen::draw();
}

/*void settingsScreen::onTick()
{
    screen::onTick();
    if (chosenMap!=loadedDesc)
    {
        clearScreen();
        draw();
    }
}*/
