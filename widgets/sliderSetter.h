#ifndef SLIDERSETTER_H
#define SLIDERSETTER_H

#include "widgetBase.h"
#include "mButton.h"

//For setting a double. Grab the white rectangle/use buttons in the ends. PgUp, PgDown adds-reduces a great amount to every sliderSetter.
class sliderSetter : public widgetBase
{
    public:
        sliderSetter(coor upperLeftCorner, coor downerRightCorner, double &var, double maxValue, double minValue, string name="Mutyumom");
        void draw();
        void update();
        void mouseDown();
        void mouseUp();
        void keyDown(event kE);
        void saveData();
    private:
        const double MAX_VALUE, MIN_VALUE;
        double* currValue;
        const string NAME;
        const double B_CHANGE;
        const double LINE_LENGTH;
        bool sliding=false;
        const double END_MARKER_LENGTH=30;
        double MARKER_HEIGHT=20;
        double MARKER_WIDTH=6;
        double markerPosX;

        static void bIncrease(sliderSetter* slider);
        static void bDecrease(sliderSetter* slider);
        void change(double delta);
};

#endif // SLIDERSETTER_H
