//
// Created by Remi on 22/04/2020.
//

#include "MovingObstacle.h"

MovingObstacle::MovingObstacle(QString imgFileName, int initialY , int localisationX, int localisationY) : Obstacle(imgFileName){

    this->setPos(localisationX,localisationY);
    this->velocity = -5;
    this->initialY = initialY;
    this->endY = initialY + 400;
}

void MovingObstacle::moveObstacle() {

    if(this->pos().y() < this->initialY || this->pos().y() + this->pixmap().height() > this->endY){
        this->velocity = - this->velocity;
    }

    this->moveBy(0, this->velocity);

}
