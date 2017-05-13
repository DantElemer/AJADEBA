#include "Picture.h"

Picture::Picture(string picFileName, coor origo)
: picFileName(picFileName), origo(origo)//, makeCanvas(), NORMAL_HEIGHT(height), NORMAL_WIDTH(width)
{
    //generateCanvas(myPic, picFileName);
    getData();
    NORMAL_HEIGHT=height;
    NORMAL_WIDTH=width;
    remakeCanvas();
}

void Picture::addNewPic(string bpicFileName, coor borigo)
{
    picFileName=bpicFileName;
    origo=borigo;
    scaleX=1;
    scaleY=1;
    getData();
    NORMAL_HEIGHT=height;
    NORMAL_WIDTH=width;
    remakeCanvas();
}

Picture::~Picture()
{
    //dtor
}

void Picture::draw()
{
    gout<<stamp(myPic,origo.X-width/2,origo.Y-height/2);
}

void Picture::getData()
{
    pixelData.clear();
    ifstream iF(picFileName);
    iF>>width>>height;
    myPic.open(width,height);

    for (int i=0;i<height;i++)
    {
        vector<pixel> newRow;
        for(int j=0;j<width;j++)
        {
            pixel newPixel;
            iF>>newPixel.r>>newPixel.g>>newPixel.b;
            newRow.push_back(newPixel);
        }
        pixelData.push_back(newRow);
    }
    iF.close();
    myPic.transparent(true);
}

void Picture::remakeCanvas()
{
    clearCanvas();
    width=NORMAL_WIDTH*scaleX;
    height=NORMAL_HEIGHT*scaleY;
    myPic.open(width,height);


    coor lastPoint=makeCoor(0,0);
    coor aimPoint;
    for (int i=0;i<NORMAL_HEIGHT;i++)
    {
        for(int j=0;j<NORMAL_WIDTH;j++)
        {
            aimPoint=makeCoor(egyRohadtRendesKerekites(scaleX*(j+1)),egyRohadtRendesKerekites(scaleY*(i+1)));
            myPic<<move_to(lastPoint.X,lastPoint.Y)<<color(pixelData[i][j].r,pixelData[i][j].g,pixelData[i][j].b)<<box(aimPoint.X-lastPoint.X,aimPoint.Y-lastPoint.Y);
            lastPoint.X=aimPoint.X;
        }
        lastPoint=makeCoor(0,aimPoint.Y);
    }
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
