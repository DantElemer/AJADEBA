#include "helpIV.h"

helpIV::helpIV()
{
    widgetBase* backButton=new button ((vFunctionCall)terminateSub, makeCoor(30,WINDOW_Y-80),makeCoor(150,WINDOW_Y-30),"Back",30);
    widgets.push_back(backButton);
    draw();
}

void helpIV::draw()
{
    helpBase::draw();
    addTitle("How to play IV");
    addParagraph("Finally conquering and assaults: ");
    addParagraph("Conquering a stronghold base: basically if you connect your barrack -whose strength isn't zero- "
                 "to it, you get it as a stronghold. However, there are some more complicated cases...if it's get "
                 "connected to different players at once, the one who sends the most soldiers (sum of connected"
                 " barracks' strengths) gets it. If there are more player, who sends more than all the other, "
                 "if one of them is the builder of the base, he gets it, otherwise current player gets it."
                 " Consequences: all undefended enemy barracks in the new stronghold's territory will be"
                 " destroyed. All other stronghold base in the new stronghold's territory will be destroyed. "); //kivéve ha õ is ugyanaazal a lépéssel lett aktiválva

    addParagraph("Starting an assault: you can start assaults from your strongholds, to enemy strongholds. To "
                 "do so, your stronghold must be connected to the enemy stronghold's territory (any of its"
                 " squares) and your stronghold's strength must be greater (not ge). Consequences: the enemy "
                 "stronghold will be destroyed. All enemy barracks, which becomes undefended, will be destroyed. ");
}
