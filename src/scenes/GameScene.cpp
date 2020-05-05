//
// Created by Remi on 10/04/2020.
//

#include "GameScene.h"
#include <iostream>
#include <QTimer>

//Constructeur
GameScene::GameScene(std::vector<Qt::Key> keys,int nbPlayers,QString imgFileName){
    this->nbPlayers=nbPlayers; //Initialisation du nombre de joueurs sur la partie
    this->w=QPixmap(imgFileName).width();
    this->h=QPixmap(imgFileName).height();
    this->setBackground(imgFileName);

    //GameLoop
    this->timer = new QTimer(this);
    this->timer->start(30); //Initialisation du la durée du timer pour la boucle

    this->keys=keys; //Initialisation des touches à utiliser pour contrôler le(s) joueur(s)

    //Widgets
    this->isWidgetLoaded = false; //Aucun widget n'est chargé

    //Timer de la partie
    this->gameTimer = QTime(0,0,0); //
    this->isTimerLaunched = false; //Le timer de la partie n'est pas lancé
    this->isTime1Set = false; //Le temps du joueur 1 n'a pas été enregistré
    if(this->nbPlayers == 2){
        this->isTime2Set = false; //Le temps du joueur 2 n'a pas été enregistré
    }

    //Début boucle du jeu
    connect(timer, SIGNAL(timeout()), this, SLOT(update())); //La fonction update va être répétée toute les 30 ms
    this->status = "InGame"; //Le status est défini comme en jeu
}

//Création niveau
void GameScene::addObstacles() {

    std::vector<std::vector<std::string> > temp = createTemp("../src/scenes/levels/" + this->path + "obstacles.txt",3);
    for(auto & i : temp){
        Obstacle* obstacle = new Obstacle(("../img/" + this->path + i[0]).c_str());
        this->obstacles.push_back(obstacle);
        this->addItem(obstacle);
        obstacle->setPos(std::stoi(i[1]),std::stoi(i[2]));
    }
    temp = createTemp("../src/scenes/levels/" + this->path + "movingObstacles.txt",4);
    for(auto & i : temp){
        MovingObstacle* movingObstacle = new MovingObstacle(("../img/" + this->path + i[0]).c_str(),std::stoi(i[3]),std::stoi(i[1]),std::stoi(i[2]));
        obstacles.push_back(movingObstacle);
        movingObstacles.push_back(movingObstacle);
        this->addItem(movingObstacle);
    }

}

void GameScene::addFloors() {

    std::vector<std::vector<std::string> > temp = createTemp("../src/scenes/levels/" + this->path + "floors.txt",3);
    for(auto & i : temp){
        Floor* floor = new Floor(("../img/" + this->path + i[0]).c_str());
        this->floors.push_back(floor);
        this->addItem(floor);
        floor->setPos(std::stoi(i[1]),std::stoi(i[2]));
    }
    temp = createTemp("../src/scenes/levels/" + this->path + "movingFloors.txt",4);
    for(auto & i : temp){
        MovingFloor* movingFloor = new MovingFloor(("../img/" + this->path + i[0]).c_str(),std::stoi(i[3]),std::stoi(i[1]),std::stoi(i[2]));
        floors.push_back(movingFloor);
        movingFloors.push_back(movingFloor);
        this->addItem(movingFloor);
    }

}

//Actions clavier :
void GameScene::keyPressEvent(QKeyEvent *event) { //Actions quand on appuie sur les touches

    if(!this->isTimerLaunched){
        this->isTimerLaunched = true; //A partir du moment ou on appuie sur une touche le timer de la partie se lance
    }

    //Contrôle premier joueur
    if (this->player->getStatus() == "Standing" || this->player->getStatus() == "Running") { //Si le joueur attend ou s'il cours
        if (event->key() == this->keys[0]) {
            if (!event->isAutoRepeat()) { //Evite les sauts répétés
                std::string previousStatus = player->getStatus(); //On récupère son status précédent pour définir le type de saut
                this->player->setStatus("Jumping", previousStatus); //Attribution du status
            }
        } else if (event->key() == this->keys[1]) {
            this->player->setStatus("Running"); //Attribution du status
            this->player->setDirection("Left"); //Attribution de la direction
        } else if (event->key() == this->keys[2]) {
            this->player->setStatus("Running"); //Attribution du status
            this->player->setDirection("Right"); //Attribution de la direction
        }
    }

    //Contrôle du second joueur (si présent)
    if(this->nbPlayers==2){
        if (this->player2->getStatus() == "Standing" || this->player2->getStatus() == "Running") { //Si le joueur attend ou s'il cours
            if (event->key() == this->keys[3]) {
                if (!event->isAutoRepeat()) { //Evite les sauts répétés
                    std::string previousStatus = player2->getStatus(); //On récupère son status précédent pour définir le type de saut
                    this->player2->setStatus("Jumping", previousStatus); //Attribution du status
                }
            } else if (event->key() == this->keys[4]) {
                this->player2->setStatus("Running"); //Attribution du status
                this->player2->setDirection("Left"); //Attribution de la direction
            } else if (event->key() == this->keys[5]) {
                this->player2->setStatus("Running"); //Attribution du status
                this->player2->setDirection("Right"); //Attribution de la direction
            }
        }
    }

    //PAUSE
    if (event->key() == Qt::Key_Escape && this->status != "EndScene") { //Si la touche entrée est échap et que le jeu n'est pas terminé
        if (this->status == "InGame") { //Si la partie est en cours
            this->status = "Paused"; //Attribution du status de pause
        } else {
            this->request = "Resume"; //Attribution de la requête de reprise du jeu
        }
    }
}

void GameScene::keyReleaseEvent(QKeyEvent *event) { //Actions quand les touches sont relachées
    //1 JOUEUR
    if(this->player->getStatus()=="Running") { //Si le joueur cours
        this->player->setStatus("Standing");
    }

    //SI 2 JOUEURS
    if(this->nbPlayers==2){
        if(this->player2->getStatus()=="Running") { //Si le joueur cours
            this->player2->setStatus("Standing");
        }
    }
}

//GameLoop
void GameScene::update() {
    if(this->status=="InGame") {
        for(auto & movingFloor : this->movingFloors){
            movingFloor->moveFloor(); //Les sols mouvants se déplacent
        }

        for(auto & movingObstacle : this->movingObstacles){
            movingObstacle->moveObstacle(); //Les obstacles mouvants bougent
        }

        //JOUEUR 1
        this->player->move(); //Déplacement du joueur
        this->labelNamePlayer->move(this->player->pos().x()+20,this->player->pos().y()-15); //Déplacement du nom du joueur en fonction de la position de celui-ci
        if(this->player->getStatus()!="Dead"){
            this->player->setSkin(); //Changement d'apparence du joueur
        }
        if (this->player->pos().x() > this->xEnd) { //Si je loueur passe la ligne d'arrivée
            this->player->setStatus("Winner"); //Son status passe à gagnant
        }
        QGraphicsView *view = this->views().at(0);
        view->centerOn(this->player); //Centrage  de la  vue sur le joueur

        if(this->nbPlayers==1) {
            if (this->player->getStatus() == "Dead" || this->player->getStatus() == "Winner") { //Si le joueur est mort ou qu'il a gagné
                this->durationP1 = this->gameTimer; //On récupère le temps qu'il a mit à finir
                this->result(); //On appelle la fin du jeu
                this->timer->stop(); //On arrête le timer de la boucle
                this->status = "EndScene"; //Le jeu passe sur la scène de fin
            }
        } else if(this->nbPlayers==2){

            this->player2->move(); //Déplacement du joueur
            this->labelNamePlayer2->move(this->player2->pos().x()+20,this->player2->pos().y()-15); //Déplacement du nom du joueur en fonction de la position de celui-ci
            if(this->player2->getStatus()!="Dead"){
                this->player2->setSkin(); //Changement d'apparence du joueur
            }

            if (this->player2->pos().x() > this->xEnd) { //Si je loueur passe la ligne d'arrivée
                this->player2->setStatus("Winner"); //Son status passe à gagnant
            }

            QGraphicsView *view2 = this->views().at(1);
            view2->centerOn(player2); //Centrage  de la  vue sur le joueur

            if(this->player->getStatus() == "Winner" && !this->isTime1Set){ //Si le joueur  a  terminé la partie mais que son score n'est pas enregistré
                this->durationP1 = this->gameTimer; //On enregistre son temps
                this->isTime1Set = true; //Son temps est enrigstré
            }
            if(this->player2->getStatus() == "Winner" && !this->isTime2Set){ //Si le joueur  a  terminé la partie mais que son score n'est pas enregistré
                this->durationP2 = this->gameTimer; //On enregistre son temps
                this->isTime2Set = true; //Son temps est enregistré
            }

            if ((this->player2->getStatus() == "Dead" || this->player2->getStatus() == "Winner") && (this->player->getStatus() == "Dead" || this->player->getStatus() == "Winner")) { //Si la partie est  terminée pour les deux joueurs
                this->result(); //On appelle la fin du jeu
                this->timer->stop(); //On arrête le timer de la boucle
                this->status = "EndScene"; //La partie est terminée
            }
        }

        if(this->isTimerLaunched){ //Si le timer de la partie est lancé
            this->gameTimer = this->gameTimer.addMSecs(30); //On ajoute 30ms à ce timer à chaque tour de la boucle
        }

    }else if(this->status == "Paused"){
        if(this->request=="Resume"){ //Si la requête demande la  remise en route du jeu
            this->status = "InGame"; //Attribution du status "en jeu"
            this->request = "Nothing"; //Le programme ne fait aucune requête
        }
    }
}

void GameScene::result() { //Fin du jeu
    std::ofstream scoresFile("../src/scenes/levels/" + this->path + "scores.txt", std::ios::app); //Ouverture en écriture du fichier de scores de la partie
    std::ofstream tempFile("../src/scenes/levels/temp.txt"); //Ouverture en écriture d'un fichier temporaire pour l'affichage des scores dans le widget de fin
    if(this->nbPlayers==2){ //Si deux  joueurs
        if(this->player->getStatus()=="Winner"){ //Si le joueur  1 a terminé le niveau
            scoresFile << this->player->getName().toStdString() + "," + this->durationP1.toString("mm:ss:z").toStdString() << std::endl; //On ajoute son score dans le fichier de scores
            tempFile << this->player->getName().toStdString() + "," + this->durationP1.toString("mm:ss:z").toStdString() << std::endl; //On ajoute son score dans le fichier temporaire
        } else { //Si le joueur 1 est mort
            tempFile << this->player->getName().toStdString() + ",Dead" << std::endl;  //On le notifie dans le fichier temporaire
        }
        if(this->player2->getStatus()=="Winner"){ //Si le joueur 2 a terminé le niveau
            scoresFile << this->player2->getName().toStdString() + "," + this->durationP2.toString("mm:ss:z").toStdString() << std::endl; //On ajoute son score dans le fichier de scores
            tempFile << this->player2->getName().toStdString() + "," + this->durationP2.toString("mm:ss:z").toStdString() << std::endl; //On ajoute son score dans le fichier temporaire
        } else {
            tempFile << this->player2->getName().toStdString() + ",Dead" << std::endl; //On le notifie dans le fichier temporaire
        }
    } else { //Si un seul joueur
        if (player->getStatus() == "Winner") { //S'il a fini la partie
            scoresFile << this->player->getName().toStdString() + "," + this->durationP1.toString("mm:ss:z").toStdString() << std::endl; //On enregistre son score dans le fichier de scores
            tempFile << this->player->getName().toStdString() + "," + this->durationP1.toString("mm:ss:z").toStdString() << std::endl; //On enregistre son score dans le fichier  temporaire

            std::ifstream scoresFile("../src/scenes/levels/levels.txt"); //Ouverture en écriture du fichier permettant de savoir quels niveaux sont débloqués
            if(scoresFile){ //Si le fichier existe
                std::string line;
                while(getline(scoresFile,line)){ //On récupère la ligne
                    if(line=="zK7k9_vYmN" && this->id=="zK7k9_vYmN"){ //Si la ligne correspond à l'id du premier niveau et que le niveau actuel est le premier
                        std::ofstream file("../src/scenes/levels/levels.txt"); //On ouvre le fichier en écriture
                        file << "kj3c7_DahY"; //On remplace l'ancien id par celui du second niveau, le niveau 2 sera alors débloqué
                    } else if(line == "kj3c7_DahY" && this->id=="kj3c7_DahY"){ //Si la ligne correspond à l'id du second niveau et que le niveau actuel est le second
                        std::ofstream file("../src/scenes/levels/levels.txt"); //On ouvre le fichier en écriture
                        file << "b74r8_aLAnZ"; //On remplace l'ancien id par celui du troisième niveau, celui-ci sera désormais débloqué
                    }
                }
            }
        } else { //S'il est mort
            tempFile << player->getName().toStdString() + ",Dead" << std::endl; //On le notifie dans le fichier temporaire
        }
    }
}

//Getters&Setters


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
    return this->gameTimer.toString("mm:ss:z"); //On récupère le temps dans le format minutes:secondes:millisecondes
}
