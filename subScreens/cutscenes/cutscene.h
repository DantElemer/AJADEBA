#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "..\subScreen.h"
#include "..\..\..\graphicsPlus.h"
#include "..\..\..\widgets\animation.h"


class cutscene : public subScreen
{
    public:
        cutscene();
        virtual void draw();

    protected:
        vector<canvas> pics;

        virtual void generatePics();
        void addTitle(string title);
        virtual void keyDown(event kE);

    private:
};

#endif // CUTSCENE_H
