#ifndef CHOOSER_H
#define CHOOSER_H#include "../widgets/button.h"

#include "widgetBase.h"
#include "mButton.h"
#include "textfield.h"

//It allows you to choose from multiple options. Use the button at the end to see options, use mousewheel to see other options.
class chooser : public widgetBase
{
    public:
        chooser(coor upperLeftCorner, coor downerRightCorner, vector<string> options, string &var, double listPlace=200, string name="Uffimuff");
        void addOption(string option);
        void draw();
        void mouseUp();
        void mouseWheelUp(event mE);
        void mouseWheelDown(event mE);
        void keyDown(event kE);
        void saveData();


    private:
        vector<string> options;
        const string NAME;
        const double LIST_SPACE;
        bool opsOpen=false;
        string* current;
        int offset=0;
        coor drc; //options downer right corner
        coor optionsULC; //options upper left corner
        double opHeight=30; //one option-button's height
        textfield newOption;
        int optionsStartIndex;

        static void chooseOther(chooser* c); //fires @c's chooseAnOther()
        void chooseAnOther(); //opens options
        void closeOptions();
        static void choosed(chooser* c); //fires @c's choosedOne
        void choosedOne(); //decide which option was chosen
        static void addOp(chooser* c);
        void killCurrent();
        static void sKillCurrent(chooser* c);
};

#endif // CHOOSER_H
