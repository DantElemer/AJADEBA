#ifndef SAVEMAP_H
#define SAVEMAP_H

#include "subScreen.h"

class mapEditor;

class saveMap : public subScreen
{
    public:
        saveMap(mapEditor* myEditor);
        void draw();
    private:
        textfield tField;
};

#endif // SAVEMAP_H
