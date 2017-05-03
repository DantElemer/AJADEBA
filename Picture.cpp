#include "Picture.h"

Picture::Picture(string picFileName)
: picFileName(picFileName)
{
    generateCanvas(myPic, picFileName);
}

Picture::~Picture()
{
    //dtor
}

void Picture::draw(coor xy)
{
    gout<<stamp(myPic,xy.X,xy.Y);
}
