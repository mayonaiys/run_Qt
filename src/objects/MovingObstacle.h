//
// Created by Remi on 22/04/2020.
//

#ifndef JEU_MOVINGOBSTACLE_H
#define JEU_MOVINGOBSTACLE_H

#include "Obstacle.h"

class MovingObstacle : public Obstacle {

private:
    int firstExtremity; //Position minimale à atteindre sur Y
    int secondExtremity; //Position maximale à atteindre sur Y
    int velocity; //Rapidité de mouvement de l'obstacle

public:
    MovingObstacle(QString, int, int, int); //Constructeur
    void moveObstacle(); //Fonction de déplacement de l'obstacle

};


#endif //JEU_MOVINGOBSTACLE_H
