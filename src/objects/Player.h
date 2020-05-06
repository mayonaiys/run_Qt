//
// Created by Remi on 09/04/2020.
//

#ifndef JEU_PLAYER_H
#define JEU_PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include "Obstacle.h"
#include "Floor.h"

class Player : public QGraphicsPixmapItem {

private: //Attributs privés
    QString name; //Nom du joueur
    int skinStatus; //Status de l'apparence actuelle
    std::string status; /*Standing,Runing,Jumping,Falling,Dead,Winner*/
    std::string previousStatus; //Status précédent du joueur
    std::string direction; //Direction dans laquelle regarde le joueur
    double velX; //Rapidité sur l'axe X
    double velY; //Rapidité sur l'axe Y
    double gravity; //Gravité appliquée au joueur

    //Environnement alentour
    std::vector<Obstacle*> obstaclesAround; //Obstacles aux alentours du joueur
    std::vector<Floor*> floorsAround; //Sols aux alentours du joueur

public: //Fonctions publiques

    Player(QString,const QString&,std::vector<Obstacle*>,std::vector<Floor*>); //Constructeur :

    //Getters&Setters :
    void setSkin(); //Modification de l'apparence du joueur
    void setStatus(std::string,std::string = ""); //Changement du status du joueur
    void setDirection(std::string); //Changement de la direction du joueur
    void setVelocity(); //Changement de la rapidité du joueur
    void setPreviousStatus(std::string); //Changement du status précédent du joueur
    QString getName(); //Récupération du nom du joueur
    std::string getStatus(); //Récupération du status du joueur

    //Actions :
    void move();
    void run();
    void jump();
    void fall();
    void stand();

    //Collisions :
    bool isObstacleCollision();
    bool isOnFloor();
    bool isHeadCollisionning();
    bool isWallCollisionning();
    bool isOnObstacle();

    //Apparition :
    void spawn(int,int);
};


#endif //JEU_PLAYER_H
