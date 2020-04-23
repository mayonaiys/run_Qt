//
// Created by Remi on 22/04/2020.
//

#include "MovingFloor.h"

MovingFloor::MovingFloor(const QString& imgFileName, int firstExtremity, int localisationX, int localisationY) : Floor(imgFileName) {

    this->setPos(localisationX,localisationY); //Ajout du sol à une position qui n'est pas forcément la même qu'initialX
    this->velocity = 10; //Initialisation de la rapidité
    this->firstExtremity = firstExtremity; //Initialisation de la premiere extrémité
    this->secondExtremity = firstExtremity + 1000; //Initialisation de la seconde extrémité

}

void MovingFloor::moveFloor() {

    if(this->pos().x() + this->pixmap().width() > this->secondExtremity || this->pos().x() < this->firstExtremity){ //Si le sol est entre la premiere et la seconde extrémité
        this->velocity = - this->velocity; //La rapidité s'inverse pour changer le sens de déplacement du sol
    }

    this->moveBy(this->velocity,0); //Déplacement du sol

}
