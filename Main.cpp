#include "src/Hexapod.h"

//Hexapod hexapod;
Leg legs[6];

void setup()
{
    legs[0].attach(2, 3, 4);
    legs[1].attach(5, 6, 7);
    legs[2].attach(8, 9, 10);
    legs[3].attach(32, 33, 34);
    legs[4].attach(35, 36, 37);
    legs[5].attach(38, 39, 40);

    for(int i = 0; i < 6; i ++)
        legs[i].test(1.571, 2, 2);
    //hexapod.setup();
}

void loop()
{
    //hexapod.update();
}