#ifndef BUILDCHOOSERSCREEN_H
#define BUILDCHOOSERSCREEN_H

#include "subScreen.h"
#include "../gameScreen/Fields/field.h"
#include "../gameScreen/Fields/field objects/fieldObject.h"
#include "../../graphicsPlus.h"

class gameScreen;

class buildChooserScreen : public subScreen
{
    public:
        buildChooserScreen(gameScreen* gS);
        void draw();
        void onTick();
    private:
        gameScreen* gS;
        vector<string> options;

        void generateOptions();
        void showOptions();
};

#endif // BUILDCHOOSERSCREEN_H
