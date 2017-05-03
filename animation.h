#ifndef ANIMATION_H
#define ANIMATION_H

#include "widgetBase.h"

//It plays a canvas-sequence repeatedly.
class animation : public widgetBase
{
    public:
        animation(coor uLC, coor dRC, vector<canvas> pics, int frameTime=4);
        void update();
        void draw();
    protected:
        int frameTime; //for how many ticks one frame shall stay
        int fTCounter;
        int currFrame;

        vector<canvas> pics;

    private:
};

#endif // ANIMATION_H
