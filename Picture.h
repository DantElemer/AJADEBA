#ifndef PICTURE_H
#define PICTURE_H

#include "graphics.hpp"

#include "graphicsPlus.h"

#include <sstream>

class Picture
{
    public:
        Picture(string picFileName, coor origo);
        virtual ~Picture();
        void draw();
        void clearPic();
        int getWidth(){return width;}
        int getHeight(){return height;}
        void setScaleX(double sX){scaleX=sX;makeCanvas();};
        void setScaleY(double sY){scaleY=sY;makeCanvas();};
    protected:
        string picFileName;
        canvas myPic;
        int width;
        int height;
        double scaleX=1;
        double scaleY=1;
        coor origo;

        void makeCanvas();
        void clearCanvas();
    private:
};

#endif // PICTURE_H
