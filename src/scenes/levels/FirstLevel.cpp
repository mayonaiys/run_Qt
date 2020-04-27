//
// Created by Remi on 17/04/2020.
//

#include "FirstLevel.h"
#include "../../objects/Player.h"
#include "../../objects/MovingFloor.h"

void FirstLevel::addObstacles() {

    Obstacle* obstacle = new Obstacle("../img/obstacle1.png");
    obstacles.push_back(obstacle);
    this->addItem(obstacle);
    obstacle->setPos(1600,630);
    
    Obstacle* obstacle2 = new Obstacle("../img/obstacle1.png");
    obstacles.push_back(obstacle2);
    this->addItem(obstacle2);
    obstacle2->setPos(5100,630);

    Obstacle* obstacle3 = new Obstacle("../img/obstacle1.png");
    obstacles.push_back(obstacle3);
    this->addItem(obstacle3);
    obstacle3->setPos(6000,460);

    Obstacle* obstacle4 = new Obstacle("../img/obstacle1.png");
    obstacles.push_back(obstacle4);
    this->addItem(obstacle4);
    obstacle4->setPos(6800,460);

    Obstacle* obstacle5 = new Obstacle("../img/obstacle1.png");
    obstacles.push_back(obstacle5);
    this->addItem(obstacle5);
    obstacle5->setPos(7950,420);

    Obstacle* obstacle6 = new Obstacle("../img/obstacle1.png");
    obstacles.push_back(obstacle6);
    this->addItem(obstacle6);
    obstacle6->setPos(9200,750);
}

void FirstLevel::addFloor() {

    Floor* floor = new Floor("../img/montagne.png");
    floors.push_back(floor);
    this->addItem(floor);
    floor->setPos(0,400);

    Floor* p1 = new Floor("../img/plateforme.png");
    floors.push_back(p1);
    this->addItem(p1);
    p1->setPos(600,350);

    Floor* trou1 = new Floor("../img/TROU1_PNG.png");
    floors.push_back(trou1);
    this->addItem(trou1);
    trou1->setPos(0,750);

    Floor* trou2 = new Floor("../img/TROU2_PNG.png");
    floors.push_back(trou2);
    this->addItem(trou2);
    trou2->setPos(900,750);

    Floor* floor2 = new Floor("../img/Floor1L_PNG.png");
    floors.push_back(floor2);
    this->addItem(floor2 );
    floor2 ->setPos(1200,750);

    Floor* trou3 = new Floor("../img/TROU1_PNG.png");
    floors.push_back(trou3);
    this->addItem(trou3);
    trou3->setPos(1500,750);

    Floor* p2 = new Floor("../img/plateforme.png");
    floors.push_back(p2);
    this->addItem(p2);
    p2->setPos(2400,700);

    Floor* p3 = new Floor("../img/plateforme.png");
    floors.push_back(p3);
    this->addItem(p3);
    p3->setPos(3180,550);

    Floor* p4 = new Floor("../img/plateforme.png");
    floors.push_back(p4);
    this->addItem(p4);
    p4->setPos(4000,800);

    Floor* trou6 = new Floor("../img/TROU2_PNG.png");
    floors.push_back(trou6);
    this->addItem(trou6);
    trou6->setPos(5600,600);

    Floor* floor4 = new Floor("../img/Floor1_PNG.png");
    floors.push_back(floor4);
    this->addItem(floor4);
    floor4 ->setPos(5800,600);

    Floor* trou7 = new Floor("../img/TROU1_PNG.png");
    floors.push_back(trou7);
    this->addItem(trou7);
    trou7->setPos(6900,600);

    Floor* trou4 = new Floor("../img/TROU2_PNG.png");
    floors.push_back(trou4);
    this->addItem(trou4);
    trou4->setPos(4870,750);

    Floor* floor3 = new Floor("../img/Floor1_PNG.png");
    floors.push_back(floor3);
    this->addItem(floor3);
    floor3 ->setPos(5430,750);

    Floor* trou5 = new Floor("../img/TROU1_PNG.png");
    floors.push_back(trou5);
    this->addItem(trou5);
    trou5->setPos(6530,750);

    Floor* p5 = new Floor("../img/plateforme.png");
    floors.push_back(p5);
    this->addItem(p5);
    p5->setPos(7750,500);

    Floor* p6 = new Floor("../img/plateforme.png");
    floors.push_back(p6);
    this->addItem(p6);
    p6->setPos(8600,450);

    Floor* trou8 = new Floor("../img/TROU2_PNG.png");
    floors.push_back(trou8);
    this->addItem(trou8);
    trou8->setPos(8400,860);

    Floor* trou9 = new Floor("../img/TROU1_PNG.png");
    floors.push_back(trou9);
    this->addItem(trou9);
    trou9->setPos(8900,860);

    Floor* p7 = new Floor("../img/plateforme.png");
    floors.push_back(p7);
    this->addItem(p7);
    p7->setPos(9720,700);

    Floor* trou10 = new Floor("../img/TROU2_PNG.png");
    floors.push_back(trou10);
    this->addItem(trou10);
    trou10->setPos(10500,650);

}

FirstLevel::FirstLevel(std::vector<Qt::Key> keys,int nbPlayers,QString namePlayer1, QString namePlayer2) : GameScene(keys, nbPlayers,"../img/1.png") {

    this->scoreFile = "../config/scores1.txt";
    this->id = "zK7k9_vYmN";

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
    player->spawn(0,200);

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
    this->xEnd = 11000;
}
