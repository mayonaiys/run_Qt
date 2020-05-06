//
// Created by Remi on 22/04/2020.
//

#ifndef JEU_MOVINGFLOOR_H
#define JEU_MOVINGFLOOR_H

#include "Floor.h"

class MovingFloor : public Floor {

private:
    int firstExtremity; //Position minimale à atteindre sur X
    int secondExtremity; //Position maximale à atteindre sur X
    int velocity; //Rapidité de déplacement du sol

public:
    MovingFloor(const QString&, int, int, int); //Constructeur
    void moveFloor(); //Mouvement du sol
};


#endif //JEU_MOVINGFLOOR_H
