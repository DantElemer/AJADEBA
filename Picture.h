#ifndef PICTURE_H
#define PICTURE_H

#include "graphics.hpp"

#include "graphicsPlus.h"


class Picture
{
    public:
        Picture(string picFileName);
        virtual ~Picture();
        void draw(coor xy={0,0});
        int getWidth(){return width;}
        int getHeight(){return height;}
    protected:
        string picFileName;
        canvas myPic;
        int width;
        int height;
    private:
};

#endif // PICTURE_H
