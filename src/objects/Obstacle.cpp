//
// Created by Remi on 14/04/2020.
//

#include "Obstacle.h"

//Constructeur
Obstacle::Obstacle(QString imgFileName) {
    this->setPixmap(QPixmap(imgFileName)); //Ajout de l'apparence de l'obstacle
}
