//
// Created by Remi on 09/04/2020.
//

#include "Player.h"
#include <QTimeLine>
#include <QtWidgets>
#include <iostream>

//Constructeur
Player::Player(QString name, const QString& imgFileName,std::vector<Obstacle*> obstaclesAround,std::vector<Floor*> floorsAround){
    this->name = std::move(name); //Nom du joueur
    this->skinStatus = 1; //Status du skin courant
    this->setPixmap(QPixmap(imgFileName)); //Ajout de l'apparence du joueur
    this->status = "Standing"; //Status courant du joueur
    this->direction = "Right"; //Direction courante du joueur
    this->setVelocity(); //Initialisation de la vitesse du joueur
    this->gravity=-2; //Initialisation de la gravité appliquée au joueur
    this->obstaclesAround = std::move(obstaclesAround); //Obstacles aux alentours du joueur
    this->floorsAround = std::move(floorsAround); //Sols sur lequel est le joueur
}

//Getters&Setters:
void Player::setSkin() { //Modifie l'apparence du joueur
    if(this->skinStatus==4 || this->status=="Standing" || this->status=="Jumping" || this->status=="Falling"){
        this->skinStatus=1; //On revient au status de départ
    }
    std::string str = "../img/player/skin" + std::to_string(this->skinStatus) + this->direction + ".png"; //On prend le chemin du skin correspondant au status actuel
    QString qStr = QString::fromStdString(str);
    this->setPixmap(QPixmap(qStr)); //On applique le skin au joueur
    this->skinStatus++;
}

void Player::setStatus(std::string status, std::string previousStatus) {
    this->status = std::move(status); //Intialisation du status
    this->previousStatus = std::move(previousStatus); //Intialisation du status prédédent
}

void Player::setDirection(std::string direction) {
    this->direction = std::move(direction); //Changement de la direction du joueur
}

void Player::setVelocity(){
    this->velX=2; //Changement de la rapidité sur l'axe X
    this->velY=3; //Changement de la rapidité sur l'axe Y
}

void Player::setPreviousStatus(std::string previousStatus) {
    this->previousStatus = std::move(previousStatus); //Changement du status précédent
}

QString Player::getName() {
    return this->name; //Récupération du nom du joueur
}

std::string Player::getStatus() {
    return this->status; //Récupération du status du joueur
}

//Actions
void Player::move() { //Choix de l'action à effectuer en fonction du status
    if(this->status=="Standing"){
        this->stand(); //Le joueur ne bouge pas
    }else if(this->status=="Running"){
        this->run(); //Le joueur court
    } else if(this->status=="Jumping"){
        this->jump(); //Le joueur saute
    } else if(this->status=="Falling") {
        this->fall(); //Le joueur tombe
    }
}

void Player::run() {
    if(this->isOnFloor() || isOnObstacle()) { //Si le joueur est sur le sol ou un obstacle
        if (this->direction == "Right") { //S'il regarde vers la droite
            this->moveBy(20, 0); //Avance de 20 sur l'axe x
            if (isObstacleCollision() || isWallCollisionning()) { //S'il se cogne à un sol ou un obstacle
                this->moveBy(-20, 0); //Recule de 20 sur l'axe x
            }
        } else if (this->direction == "Left") { //Si le regarde vers la gauche
            this->moveBy(-20, 0); //Avance de -20 sur l'axe x
            if (isObstacleCollision() || isWallCollisionning() || this->pos().x()-20 < 0) { //S'il se cogne à un obstacle, un sol ou s'il essaie de sortir du jeu
                this->moveBy(20, 0); //Recule de 20 sur l'axe x
            }
        }
    } else {
        this->status = "Falling"; //Il tombe
    }
}

void Player::jump() { //Source : https://www.youtube.com/watch?v=c4b9lCfSDQM

    if(this->velY > 0  && !this->isHeadCollisionning() && !this->isWallCollisionning() && !this->isObstacleCollision()){ //Si sa rapidité verticale est suppérieure à 0, qu'il ne touche pas un mur,un obstacle ou un sol avec sa tête
        if(this->previousStatus=="Standing") { //Si le joueur ne bouge pas
            this->velX=0; //Rapidité à 0 pour un saut droit
            this->moveBy(0, -this->velY * 10); //Fait se déplacer le joueur de - sa rapidité fois 10 sur l'axe Y
        } else {
            if (this->direction == "Right") { //Si le joueur regarde vers la droite
                this->moveBy(this->velX * 10, -this->velY * 10); //Déplace le joueur en fonction de sa rapidité
            } else if (this->direction == "Left") { //Si le joueur regarde vers la droite
                this->moveBy(-this->velX * 10, -this->velY * 10); //Déplace le joueur en fonction de sa rapidité
            }
        }
    } else {
        this->status = "Falling"; //Il tombe
    }
    this->velY = this->velY + this->gravity*0.15; //Applique une nouvelle rapidité verticale au joueur

}

void Player::fall() {

    if(!this->isOnFloor() && !this->isOnObstacle()){ //Si le joueur n'est ni sur
        if (this->isWallCollisionning() || this->isObstacleCollision()) { //Si le joueur se cogne dans un mur ou un obstacle
            if (this->pos().y() > 600) { //Si sa position sur l'axe Y est supérieure à 600
                if (this->direction == "Right") { //S'il regarde à droite
                    this->direction = "Left"; //Sa direction change
                } else if (this->direction == "Left") { //S'il regarde à gauche
                    this->direction = "Right"; //Sa direction change
                }
            } else {
                velX = 0; //Sa rapidité sur X est nulle
            }
        }

        if (this->direction == "Right") { //Si le joueur regarde vers la droite
            this->moveBy(velX * 7, velY * 7); //Déplace le joueur en fonction de sa rapidité
        } else if (this->direction == "Left") { //Si le joueur regarde vers la gauche
            this->moveBy(-velX * 7, velY * 7); //Déplace le joueur en fonction de sa rapidité
        }

        if (this->pos().y() > 1000) { //Si la position du joueur sur l'axe Y est suppérieure à 100
            this->status = "Dead"; //Il meurt
            return;
        }

        velY = velY - gravity * 0.15; //Modification de la rapidité sur l'axe Y
    } else {
        this->status = "Standing"; //Le joueur attend
        this->setVelocity(); //Sa rapidité est réinitialisée
    }

}

void Player::stand() {

    if(!this->isOnFloor() && !this->isOnObstacle()){ //Si le joueur n'est plus sur le sol ou sur un obstacle
            this->fall(); //Il tombe
    }

}

//Detections :
bool Player::isOnObstacle(){
    QRectF rect((pos().x()+boundingRect().width()/2)-5, (pos().y() + boundingRect().height()) -5, 10, 5); //Création de la hitBox du joueur (au niveau des pieds)
    for(auto & obstacle : obstaclesAround){
        QRectF otherRect(obstacle->pos().x(), obstacle->pos().y(), obstacle->boundingRect().width(), obstacle->boundingRect().height()); //Création de la hitbox de l'obstacle
        if(rect.intersects(otherRect)){ //Si les deux hitbox se croisent
            std::cout << "on obstacles" << std::endl;
            return true; //Le joueur est sur l'obstacle
        }
    }
}

bool Player::isObstacleCollision() {
    QRectF rect((pos().x() + boundingRect().width()/2)-30, pos().y()+20, 60,boundingRect().height()-60); //Création de la hitBox du joueur (corps entier)
    for(auto & obstacle : obstaclesAround){
        QRectF otherRect(obstacle->pos().x(), obstacle->pos().y(), obstacle->boundingRect().width(), obstacle->boundingRect().height()); //Création de la hitbox de l'obstacle
        if(rect.intersects(otherRect)){ //Si les deux hitbox se croisent
            std::cout << "collision obstacle" << std::endl;
            return true; //Le joueur se cogne dans l'obstacle
        }
    }
}

bool Player::isOnFloor(){
    QRectF rect((pos().x()+boundingRect().width()/2)-5, (pos().y() + boundingRect().height()) -5, 10, 5); //Création de la hitBox du joueur (au niveau des pieds)
    for(auto & floor : floorsAround){
        QRectF otherRect(floor->pos().x(), floor->pos().y(), floor->boundingRect().width(), floor->boundingRect().height()); //Création de la hitbox du sol
        if(rect.intersects(otherRect)){ //Si les deux hitbox se croisent
            std::cout << "on floor" << std::endl;
            return true; //Le joueur est sur le sol
        }
    }
}

bool Player::isHeadCollisionning(){
    QRectF rect((pos().x()+boundingRect().width()/2)-5, pos().y(), 10, 5); //Création de la hitBox du joueur (au niveau de la tête)
    for(auto & floor : floorsAround){
        QRectF otherRect(floor->pos().x(), floor->pos().y(), floor->boundingRect().width(), floor->boundingRect().height()); //Création de la hitbox du sol
        if(rect.intersects(otherRect)){ //Si les deux hitbox se croisent
            std::cout << "head collision" << std::endl;
            return true; //Le joueur se cogne la tête
        }
    }
}

bool Player::isWallCollisionning(){
    QRectF rect((pos().x() + boundingRect().width()/2)-30, pos().y()+20, 60,boundingRect().height()-60); //Création de la hitBox du joueur (au niveau du corps)
    for(auto & floor : floorsAround){
        QRectF otherRect(floor->pos().x(), floor->pos().y(), floor->boundingRect().width(), floor->boundingRect().height()); //Création de la hitbox du sol
        if(rect.intersects(otherRect)){ //Si les deux hitbox se croisent
            std::cout << "collision wall" << std::endl;
            return true; //Le joueur se cogne dans le sol
        }
    }
}

//Apparition
void Player::spawn(int x, int y) {
    this->status = "Standing"; //Le status du joueur est initialisé à standing (il ne bouge pas)
    this->setPos(x, y); //Initialisation de la position du joueur
}
