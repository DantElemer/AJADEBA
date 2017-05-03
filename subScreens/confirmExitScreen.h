#ifndef CONFIRMEXITSCREEN_H
#define CONFIRMEXITSCREEN_H

#include "subScreen.h"
#include "../../graphicsPlus.h"

//"Are you sure you wan to exit?"
class confirmExitScreen : public subScreen
{
    public:
        confirmExitScreen();
        void onTick();

    protected:
    private:
};

#endif // CONFIRMEXITSCREEN_H
