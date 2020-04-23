//
// Created by Remi on 09/04/2020.
//

#ifndef JEU_PLAYER_H
#define JEU_PLAYER_H

#include <QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsItemAnimation>
#include "Obstacle.h"
#include "Floor.h"

class Player : public QGraphicsPixmapItem {

private: //Attributs privés
    QString name;
    int skinStatus;
    std::string status; /*Standing,Runing,Jumping,Falling,Dead,Winner*/
    std::string previousStatus;
    std::string direction;
    float velX;
    float velY;
    float gravity;

    //Environnement alentour
    std::vector<Obstacle*> obstaclesAlentours;
    std::vector<Floor*> floors;

public: //Fonctions publiques

    //Constructeur
    Player(int,QString,QString,std::vector<Obstacle*>,std::vector<Floor*>);

    //Getters&Setters
    void setSkin();
    void setStatus(std::string,std::string = "");
    std::string getStatus();
    void setDirection(std::string);
    void setVelocity();
    void setPreviousStatus(std::string);
    QString getName();

    //Déplacements :
    void move();
    void run();
    void jump();
    void fall();

    //Collisions :
    bool isObstacleCollision();
    bool isOnFloor();
    bool isHeadCollisionning();
    bool isWallCollisionning();
    bool isOnObstacle();

    //
    void spawn(int,int);

    void stand();
};


#endif //JEU_PLAYER_H
