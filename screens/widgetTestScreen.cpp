#include "widgetTestScreen.h"
#include <windows.h>

widgetTestScreen::widgetTestScreen()
{
    //widgets.push_back(new sliderSetter(makeCoor(100,300),makeCoor(300,360),100,10,"Bigyusz1"));
    //widgets.push_back(new sliderSetter(makeCoor(100,400),makeCoor(300,460),num,1000,0,"Mennyi"));
    //vector<string> v={"hamizni!","ROFIK","malacok","sertesek","disznok","ekezet rossz:","αινσό","tenyleg","francba","de fajlba jot ir"};
    //vector<string> v={"cortex.itk.ppke.hu"};
    //widgets.push_back(new chooser(makeCoor(500,400),makeCoor(700,460),v,izeke,200, "Bigyusz3"));
    /*vector<string> v2={"Domi","Laci"};
    widgets.push_back(new chooser(makeCoor(500,200),makeCoor(700,260),v2,100,"Bigyusz4"));*/

    //widgets.push_back(new mButton((memberFunctionCall)sIzelj,this,WINDOW_ORIGO,100,50,"kifele"));
    //widgets.push_back(new checkbox(makeCoor(100,100),makeCoor(150,150),isNum));

    //lWriteText(WINDOW_ORIGO,"sdufhsdfh siufhsdi sdjfhsd isdufh idsfhsdifuhs .sdufhsdfh siufhsdi sdjfhsd isdufh idsfhsdifuhs",150,20);
    //widgets.push_back(new lButton([this](){cout<<"hi"<<this->num;},WINDOW_ORIGO,200,50,"Lambda"));

    draw();
}

void widgetTestScreen::draw()
{
    addTitle("Ping");
    Picture pic("pics/csillarmika.bmp.kep",WINDOW_ORIGO);
    pic.draw();
    for (double i=0;i<8;i+=0.1)
    {
        clearScreen();
        pic.setScaleX(i);
        pic.setScaleY(i);
        pic.draw();
        gout<<refresh;
    }
    screen::draw();
}

void widgetTestScreen::keyDown(event kE)
{
    screen::keyDown(kE);
    if (kE.keycode=='s') //saving data into file (data.txt)
    {
        ofstream file(widgetBase::DATA_FILE_NAME); //to clear file
        file.close();
        for (widgetBase* w:widgets)
            w->saveData();
    }
}

void widgetTestScreen::sIzelj(widgetTestScreen* wTS)
{
    wTS->izelj();
}

void widgetTestScreen::izelj()
{
    string parancs="ping -n "+numToString(num)+" "+izeke;
    system(parancs.c_str());
}

