#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include "fieldObject.h"
#include "../../../../coor.h"
#include "../../../../graphicsPlus.h"

class stronghold : public fieldObject
{
    public:
        stronghold(coor origo, string owner);
        virtual ~stronghold();
        virtual void draw();
    protected:
        string owner;
    private:
};

#endif // STRONGHOLD_H
