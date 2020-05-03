//
// Created by Remi on 03/05/2020.
//

#include "ThirdLevel.h"

ThirdLevel::ThirdLevel(std::vector<Qt::Key> keys,int nbPlayers,QString namePlayer1, QString namePlayer2) : GameScene(keys, nbPlayers,"../img/backgroundLevel3.png") {
    this->scoreFile = "../config/scores3.txt";
    this->id = "b74r8_aLAnZ";

    //Ajout d'un obstacle
    this->addObstacles();

    //Ajout du floor
    this->addFloor();

    //Ajout d'un personnage à la scène
    player = new Player(1,namePlayer1,"../img/skin1Right.png",obstacles,floors);
    this->addItem(player);
    labelNamePlayer = new QLabel(player->getName());
    labelNamePlayer->setAttribute(Qt::WA_NoSystemBackground);
    labelNamePlayer->setFont(QFont("Joystick",16));
    labelNamePlayer->setAlignment(Qt::AlignHCenter);
    this->addWidget(labelNamePlayer);
    player->spawn(0,400);

    if(nbPlayers==2){
        player2 = new Player(1,namePlayer2,"../img/skin1Right.png",obstacles,floors);
        this->addItem(player2);
        labelNamePlayer2 = new QLabel(player2->getName());
        labelNamePlayer2->setAttribute(Qt::WA_NoSystemBackground);
        labelNamePlayer2->setFont(QFont("Joystick",16));
        labelNamePlayer2->setAlignment(Qt::AlignHCenter);
        this->addWidget(labelNamePlayer2);
        player2->spawn(0,200);
    }

    //Point d'arrivée
    this->xEnd = 15000;


}

void ThirdLevel::addObstacles() {
    Obstacle* obstacle1 = new Obstacle("../img/obstacle3.png");
    obstacles.push_back(obstacle1);
    this->addItem(obstacle1);
    obstacle1->setPos(1700,620);


}

void ThirdLevel::addFloor() {
    Floor* pit2 = new Floor("../img/Floor3_PNG.png");
    floors.push_back(pit2);
    this->addItem(pit2);
    pit2->setPos(0,750);

    Floor* pit3 = new Floor("../img/TROU13_PNG.png");
    floors.push_back(pit3);
    this->addItem(pit3);
    pit3->setPos(1500,750);

    Floor* pit3d = new Floor("../img/plateforme3.png");
    floors.push_back(pit3d);
    this->addItem(pit3d);
    pit3d->setPos(2000,400);

}
