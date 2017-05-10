#ifndef LBUTTON_H
#define LBUTTON_H

#include "button.h"

#include <functional>


class lButton : public button
{
    public:
        lButton(function<void()> fire, coor origo, int width, int height, string texty="", int fontSize=40, bool selfClear=true);
        virtual ~lButton();
    protected:
        function<void()> fire;
        void fireFunction();
    private:
};

#endif // LBUTTON_H
