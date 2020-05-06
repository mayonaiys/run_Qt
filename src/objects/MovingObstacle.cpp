//
// Created by Remi on 22/04/2020.
//

#include "MovingObstacle.h"

//Constructeur
MovingObstacle::MovingObstacle(QString imgFileName, int firstExtremity , int localisationX, int localisationY) : Obstacle(imgFileName){

    this->setPos(localisationX,localisationY); //Ajout de l'obstacle à une position qui n'est pas forcément la même qu'initialY
    this->velocity = -5; //Initialisation de la rapidité
    this->firstExtremity = firstExtremity; //Initialisation de la premiere extrémité
    this->secondExtremity = firstExtremity + 100; //Initialisation de la seconde extrémité

}

//Mouvement
void MovingObstacle::moveObstacle() {

    if(this->pos().y() < this->firstExtremity || this->pos().y() > this->secondExtremity){ //Si l'obstacle se situe entre les deux extrémités
        this->velocity = - this->velocity; //Inversement de la rapidité pour changer le sens de déplacement
    }
    this->moveBy(0, this->velocity); //Déplacement de l'obstacle

}
