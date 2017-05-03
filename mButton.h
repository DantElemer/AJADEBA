#ifndef MBUTTON_H
#define MBUTTON_H

#include "button.h"

typedef void (* memberFunctionCall)(void*);

/*How to use it:
1) create a member function, which you want to fire
2) create a static member function, which has a object* parameter (object shall be the type to which you want access)
this function shall fire your member function using its parameter
3) create your mButton and give it the reference to your static function, and the object as parameters
+1 You can find examples in sliderSetter, chooser
*/

//for firing member functions (not directly)
class mButton : public button
{
    public:
        mButton(memberFunctionCall fire, void* object, coor origo, double width, double height, string texty="", int fontSize=40);
        mButton(memberFunctionCall fire, void* object, coor ULC, coor DRC, string texty="", int fontSize=40);
    protected:
        void* object;
        void fireFunction();
    private:
        memberFunctionCall memFunCall;
};

#endif // MBUTTON_H
