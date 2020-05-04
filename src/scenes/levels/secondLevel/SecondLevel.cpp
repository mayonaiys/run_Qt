//
// Created by Remi on 22/04/2020.
//

#include "SecondLevel.h"

SecondLevel::SecondLevel(std::vector<Qt::Key> keys,int nbPlayers,QString namePlayer1, QString namePlayer2) : GameScene(keys, nbPlayers,"../img/secondLevel/background.png") {

    this->id = "kj3c7_DahY";
    this->path = "secondLevel/"; //Chemin des images des sols/obtacles

    //Ajout des obstacles
    this->addObstacles();

    //Ajout du sol
    this->addFloors();

    //Ajout d'un personnage à la scène
    player = new Player(std::move(namePlayer1),"../img/skin1Right.png",obstacles,floors);
    player->spawn(0,300);
    labelNamePlayer = new QLabel(player->getName());
    labelNamePlayer->setAttribute(Qt::WA_NoSystemBackground);
    labelNamePlayer->setAlignment(Qt::AlignHCenter);
    labelNamePlayer->setFont(QFont("Joystick",16));
    this->addWidget(labelNamePlayer);
    this->addItem(player);
    if(nbPlayers==2){
        player2 = new Player(std::move(namePlayer2),"../img/skin1Right.png",obstacles,floors);
        player2->spawn(0,300);
        labelNamePlayer2 = new QLabel(player2->getName());
        labelNamePlayer2->setAttribute(Qt::WA_NoSystemBackground);
        labelNamePlayer2->setAlignment(Qt::AlignHCenter);
        labelNamePlayer2->setFont(QFont("Joystick",16));
        this->addWidget(labelNamePlayer2);
        this->addItem(player2);
    }

    //Point d'arrivée
    this->xEnd = 15000;

}
