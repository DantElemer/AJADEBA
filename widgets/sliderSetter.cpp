#include "sliderSetter.h"

sliderSetter::sliderSetter(coor upperLeftCorner, coor downerRightCorner,  double &var, double maxValue, double minValue, string name)
: widgetBase(upperLeftCorner,downerRightCorner), MAX_VALUE(maxValue), MIN_VALUE(minValue), currValue(&var), NAME(name), B_CHANGE((MAX_VALUE-MIN_VALUE)/20.0), LINE_LENGTH(width*3/4)
{
    double changeButtsSide=20;
    subWidgets.push_back(new mButton((memberFunctionCall)bIncrease,this,downerRightCorner-makeCoor(changeButtsSide/2,height/2),changeButtsSide,changeButtsSide,"+",12));
    subWidgets.push_back(new mButton((memberFunctionCall)bDecrease,this,upperLeftCorner+makeCoor(changeButtsSide/2,height/2),changeButtsSide,changeButtsSide,"-",12));
}

void sliderSetter::draw()
{
    widgetBase::draw();
    mWriteText(origo-makeCoor(0,(height-countTextHeight(NAME))/2),NAME,20);
    mWriteText(origo+makeCoor(0,(height-countTextHeight(numToString(*currValue)))/2),numToString(*currValue),15);
    gout<<move_to(origo.X-LINE_LENGTH/2,origo.Y)<<line_to(origo.X+LINE_LENGTH/2,origo.Y);

    gout<<move_to(origo.X-LINE_LENGTH/2,origo.Y-END_MARKER_LENGTH/2)<<line_to(origo.X-LINE_LENGTH/2,origo.Y+END_MARKER_LENGTH/2);
    gout<<move_to(origo.X+LINE_LENGTH/2,origo.Y-END_MARKER_LENGTH/2)<<line_to(origo.X+LINE_LENGTH/2,origo.Y+END_MARKER_LENGTH/2);

    markerPosX=origo.X-LINE_LENGTH/2+(LINE_LENGTH-MARKER_WIDTH)*(*currValue-MIN_VALUE)/(MAX_VALUE-MIN_VALUE);
    drawRectangle(makeCoor(markerPosX,origo.Y-MARKER_HEIGHT/2),makeCoor(markerPosX+MARKER_WIDTH,origo.Y+MARKER_HEIGHT/2),true);
}

void sliderSetter::mouseDown()
{
    widgetBase::mouseDown();
    if (mouse.inRect(origo-makeCoor(LINE_LENGTH/2,END_MARKER_LENGTH/2), origo+makeCoor(LINE_LENGTH/2,END_MARKER_LENGTH/2)))
        sliding=true;
}

void sliderSetter::mouseUp()
{
    widgetBase::mouseUp();
    sliding=false;
}

void sliderSetter::keyDown(event kE)
{
    if (kE.keycode==key_pgdn)
        change(-5*B_CHANGE);
    if (kE.keycode==key_pgup)
        change(5*B_CHANGE);
}

void sliderSetter::update()
{
    widgetBase::update();
    if (sliding)
        change(MIN_VALUE+(MAX_VALUE-MIN_VALUE)*(mouseX-MARKER_WIDTH/2-(origo.X-LINE_LENGTH/2))/(LINE_LENGTH-MARKER_WIDTH)-*currValue);
    redraw();
}

void sliderSetter::bIncrease(sliderSetter* slider)
{
    //slider->change(slider->B_CHANGE);
    slider->change(1);
}

void sliderSetter::bDecrease(sliderSetter* slider)
{
    //slider->change(-slider->B_CHANGE);
    slider->change(-1);
}

void sliderSetter::change(double delta)
{
    delta=int(delta);
    *currValue+=delta;
    if (*currValue<MIN_VALUE)
        *currValue=MIN_VALUE;
    if (*currValue>MAX_VALUE)
        *currValue=MAX_VALUE;
}

void sliderSetter::saveData()
{
    ofstream file(DATA_FILE_NAME,ofstream::app);
    file<<"Hi there! My value: "<<currValue<<endl;
    file.close();
}
