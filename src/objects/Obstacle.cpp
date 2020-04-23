//
// Created by Remi on 14/04/2020.
//

#include <iostream>
#include "Obstacle.h"

Obstacle::Obstacle(QString imgFileName) {
    this->setPixmap(QPixmap(imgFileName)); //Skin de l'obstacle
}
