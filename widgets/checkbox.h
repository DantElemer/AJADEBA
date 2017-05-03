#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "widgetBase.h"
#include "mButton.h"

class checkbox : public widgetBase
{
    public:
        checkbox(coor uLC, coor dRC, bool &var);
        virtual ~checkbox();

        void update();

    protected:

    private:
        bool* currValue;

        static void sChange(checkbox* c);
        void change();
        void draw();
};

#endif // CHECKBOX_H
