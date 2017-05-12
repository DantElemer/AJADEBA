#include "graphicsPlus.h"

using namespace genv;

int titleFontSize=100;
int titleFromWindow=30;

void clearScreen(coor uLC, coor dRC)
{
    gout<<move_to(max(0,(int)uLC.X),max(0,(int)uLC.Y))<<color(0,0,0)<<box(min((int)(dRC.X-uLC.X+1),WINDOW_X),min((int)(dRC.Y-uLC.Y+1),WINDOW_Y));
}

void darkening(int rate, coor uLC, coor dRC)
{
    for (int i=(int)uLC.X;i<=(int)dRC.X;i++)
        for (int j=(int)uLC.Y;j<=(int)dRC.Y;j++)
            if (i%rate==0&&j%rate==0)
                gout<<move_to(i,j)<<color(100,100,100)<<dot;
}

void drawFatLine(coor startPoint, coor endPoint, int width, int r, int g, int b)
{
    const double ennyiBiztosEleg=max(abs(startPoint.X-endPoint.X),abs(startPoint.Y-endPoint.Y));
    if (ennyiBiztosEleg>1000000)
        return;
    const coor delta=(endPoint-startPoint)/ennyiBiztosEleg;
    for (int i=0;i<=ennyiBiztosEleg;i++)
    {
        coor testPoint=startPoint+delta*i;
        if (testPoint.inWindow())
            drawFilledCircle(testPoint,width,r,g,b);
    }
}

void drawLine(coor startPoint, coor endPoint, int r, int g, int b)
{
    if (startPoint.inWindow()&&endPoint.inWindow())
    {
        gout<<move_to(startPoint.X,startPoint.Y)<<color(r,g,b)<<line_to(endPoint.X,endPoint.Y);
    }

    else
    {
        coor sPoint={-1,-1};
        coor ePoint={-1,-1};
        const double ennyiBiztosEleg=max(abs(startPoint.X-endPoint.X),abs(startPoint.Y-endPoint.Y));
        if (ennyiBiztosEleg>1000000) //hagyjuk má
            return;
        const coor delta=(endPoint-startPoint)/ennyiBiztosEleg;
        for (int i=0;i<=ennyiBiztosEleg;i++)
        {
            coor testPoint=startPoint+delta*i;
            if (testPoint.inWindow())
                if (sPoint.X==-1)
                    sPoint=testPoint;
                ePoint=testPoint;
        }
        if (sPoint.X==-1)
            return;
        gout<<move_to(sPoint.X,sPoint.Y)<<color(r,g,b)<<line_to(ePoint.X,ePoint.Y);
    }
}

void drawRectangle(coor upperLeftCorner,coor downerRightCorner, bool filled, int r, int g, int b)
{
    if (upperLeftCorner.X<0)
        upperLeftCorner.X=0;
    if (downerRightCorner.X>WINDOW_X)
        downerRightCorner.X=WINDOW_X;
    if (upperLeftCorner.Y<0)
        upperLeftCorner.Y=0;
    if (downerRightCorner.Y>WINDOW_Y)
        downerRightCorner.Y=WINDOW_Y;
    int width=downerRightCorner.X-upperLeftCorner.X;
    int height=downerRightCorner.Y-upperLeftCorner.Y;
    gout<<color(r,g,b)<<move_to(upperLeftCorner.X,upperLeftCorner.Y);
    if (filled)
        gout<<box(width,height);
    else
        gout<<line_to(upperLeftCorner.X+width,upperLeftCorner.Y)<<line_to(upperLeftCorner.X+width,upperLeftCorner.Y+height)<<line_to(upperLeftCorner.X,upperLeftCorner.Y+height)<<line_to(upperLeftCorner.X,upperLeftCorner.Y);
}

void drawCircle(coor origo, double radius, int r, int g, int b, int accuracy)
{
    float alfa=atan(1)*8.0/accuracy;
    gout << move_to(origo.X+radius,origo.Y)<<color(r,g,b);
    for (int i=1;i<=accuracy;i++)
    {
        gout << line_to(origo.X+radius*cos(i*alfa),origo.Y-radius*sin(i*alfa));
    }
}

void drawFilledCircle(coor origo, double radius, int r, int g, int b)
{
    gout<<color(r,g,b);
    for (int i=-(int)radius;i<=(int)radius;i++)
        for (int j=-(int)radius;j<=(int)radius;j++)
            if (pow(i,2)+pow(j,2)<=radius*radius)
                gout<<move_to(origo.X+i, origo.Y+j)<<dot;
}

void setFont(int fontSize)
{
    if (fontSize>0&&fontSize!=loadedFontSize) //for saving (much) time
    {
        gout.load_font("LiberationSerif-Bold.ttf",fontSize);
        loadedFontSize=fontSize;
    }
}

void printText(string texty, int fontSize)
{
    setFont(fontSize);
    gout<<color(255,255,255)<<text(texty);
}

int lWriteText(coor startPoint, string texty, int lineLength, int fontSize)
{
    int lineCounter=0;
    int lineStart=0;
    int lineEnd=texty.length()-1;
    while (lineStart<texty.length()-1)
    {
        bool lineDone=false;
        string line;
        while (!lineDone)
        {
            line=texty.substr(lineStart,lineEnd-lineStart);
            if ( (countTextWidth(line,fontSize)<lineLength) && ( (texty.at(lineEnd)==' ') || (lineEnd==texty.length()-1) ) )
                lineDone=true;
            else
                lineEnd--;
        }
        lineStart=lineEnd+1; //we don't need space at the beginning of a line
        lineEnd=texty.length()-1;
        writeText(startPoint+makeCoor(0,lineCounter*countTextHeight(line,fontSize)),line,fontSize);
        lineCounter++;

    }
    return lineCounter;
}

void writeText(coor startPoint, string texty, int fontSize)
{
    gout<<move_to((int)startPoint.X,(int)startPoint.Y);
    printText(texty,fontSize);
}

void mWriteText(coor origo, string texty, int fontSize)
{
    writeText(origo-countTextMiddle(texty,fontSize),texty,fontSize);
}

void addTitle(string title)
{
    setFont(titleFontSize);
    int titleLength=gout.twidth(title);
    writeText(makeCoor((WINDOW_X-titleLength)/2,titleFromWindow),title,titleFontSize);
}

int countTextHeight(string texty, int fontSize)
{
    setFont(fontSize);
    return gout.cascent()+gout.cdescent();
}

int countTextWidth(string texty, int fontSize)
{
    setFont(fontSize);
    return gout.twidth(texty);
}

int countTextBaseline(string texty, int fontSize)
{
    setFont(fontSize);
    return gout.cdescent()+gout.cascent()/2;
}

coor countTextMiddle(string texty, int fontSize)
{
    int textLength=countTextWidth(texty, fontSize);
    int textBaseline=countTextBaseline(texty, fontSize); //no idea why, but it's approximately good (baseline is above letters, when font is loaded)
    return makeCoor(textLength/2,textBaseline);
}

void generateCanvas(canvas &can, string fileName, bool blackAndWhite, bool transp /*, double width*/)
{
    ifstream iF(fileName);
    int w,h;
    iF>>w>>h;
    can.open(w,h);
    for (int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            int r,g,b;
            iF>>r>>g>>b;
            if (blackAndWhite)
            {
                double atl=(r+g+b)/3;
                if (atl<100)
                    atl=0;
                /*if (atl>190)
                    atl=255;*/
                can<<move_to(j,i)<<color(atl,atl,atl)<<dot;
            }
            else
                can<<move_to(j,i)<<color(r,g,b)<<dot;

        }
    }
    can.transparent(transp);
    iF.close();
}
