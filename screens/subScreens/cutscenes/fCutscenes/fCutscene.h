#ifndef FCUTSCENE_H
#define FCUTSCENE_H

#include "../cutscene.h"


class fCutscene : public cutscene
{
    public:
        fCutscene();

    protected:
        void generatePics();
        virtual void draw();
    private:
};

#endif // FCUTSCENE_H
