#ifndef HELPBASE_H
#define HELPBASE_H

#include "../subScreen.h"


class helpBase : public subScreen
{
    public:
        helpBase();
        virtual ~helpBase();
        virtual void draw();
    protected:
        coor startPoint=makeCoor(50,150);
        int fSize=18;
        int height=0;
        int bekezdDist=30;
        int lines;

        void addParagraph(string par);
};

#endif // HELPBASE_H
