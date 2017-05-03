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
    protected:
        string picFileName;
        canvas myPic;
    private:
};

#endif // PICTURE_H
