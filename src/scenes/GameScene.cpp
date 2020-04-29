//
// Created by Remi on 10/04/2020.
//

#include "GameScene.h"
#include <iostream>
#include <QTimer>
#include <ctime>
#include <fstream>


GameScene::GameScene(std::vector<Qt::Key> keys,int nbPlayers,QString imgFileName){
    this->nbPlayers=nbPlayers;
    //Ajout du background de la scène
    this->setBackground(imgFileName);

    //GameLoop
    this->timer = new QTimer(this);
    this->timer->start(30);

    this->isTimerLaunched = false;

    //Début de calcul du temps mit
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    this->status = "InGame";

    this->keys=keys;
    std::cout << this->keys.size() << std::endl;

    isTime1Set = false;

    if(this->nbPlayers == 2){
        isTime2Set = false;
    }

    this->isWidgetLoaded = false;
    this->gameTimer = QTime(0,0,0);
}

//Actions clavier :
void GameScene::keyPressEvent(QKeyEvent *event) {

    if(!isTimerLaunched){
        isTimerLaunched = true;
    }

    //1ER JOUEUR
    if (player->getStatus() == "Standing" || player->getStatus() == "Running") {
        if (event->key() == this->keys[0]) {
            if (event->isAutoRepeat()) {
                return;
            }
            std::string previousStatus = player->getStatus();
            player->setStatus("Jumping", previousStatus);
        } else if (event->key() == this->keys[1]) {
            player->setStatus("Running");
            player->setDirection("Left");
        } else if (event->key() == this->keys[2]) {
            player->setStatus("Running");
            player->setDirection("Right");
        }
    }

    //SI 2 JOUEURS
    if(this->nbPlayers==2){
        if (player2->getStatus() == "Standing" || player2->getStatus() == "Running") {
            if (event->key() == this->keys[3]) {
                if (event->isAutoRepeat()) {
                    return;
                }
                std::string previousStatus = player2->getStatus();
                player2->setStatus("Jumping", previousStatus);
            } else if (event->key() == this->keys[4]) {
                player2->setStatus("Running");
                player2->setDirection("Left");
            } else if (event->key() == this->keys[5]) {
                player2->setStatus("Running");
                player2->setDirection("Right");
            }
        }
    }

    //PAUSE
    if (event->key() == Qt::Key_Escape && this->status != "EndScene") {
        if (this->status == "InGame") {
            this->status = "Paused";
        } else {
            this->request = "Resume";
        }
    }
}

void GameScene::keyReleaseEvent(QKeyEvent *event) {
    //1 JOUEUR
    if(player->getStatus() != "Jumping" && player->getStatus() != "Falling") {
        if (event->isAutoRepeat()) {
            return;
        }
        player->setStatus("Standing");
    }

    //SI 2 JOUEURS
    if(this->nbPlayers==2){
        if(player2->getStatus() != "Jumping" && player2->getStatus() != "Falling") {
            if (event->isAutoRepeat()) {
                return;
            }
            player2->setStatus("Standing");
        }
    }
}

//GameLoop
void GameScene::update() {
    if(this->status == "Paused") { //Si le jeu est en pause
        if(this->request=="Resume"){
            this->status = "InGame";
            this->request = "";
        }
    } else { //Si le jeu est en cours
        for(auto & movingFloor : this->movingFloors){
            movingFloor->moveFloor();
        }

        for(auto & movingObstacle : this->movingObstacles){
            movingObstacle->moveObstacle();
        }

        //JOUEUR 1
        if (player->getStatus() != "Jumping") {
            player->setPreviousStatus(player->getStatus());
        }

        player->move();
        player->setSkin();
        labelNamePlayer->move(player->pos().x()+20,player->pos().y()-15);

        if (player->pos().x() > xEnd) {
            player->setStatus("Winner");
        }

        if(nbPlayers==1) {
            QGraphicsView *view = this->views().at(0);
            view->centerOn(player);
            if (player->getStatus() == "Dead" || player->getStatus() == "Winner") { //Si le joueur est mort ou qu'il a gagné
                this->durationP1 = this->gameTimer;
                this->timer->stop();
                this->status = "EndScene";
                this->result(); //On appelle la fin du jeu
            }
        }

        //SI 2 JOUEURS
        if(this->nbPlayers==2){
            std::cout << player->getStatus() << " " << player2->getStatus() << std::endl;
            if (player2->getStatus() != "Jumping") {
                player2->setPreviousStatus(player2->getStatus());
            }

            player2->move();
            player2->setSkin();
            labelNamePlayer2->move(player2->pos().x()+20,player2->pos().y()-15);

            if (player2->pos().x() > xEnd) {
                player2->setStatus("Winner");
            }
            QGraphicsView *view = this->views().at(0);
            view->centerOn(player);
            view->centerOn(player);

            QGraphicsView *view2 = this->views().at(1);
            view2->setScene(this);
            view2->centerOn(player2);

            if(player->getStatus() == "Winner" && !isTime1Set){
                isTime1Set = true;
                this->durationP1 = this->gameTimer;
            }
            if(player2->getStatus() == "Winner" && !isTime2Set){
                isTime2Set = true;
                this->durationP2 = this->gameTimer;
            }

            if ((player2->getStatus() == "Dead" || player2->getStatus() == "Winner") && (player->getStatus() == "Dead" || player->getStatus() == "Winner")) { //Si le joueur est mort ou qu'il a gagné
                this->status = "EndScene";
                this->timer->stop();
                this->result(); //On appelle la fin du jeu
            }
        }

        if(this->isTimerLaunched){
            this->gameTimer = this->gameTimer.addMSecs(30);
        }

    }
}

void GameScene::addObstacles() {}

void GameScene::addFloor() {}

void GameScene::result() { //Fin du jeu
    std::ofstream scoresFile(this->scoreFile, std::ios::app);
    if(nbPlayers==2){
        if(player->getStatus() == "Winner" && player2->getStatus() == "Winner"){
            scoresFile << player->getName().toStdString() + "," + this->durationP1.toString("mm:ss:z").toStdString() << std::endl;
            scoresFile << player2->getName().toStdString() + "," + this->durationP2.toString("mm:ss:z").toStdString() << std::endl;
        } else if(player->getStatus() == "Winner" && player2->getStatus() == "Dead"){
            scoresFile << player->getName().toStdString() + "," + this->durationP1.toString("mm:ss:z").toStdString() << std::endl;
        } else if(player->getStatus() == "Dead" && player2->getStatus() == "Winner"){
            scoresFile << player2->getName().toStdString() + "," + this->durationP2.toString("mm:ss:z").toStdString() << std::endl;
        }
    } else {
        if (player->getStatus() == "Winner") {
            scoresFile << player->getName().toStdString() + "," + this->durationP1.toString("mm:ss:z").toStdString() << std::endl;

            std::ifstream scoresFile("../config/levels.txt");
            if(scoresFile){
                std::string line;
                while(getline(scoresFile,line)){
                    if(line=="zK7k9_vYmN" && this->id=="zK7k9_vYmN"){
                        std::ofstream file("../config/levels.txt");
                        file << "kj3c7_DahY";
                    } else if(line == "kj3c7_DahY" && this->id=="kj3c7_DahY"){
                        std::ofstream file("../config/levels.txt");
                        file << "b74r8_aLAnZ";
                    }
                }
            }
        }
    }
}

//Getters&Setters
std::string GameScene::getStatus() {
    return this->status;
}

bool GameScene::getIsWidgetLoaded() {
    return this->isWidgetLoaded;
}

void GameScene::setIsWidgetLoaded(bool loaded) {
    this->isWidgetLoaded = loaded;
}

void GameScene::setRequest(std::string request) {
    this->request = request;
}

std::string GameScene::getRequest(){
    return this->request;
}

bool GameScene::getIsTimerLaunched() {
    return this->isTimerLaunched;
}

QString GameScene::getTime() {
    return this->gameTimer.toString("mm:ss:z");
}
