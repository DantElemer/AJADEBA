#ifndef BARRACK_H
#define BARRACK_H

#include "fieldObject.h"
#include "../../../../coor.h"
#include "../../../../graphicsPlus.h"

class player;

class barrack : public fieldObject
{
    public:
        barrack(coor origo, player* owner);
        virtual ~barrack();
        virtual void draw();
    protected:
        player* owner;
    private:
};

#endif // BARRACK_H
