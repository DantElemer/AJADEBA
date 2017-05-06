#ifndef BARRACK_H
#define BARRACK_H

#include "fieldObject.h"
#include "../../../../coor.h"
#include "../../../../graphicsPlus.h"


class barrack : public fieldObject
{
    public:
        barrack(coor origo, string owner);
        virtual ~barrack();
        virtual void draw();
    protected:
        string owner;
    private:
};

#endif // BARRACK_H
