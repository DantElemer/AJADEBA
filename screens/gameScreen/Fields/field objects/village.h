#ifndef VILLAGE_H
#define VILLAGE_H

#include "fieldObject.h"
#include "../../../../graphicsPlus.h"

class village : public fieldObject
{
    public:
        village(coor origo);
        virtual ~village();
        virtual void draw();
    protected:
    private:
};

#endif // VILLAGE_H
