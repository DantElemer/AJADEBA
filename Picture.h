#ifndef PICTURE_H
#define PICTURE_H

#include "graphics.hpp"

#include "graphicsPlus.h"

#include <sstream>

struct pixel
{
    int r,g,b;
};

class Picture
{
    public:
        Picture(string picFileName, coor origo);
        Picture(){};
        void addNewPic(string picFileName, coor origo);
        virtual ~Picture();
        void draw();
        void clearPic();
        int getWidth(){return width;}
        int getHeight(){return height;}
        void setScaleX(double sX){scaleX=sX;remakeCanvas();};
        void setScaleY(double sY){scaleY=sY;remakeCanvas();};

        int NORMAL_WIDTH;
        int NORMAL_HEIGHT;

    protected:
        string picFileName;
        canvas myPic;
        int width;
        int height;
        double scaleX=1;
        double scaleY=1;
        coor origo;
        vector<vector<pixel>> pixelData;

        void getData();
        void remakeCanvas();
        void clearCanvas();
    private:
};

#endif // PICTURE_H
