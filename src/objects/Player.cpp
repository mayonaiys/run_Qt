//
// Created by Remi on 09/04/2020.
//

#include "Player.h"
#include <iostream>
#include <QtCore/QTimeLine>
#include <QtWidgets/QGraphicsItemAnimation>
#include <QtWidgets/QLabel>

//Constructeur
Player::Player(int status, QString name, QString imgFileName,std::vector<Obstacle*> obstaclesAlentours,std::vector<Floor*> floors){
    this->name = name; //Nom du joueur
    this->skinStatus = status; //Status du skin courant
    this->setPixmap(QPixmap(imgFileName)); //Skin du joueur
    this->status = "Standing"; //Status courant du joueur
    this->direction = "Right"; //Direction courante du joueur
    this->obstaclesAlentours = obstaclesAlentours; //Obstacles aux alentours du joueur
    this->floors = floors; //Sols sur lequel est le joueur
    this->setVelocity();
    this->gravity=-2;
}

//Getters&Setters:
void Player::setSkin() { //Modifie le skin du joueur
    if(skinStatus==4 || status=="Standing" || status=="Jumping" || status=="Falling"){
        skinStatus=1; //On revient au status de départ
    }
    std::string str = "../img/skin" + std::to_string(this->skinStatus) + direction + ".png"; //On prend le chemin du skin correspondant au status actuel
    QString qStr = QString::fromStdString(str);
    this->setPixmap(QPixmap(qStr)); //On applique le skin au joueur
    skinStatus++;
}


void Player::setStatus(std::string status,std::string previousStatus) {
    this->status = status;
    this->previousStatus = previousStatus;
}

std::string Player::getStatus() {
    return this->status;
}

void Player::setDirection(std::string direction) {
    this->direction = direction;
}


//Déplacements
void Player::move() { //Déplace le joueur
    if(status=="Standing"){
        this->stand();
    }else if(status=="Running"){
        //std::cout << "Running" << std::endl;
        this->run();
    } else if(status=="Jumping"){
        //std::cout << "Jumping" << std::endl;
        this->jump();
    } else if(status=="Falling"){
        //std::cout << "Falling" << std::endl;
        this->fall();
    }
}

void Player::run() {
    if(this->isOnFloor() || isOnObstacle()) {
        if (direction == "Right") {
            this->moveBy(20, 0); //Avance de 20 sur l'axe x
            if (isObstacleCollision() || isWallCollisionning()) {
                this->moveBy(-20, 0);
            }
        } else if (direction == "Left") {
            this->moveBy(-20, 0); //Recule de 20 sur l'axe x
            if (isObstacleCollision() || isWallCollisionning() || this->pos().x()-20 < 0) {
                this->moveBy(20, 0);
            }
        }
    } else {
        status = "Falling";
    }
}

void Player::jump() { //https://www.youtube.com/watch?v=c4b9lCfSDQM
    //std::cout << status << std::endl;
    if(this->previousStatus=="Standing"){
        if(velY < 0  || this->isHeadCollisionning() || this->isObstacleCollision()){
            this->status = "Falling";
            return;
        } else {
            velX=0;
            this->moveBy(0, -velY * 10); //Déplace le joueur en fonction de la vélocité
        }
    } else {
        if(velY < 0  || this->isHeadCollisionning() || this->isWallCollisionning() || this->isObstacleCollision()){
            this->status = "Falling";
            return;
        } else {
            if (direction == "Right") {
                this->moveBy(velX * 10, -velY * 10); //Déplace le joueur en fonction de la vélocité
            } else if (direction == "Left") {
                this->moveBy(-velX * 10, -velY * 10); //Déplace le joueur en fonction de la vélocité
            }
        }
    }
    velY = velY + gravity*0.15; //Applique une nouvelle vélocité
}

void Player::fall() {
    //std::cout << status << std::endl;
    if(this->isWallCollisionning()){
        if(this->pos().y()>600){
            if(this->direction=="Right"){
                this->direction="Left";
            } else if(this->direction=="Left"){
                this->direction="Right";
            }
        } else {
            velX = 0;
        }
    }
    if(this->isObstacleCollision()){
        velX=0;
    }
    if(this->direction=="Right"){
        this->moveBy(velX*7,velY*7); //Déplace le joueur en fonction de la vélocité
    } else if(this->direction=="Left"){
        this->moveBy(-velX*7,velY*7); //Déplace le joueur en fonction de la vélocité
    }
    velY = velY - gravity * 0.15; //Applique une nouvelle vélocité
    if(this->isOnFloor() || isOnObstacle()){
        this->status = "Standing";
        this->setVelocity();
        return;
    }
    if(this->pos().y()>1000){
        this->status = "Dead";
        this->setVelocity();
        return;
    }
}

//Detections obstacles
bool Player::isOnObstacle(){
    QRectF rect((pos().x()+boundingRect().width()/2)-5, (pos().y() + boundingRect().height()) -5, 10, 5);
    for(auto & obstacle : obstaclesAlentours){
        QRectF otherRect(obstacle->pos().x(), obstacle->pos().y(), obstacle->boundingRect().width(), obstacle->boundingRect().height());
        if(rect.intersects(otherRect)){
            return true;
        }
    }
}



bool Player::isObstacleCollision() {
    QRectF rect((pos().x() + boundingRect().width()/2)-30, pos().y()+20, 60,boundingRect().height()-60);
    for(auto & obstacle : obstaclesAlentours){
        QRectF otherRect(obstacle->pos().x(), obstacle->pos().y(), obstacle->boundingRect().width(), obstacle->boundingRect().height());
        if(rect.intersects(otherRect)){
            return true;
        }
    }
    return false;
}

//Detections sol
bool Player::isOnFloor(){
    QRectF rect((pos().x()+boundingRect().width()/2)-5, (pos().y() + boundingRect().height()) -5, 10, 5);
    for(auto & floor : floors){
        QRectF otherRect(floor->pos().x(), floor->pos().y(), floor->boundingRect().width(), floor->boundingRect().height());
        if(rect.intersects(otherRect)){
            return true;
        }
    }
}

//Detections plateformes
bool Player::isHeadCollisionning(){
    QRectF rect((pos().x()+boundingRect().width()/2)-5, pos().y(), 10, 5);
    for(auto & floor : floors){
        QRectF otherRect(floor->pos().x(), floor->pos().y(), floor->boundingRect().width(), floor->boundingRect().height());
        if(rect.intersects(otherRect)){
            return true;
        }
    }
}

bool Player::isWallCollisionning(){
    QRectF rect((pos().x() + boundingRect().width()/2)-30, pos().y()+20, 60,boundingRect().height()-60);
    for(auto & floor : floors){
        QRectF otherRect(floor->pos().x(), floor->pos().y(), floor->boundingRect().width(), floor->boundingRect().height());
        if(rect.intersects(otherRect)){
            return true;
        }
    }
    return false;
}

void Player::setVelocity(){
    this->velY=3;
    this->velX=2;
}

void Player::setPreviousStatus(std::string previousStatus) {
    this->previousStatus = previousStatus;
}

void Player::spawn(int x, int y) {
    this->status = "Standing";
    this->setPos(x,y);
}

QString Player::getName() {
    return this->name;
}

void Player::stand() {
    if(!this->isOnFloor()){
        if(!this->isOnObstacle()) {
            this->fall();
        }
    }
}
