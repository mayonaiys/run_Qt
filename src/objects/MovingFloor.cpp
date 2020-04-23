//
// Created by Remi on 22/04/2020.
//

#include "MovingFloor.h"

MovingFloor::MovingFloor(QString imgFileName, int initialX, int localisationX, int localisationY) : Floor(imgFileName) {

    this->setPos(localisationX,localisationY);
    this->velocity = 10;
    this->initialX = initialX;
    this->endX = initialX + 1000;

}

void MovingFloor::moveFloor() {

    if(this->pos().x() + this->pixmap().width() > endX || this->pos().x() < initialX){
        this->velocity = - this->velocity;
    }

    this->moveBy(this->velocity,0);

}
