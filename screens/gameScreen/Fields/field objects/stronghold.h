#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include "fieldObject.h"
#include "../../../../coor.h"
#include "../../../../graphicsPlus.h"

class player;

class stronghold : public fieldObject
{
    public:
        stronghold(coor origo, player* builder);
        virtual ~stronghold();
        virtual void draw();
        void gotOwner(player* owner);
        bool getHasOwner(){return hasOwner;};

        static const int RADIUS=3;
    protected:
        player* owner;
        player* builder;
        bool hasOwner=false;
        Picture territory;
    private:
};

#endif // STRONGHOLD_H
