#include "screen.h"

const string screen::MENU_SCREEN="menu screen";
const string screen::GAME_SCREEN="game screen";
const string screen::GAME_OVER_SCREEN="game over screen";
const string screen::VICTORY_SCREEN="victory screen";
const string screen::DIFFICULTY_SETTING_SCREEN="difficulty setting screen";
const string screen::HOW_TO_PLAY_SCREEN="how to play screen";
const string screen::CONFIRM_EXIT="confirm exit";
const string screen::BUILD_CHOOSER_SCREEN="build chooser screen";
/*const string screen::ALPHA_DONE="alpha done";
const string screen::HEIGHT_DONE="height done";
const string screen::AT_START="at start";
const string screen::END_SCENE="end scene";*/
const string screen::WIDGET_TEST_SCREEN="end scene";
const string screen::STAY="stay";
const string screen::EXIT="exit";
const string screen::TERMINATED="terminated";
string screen::switchTo=screen::STAY;
string screen::newSub=screen::STAY;

screen::screen()
{

}

void screen::soul(event ev)
{
    switch (ev.type)
    {
        case ev_timer:
            onTick();
            gout<<refresh;
            break;
        case ev_mouse:
            if (ev.button==-btn_left)
                mouseUp(ev);
            else if (ev.button==btn_left)
                mouseDown(ev);
            else if (ev.button==0)
                mouseMoved(ev);
            else if (ev.button==btn_wheelup)
                mouseWheelUp(ev);
            else if (ev.button==btn_wheeldown)
                mouseWheelDown(ev);
            break;
        case ev_key:
            if (ev.keycode>0)
                keyDown(ev);
            else
                keyUp(ev);
            break;
    }
}

void screen::draw()
{

}

void screen::mouseMoved(event mE)
{
    mouseX=mE.pos_x;
    mouseY=mE.pos_y;
    mouse=makeCoor(mouseX,mouseY);
}

void screen::onTick()
{
    for (widgetBase* &w:widgets)
        w->update();
}

void screen::mouseUp(event mE)
{
    for (widgetBase* &w:widgets)
        w->mouseUp();
}

void screen::mouseDown(event mE)
{
    for (widgetBase* &w:widgets)
        w->mouseDown();
}

void screen::mouseWheelUp(event mE)
{
    for (widgetBase* &w:widgets)
        w->mouseWheelUp(mE);
}

void screen::mouseWheelDown(event mE)
{
    for (widgetBase* &w:widgets)
        w->mouseWheelDown(mE);
}

void screen::ponyEffect() //as it's a Halflemon game
{
    cout<<endl<<endl;
    cout<<"            ______/``'``'-."<<endl;
    cout<<"           (_   6  \\    .^"<<endl;
    cout<<"         _ `'._,   |    `'-."<<endl;
    cout<<"        /_ \\  /    /      :`^'"<<endl;
    cout<<"      /`/_` \\/    /       .'"<<endl;
    cout<<"      '/  `'-    |.-'`^. `."<<endl;
    cout<<"      / .`-._     \\   `'^^^"<<endl;
    cout<<"    /`/'    \\      \\ "<<endl;
    cout<<"    ''       \\      `."<<endl;
    cout<<"              `\\      `."<<endl;
    cout<<"                `\\/     \\-'-.-"<<endl;
    cout<<"                 /     /`.  `-."<<endl;
    cout<<"                (    /'   )  .^"<<endl;
    cout<<"                 \\ \\ \\  .'^. `."<<endl;
    cout<<"                  \\ > >  `` `. )"<<endl;
    cout<<"                  // /       .`"<<endl;
    cout<<"                /`/== "<<endl;
    cout<<"               ==="<<endl;
    cout<<endl<<endl;
}

void screen::keyDown(event kE)
{
    if (kE.keycode==key_escape)
        exitRequest();
    if (kE.keycode=='q')
        ponyEffect();
    for (widgetBase* &w:widgets)
        w->keyDown(kE);
}

void screen::keyUp(event kE)
{
    for (widgetBase* &w:widgets)
        w->keyUp(kE);
}

void screen::switchToGameScreen()
{
    switchTo=screen::GAME_SCREEN;
}

void screen::subToHowToPlayScreen()
{
    newSub=screen::HOW_TO_PLAY_SCREEN;
}

void screen::switchToMenuScreen()
{
    switchTo=screen::MENU_SCREEN;
}

void screen::exitRequest()
{
    newSub=CONFIRM_EXIT;
}

