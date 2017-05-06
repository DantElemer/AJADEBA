#ifndef BUILDCHOOSERSCREEN_H
#define BUILDCHOOSERSCREEN_H

#include "subScreen.h"
#include "../gameScreen/Fields/field.h"
/*#include "../gameScreen/Fields/field objects/barrack.h"
#include "../gameScreen/Fields/field objects/road.h"
#include "../gameScreen/Fields/field objects/village.h"
#include "../gameScreen/Fields/field objects/stronghold.h"*/
#include "../gameScreen/Fields/field objects/fieldObject.h"

class gameScreen;

class buildChooserScreen : public subScreen
{
    public:
        buildChooserScreen(gameScreen* gS);
        void draw();
    private:
        gameScreen* gS;
        vector<string> options;

        void generateOptions();
        void showOptions();
};

#endif // BUILDCHOOSERSCREEN_H
