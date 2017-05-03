#ifndef ENDSCENE_H
#define ENDSCENE_H

#include "fCutscene.h"


class endScene : public fCutscene
{
    public:
        endScene();
        void draw();
    protected:
        void keyDown(event kE);
        void terminateSub();
    private:
};

#endif // ENDSCENE_H
