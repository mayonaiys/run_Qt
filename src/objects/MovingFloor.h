//
// Created by Remi on 22/04/2020.
//

#ifndef JEU_MOVINGFLOOR_H
#define JEU_MOVINGFLOOR_H

#include "Floor.h"

class MovingFloor : public Floor {

private:
    int initialX;
    int velocity;
    int endX;

public:
    MovingFloor(QString, int, int, int);
    void moveFloor();
};


#endif //JEU_MOVINGFLOOR_H
