#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class player
{
    public:
        player(string name, string nation);

        string name;
        string nation;
        bool finishedTurn=false;
        int steps;
        static const int MAX_STEPS=4;
    protected:
    private:
};

#endif // PLAYER_H
