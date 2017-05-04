#include "Picture.h"

Picture::Picture(string picFileName, coor origo)
: picFileName(picFileName), origo(origo)
{
    //generateCanvas(myPic, picFileName);
    makeCanvas();
}

Picture::~Picture()
{
    //dtor
}

void Picture::draw()
{
    gout<<stamp(myPic,origo.X-width/2,origo.Y-height/2);
}

void Picture::makeCanvas() //TODO time-optimalization: do not read from file every time
{
    ifstream iF(picFileName);
    iF>>width>>height;
    clearCanvas();
    myPic.open(width*scaleX,height*scaleY);


    coor lastPoint=makeCoor(0,0);
    coor aimPoint;
    for (int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            int r,g,b;
            iF>>r>>g>>b;
            //lastPoint=makeCoor(j*scaleX,i*scaleY);
            aimPoint=makeCoor(egyRohadtRendesKerekites(scaleX*j),egyRohadtRendesKerekites(scaleY*i));
            myPic<<move_to(lastPoint.X,lastPoint.Y)<<color(r,g,b)<<box(aimPoint.X-lastPoint.X,aimPoint.Y-lastPoint.Y);
            lastPoint.X=aimPoint.X;
        }
        lastPoint=makeCoor(0,aimPoint.Y);
    }
    iF.close();
}

void Picture::clearCanvas()
{
    myPic.open(width,height);
    for (int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            myPic<<move_to(j,i)<<color(0,0,0)<<dot;
        }
    }
}

void Picture::clearPic()
{
    clearScreen(origo-makeCoor(width/2,height/2),origo+makeCoor(width/2,height/2));
}
