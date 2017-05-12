#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "../../data.h"

using namespace std;

class player
{
    public:
        player(string name, string nation);
        void changeStrongholdNumber(int delta);

        string name;
        string nation;
        int steps;
        static const int MAX_STEPS=4;
        bool dead=false;
        double timeLeft;
        int strongholdNumber=0;
        bool boosted=false;
    private:

};

#endif // PLAYER_H
