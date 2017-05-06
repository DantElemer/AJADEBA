#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include "fieldObject.h"
#include "../../../../coor.h"
#include "../../../../graphicsPlus.h"

class player;

class stronghold : public fieldObject
{
    public:
        stronghold(coor origo);
        virtual ~stronghold();
        virtual void draw();
        void gotOwner(player* owner);
        bool getHasOwner(){return hasOwner;};
    protected:
        player* owner;
        bool hasOwner=false;;
    private:
};

#endif // STRONGHOLD_H
