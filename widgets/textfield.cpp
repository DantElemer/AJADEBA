#include "textfield.h"

textfield::textfield(coor upperLeftCorner, coor downerRightCorner, int fS, string text)
:widgetBase(upperLeftCorner,downerRightCorner), myText(text), cursorIn(false), fontSize(fS)
{
    //ctor
}

textfield::~textfield()
{
    //dtor
}

void textfield::mouseUp()
{
    widgetBase::mouseUp();
    if (mouse.inRect(upperLeftCorner,downerRightCorner))
        cursorIn=true;
    else
        cursorIn=false;
}

void textfield::draw()
{
    drawRectangle(upperLeftCorner, downerRightCorner);
    char cursor=' ';
    if (cursorIn)
        cursor='|';
    if (myText.length()>0||cursorIn)
        writeText(upperLeftCorner+makeCoor(DIST_FROM_EDGE,height/2-countTextHeight(myText,fontSize/2)), myText+cursor, fontSize);
}

void textfield::keyDown(event kE)
{
    widgetBase::keyDown(kE);
    if (cursorIn)
    {
        if (kE.keycode==key_backspace)
            myText=myText.substr(0,myText.length()-1);
        else if (kE.keycode>=97&&kE.keycode<=122) //it's between 'a' & 'z'
        {
            string newText=myText;
            newText+=kE.keycode;
            if (downerRightCorner.X-upperLeftCorner.X>countTextWidth(newText,fontSize)+DIST_FROM_EDGE)
                myText+=kE.keycode;
        }
    }

}

void textfield::update()
{
    redraw();
}
