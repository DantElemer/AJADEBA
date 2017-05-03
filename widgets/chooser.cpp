#include "chooser.h"

chooser::chooser(coor upperLeftCorner, coor downerRightCorner, vector<string> options, string &var, double listPlace, string name)
: widgetBase(upperLeftCorner,downerRightCorner), options(options), current(&var), NAME(name), LIST_SPACE(listPlace), newOption(downerRightCorner,downerRightCorner+makeCoor(100,20))
{
    const double O_W=20; //width=height of options-opening button
    *current="Choose->";
    subWidgets.push_back(&newOption);
    subWidgets.push_back(new mButton((memberFunctionCall)sKillCurrent,this,downerRightCorner+makeCoor(100,50),50,20,"Kill",14)); //14 is the fontsize
    subWidgets.push_back(new mButton((memberFunctionCall)addOp,this,downerRightCorner+makeCoor(100,20),50,20,"Add",14)); //14 is the fontsize
    subWidgets.push_back(new mButton((memberFunctionCall)chooseOther,this,upperLeftCorner+makeCoor(width-O_W/2,O_W/2),O_W,O_W,">",14)); //14 is the fontsize

    optionsStartIndex=subWidgets.size();
    draw();
}

void chooser::addOp(chooser* c)
{
    c->addOption(c->newOption.myText);
    c->newOption.myText="";
}

void chooser::draw()
{
    writeText(upperLeftCorner,NAME+": ",20);
    drawRectangle(upperLeftCorner+makeCoor(countTextWidth(NAME+": "),0),downerRightCorner-makeCoor(0,height-countTextHeight(NAME+": ")+2));
    writeText(upperLeftCorner+makeCoor(countTextWidth(NAME+": ")+3,0),*current,15);
}

void chooser::addOption(string option)
{
    if (option.length()>0)
        options.push_back(option);
}

void chooser::chooseOther(chooser* c)
{
     c->chooseAnOther();
}

void chooser::chooseAnOther()
{
    if (opsOpen)
        return;
    optionsULC=upperLeftCorner+makeCoor(countTextWidth(NAME+": "),countTextHeight(NAME,20));
    int i=0;
    while ((i+1)*opHeight<=LIST_SPACE&&i+offset<options.size())
    {
        subWidgets.push_back(new mButton((memberFunctionCall)&choosed,this,optionsULC+makeCoor(0,opHeight*i),optionsULC+makeCoor(width-countTextWidth(NAME+": "),opHeight*(i+1)),options[i+offset],15));
        i++;
    }
    drc=optionsULC+makeCoor(width-countTextWidth(NAME+": "),i*opHeight);
    opsOpen=true;
}

void chooser::keyDown(event kE)
{
    widgetBase::keyDown(kE);
    if (kE.keycode==key_enter)
        addOp(this);
}

void chooser::closeOptions()
{
    if (options.size()>0)
    {
         for (int i=subWidgets.size()-1;i>=optionsStartIndex;i--)
        {
            subWidgets[i]->clearWid();
            delete subWidgets[i];
            subWidgets.pop_back();
        }
    }
    opsOpen=false;
}

void chooser::choosed(chooser* c)
{
    c->choosedOne();
}

void chooser::choosedOne()
{
    coor optionsULC=upperLeftCorner+makeCoor(countTextWidth(NAME+": ",20),countTextHeight(NAME));
    for (int i=0;i<options.size();i++)
    {
        if (mouse.inRect(optionsULC+makeCoor(0,6+opHeight*i),optionsULC+makeCoor(width-countTextWidth(NAME+": "),6+opHeight*(i+1)))) //todo 6?
        {
            *current=options[i+offset];
            redraw();
        }
    }
}

void chooser::mouseUp()
{
    widgetBase::mouseUp();
    const double O_W=20;
    if (!mouse.inRect(upperLeftCorner+makeCoor(width-O_W,0),upperLeftCorner+makeCoor(width,O_W)))
        closeOptions();
}

void chooser::mouseWheelDown(event mE)
{
    widgetBase::mouseWheelDown(mE);
    if (opsOpen&&mouse.inRect(optionsULC,drc))
    {
        double opHeight=30;
        if ((options.size()-offset)*opHeight>LIST_SPACE)
        {
            closeOptions();
            offset++;
            chooseAnOther();
        }
    }

}

void chooser::mouseWheelUp(event mE)
{
    widgetBase::mouseWheelUp(mE);
    if (opsOpen&&mouse.inRect(optionsULC,drc))
    {
        double opHeight=30;
        if (offset>0)
        {
            closeOptions();
            offset--;
            chooseAnOther();
        }
    }
}

void chooser::saveData()
{
    ofstream file(DATA_FILE_NAME,ofstream::app);
    if (*current=="Choose->")
        file<<"Hi there! My value: NOTHING!"<<endl;
    else
        file<<"Hi there! My value: "<<current<<endl;
    file.close();
}

void chooser::killCurrent()
{
    for (int i=0;i<options.size();i++)
        if (options[i]==*current)
        {
            options.erase(options.begin()+i,options.begin()+i+1);
            if (LIST_SPACE-(options.size()-1-offset)*opHeight>opHeight)
                offset=max(offset-1,0);
            *current="Choose->";
            redraw();
            return;
        }
}

void chooser::sKillCurrent(chooser* c)
{
    c->killCurrent();
}

