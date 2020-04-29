//
// Created by Remi on 22/04/2020.
//

#include "SecondLevel.h"

SecondLevel::SecondLevel(std::vector<Qt::Key> keys,int nbPlayers,QString namePlayer1, QString namePlayer2) : GameScene(keys, nbPlayers,"../img/backgroundLevel2.png") {

    this->scoreFile = "../config/scores2.txt";
    this->id = "kj3c7_DahY";

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
    player->spawn(11000,400);

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

void SecondLevel::addObstacles() {
    Obstacle* obstacle1 = new Obstacle("../img/obstacle2.png");
    obstacles.push_back(obstacle1);
    this->addItem(obstacle1);
    obstacle1->setPos(1600,590);

    Obstacle* obstacle2 = new Obstacle("../img/obstacle2.png");
    obstacles.push_back(obstacle2);
    this->addItem(obstacle2);
    obstacle2->setPos(3700,590);

    Obstacle* obstacle3 = new Obstacle("../img/obstacle2.png");
    obstacles.push_back(obstacle3);
    this->addItem(obstacle3);
    obstacle3->setPos(6350,270);

    Obstacle* obstacle4 = new Obstacle("../img/obstacle2.png");
    obstacles.push_back(obstacle4);
    this->addItem(obstacle4);
    obstacle4->setPos(9100,460);

    Obstacle* obstacle5 = new Obstacle("../img/obstacle2.png");
    obstacles.push_back(obstacle5);
    this->addItem(obstacle5);
    obstacle5->setPos(10150,460);

    Obstacle* obstacle6 = new Obstacle("../img/obstacle2.png");
    obstacles.push_back(obstacle6);
    this->addItem(obstacle6);
    obstacle6->setPos(11300,750);

}

void SecondLevel::addFloor() {

    Floor* floor2 = new Floor("../img/TROU12_PNG.png");
    floors.push_back(floor2);
    this->addItem(floor2);
    floor2->setPos(-150,500);

    Floor* floor1 = new Floor("../img/Floor2_PNG.png");
    floors.push_back(floor1);
    this->addItem(floor1);
    floor1->setPos(0,750);

    Floor* pit1 = new Floor("../img/TROU12_PNG.png");
    floors.push_back(pit1);
    this->addItem(pit1);
    pit1->setPos(1500,750);

    Floor* platform1 = new Floor("../img/plateforme2.png");//
    floors.push_back(platform1);
    this->addItem(platform1);
    platform1->setPos(700,450);

    Floor* platform2 = new Floor("../img/plateforme2.png");//
    floors.push_back(platform2);
    this->addItem(platform2);
    platform2->setPos(1500,300);

    MovingFloor* platform3 = new MovingFloor("../img/plateforme2.png",2200,2600,750);
    floors.push_back(platform3);
    movingFloors.push_back(platform3);
    this->addItem(platform3);

    Floor* pit2 = new Floor("../img/TROU22_PNG.png");
    floors.push_back(pit2);
    this->addItem(pit2);
    pit2->setPos(3400,750);

    Floor* floor3 = new Floor("../img/Floor2_PNG.png");
    floors.push_back(floor3);
    this->addItem(floor3);
    floor3->setPos(3967,750);

    Floor* floor4 = new Floor("../img/TROU22_PNG.png");
    floors.push_back(floor4);
    this->addItem(floor4);
    floor4->setPos(5830,400);

    Floor* pit3 = new Floor("../img/TROU12_PNG.png");
    floors.push_back(pit3);
    this->addItem(pit3);
    pit3->setPos(5467,750);

    Floor* platform4 = new Floor("../img/plateforme2.png");
    floors.push_back(platform4);
    this->addItem(platform4);
    platform4->setPos(4100,500);

    Floor* platform5 = new Floor("../img/plateforme2.png");
    floors.push_back(platform5);
    this->addItem(platform5);
    platform5->setPos(4900,400);

    Floor* pit4 = new Floor("../img/TROU12_PNG.png");
    floors.push_back(pit4);
    this->addItem(pit4);
    pit4->setPos(6397,400);

    MovingFloor* platform6 = new MovingFloor("../img/plateforme2.png",7200,7700,600);
    floors.push_back(platform6);
    movingFloors.push_back(platform6);
    this->addItem(platform6);

    Floor* pit5 = new Floor("../img/TROU22_PNG.png");
    floors.push_back(pit5);
    this->addItem(pit5);
    pit5->setPos(8400,600);

    Floor* floor6 = new Floor("../img/Floor2_PNG.png");
    floors.push_back(floor6);
    this->addItem(floor6);
    floor6->setPos(9600,900);

    Floor* floor5 = new Floor("../img/Floor2_PNG.png");
    floors.push_back(floor5);
    this->addItem(floor5);
    floor5->setPos(8967,600);

    Floor* platform7 = new Floor("../img/plateforme2.png");
    floors.push_back(platform7);
    this->addItem(platform7);
    platform7->setPos(9400,300);

    Floor* pit6 = new Floor("../img/TROU12_PNG.png");
    floors.push_back(pit6);
    this->addItem(pit6);
    pit6->setPos(10467,600);

    Floor* pit7 = new Floor("../img/TROU12_PNG.png");
    floors.push_back(pit7);
    this->addItem(pit7);
    pit7->setPos(11100,900);

    Floor* platform8 = new Floor("../img/plateforme2.png");
    floors.push_back(platform8);
    this->addItem(platform8);
    platform8->setPos(11850,750);
}
