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
    addParagraph("Conquering and assaults: ");
    addParagraph("Conquering a stronghold base: if you connect your barracks - whose strength isn't zero - "
                 "to a stronghold base, you upgrade it to a stronghold under your command. There are some additional rules: if "
                 " it is connected to multiple players at the same time, the one who sends the most soldiers (sum of connected"
                 " barracks' strengths) gets it. If there are multiple players with the most soldiers, "
                 " if one of them is the builder of the base, they get it, otherwise the player currently doing their turn gets it."
                 " Consequences of acquiring a stronghold: all undefended enemy barracks in the new stronghold's territory are"
                 " destroyed. All other stronghold bases in the new stronghold's territory are destroyed." 
                 " unless the other stronghold bases were also activated by the same action. "); 

    addParagraph("Starting an assault: you can start assaults from your strongholds towards enemy strongholds. "
                 " To do so, your stronghold must be connected to the enemy stronghold's territory (any of its "
                 " squares) and your stronghold's strength must be greater (not equal). Consequences: the enemy "
                 "stronghold is destroyed. All enemy barracks which become undefended are destroyed. ");
}
