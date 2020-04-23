//
// Created by Remi on 22/04/2020.
//

#ifndef JEU_MOVINGOBSTACLE_H
#define JEU_MOVINGOBSTACLE_H

#include "Obstacle.h"

class MovingObstacle : public Obstacle {

private:
    int initialY;
    int velocity;
    int endY;

public:
    MovingObstacle(QString, int, int, int);
    void moveObstacle();

};


#endif //JEU_MOVINGOBSTACLE_H
