#ifndef SUBSCREEN_H
#define SUBSCREEN_H

#include "../screen.h"

//A screen which doesn't clears the current one(s), just gets on the top of them. It can be removed by using "terminateSub()".
class subScreen : public screen
{
    public:
        subScreen();

        static const string CANCEL;
    protected:
        static void terminateSub();
        void addFrame(coor uLC, coor dRC);
    private:
};

#endif // SUBSCREEN_H
