#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class player
{
    public:
        player(string name, string nation);

        string name;
        bool finishedTurn=false;
    protected:

        string nation;
    private:
};

#endif // PLAYER_H
