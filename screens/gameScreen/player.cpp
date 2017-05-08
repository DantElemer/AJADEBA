#include "player.h"

player::player(string name, string nation)
: name(name), nation(nation), steps(MAX_STEPS)
{
    //ctor
}

void player::changeStrongholdNumber(int delta)
{
    strongholdNumber+=delta;
    if (strongholdNumber==0)
        dead=true;
}

