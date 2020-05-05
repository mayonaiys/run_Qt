//
// Created by Remi on 09/04/2020.
//

#include <iostream>
#include "Window.h"

Window::Window(){
    //Apparence fenêtre
    this->setWindowTitle("Run");

    //Boucle du programme
    this->timer = new QTimer(this);
    this->timer->start(30); //Le timer durera 30 ms
    connect(timer, SIGNAL(timeout()), this, SLOT(update())); //Toute les 30ms la fonction update va être appelée

    //Scenes
    this->settingsScene = new SettingsScene(); //Création de la scène de paramètre dès le debut pour que les touches puissent êtres initialisées
    this->status = "inStart"; //Status du programme, initialement dans le menu de démarrage

    this->isSceneLoaded = false; //La scène n'est initialement pas chargée
    this->isWidgetLoaded = false; //Aucun widget n'est chargé

    //Création & application de la vue
    this->mainView = new QGraphicsView();
    this->setCentralWidget(mainView); //La vue devient le widget central de la fenête

    //Dimensionnement de la fenêtre
    this->setMinimumSize(1280,720);
    this->resize(1280,720);
}

void Window::update() {
    if(this->status =="inStart") {
        if(!isSceneLoaded){
            this->loadStart();
            this->isSceneLoaded = true;
        } else {
            this->startScene->adjustSize(this->width(),this->height());
            if (startScene->getRequest() == "Settings") {
                this->status = "inSettings";
                this->isSceneLoaded = false;
            } else if (startScene->getRequest() == "Scores") {
                this->status = "inScores";
                this->isSceneLoaded = false;
            } else if (startScene->getRequest() == "Solo" || startScene->getRequest() == "Multi") {
                if(!this->isWidgetLoaded){
                    this->startScene->disableButtons();
                    if (startScene->getRequest() == "Solo") {
                        this->choiceWidget = new ChoiceWidget(1);
                    } else if (startScene->getRequest() == "Multi") {
                        this->choiceWidget = new ChoiceWidget(2);
                    }
                    this->startScene->addWidget(this->choiceWidget);
                    this->choiceWidget->move((this->width()/2)-(this->choiceWidget->width())/2,(this->height())/2-(this->choiceWidget->height())/2);
                    this->isWidgetLoaded = true;
                } else {
                    if(!this->choiceWidget->getIsChoiceDo()){
                        this->startScene->adjustSize(this->width(),this->height());
                        this->choiceWidget->move((this->width()/2)-(this->choiceWidget->width())/2,(this->height())/2-(this->choiceWidget->height())/2);
                        if (this->choiceWidget->getIsPlayersValid() && this->choiceWidget->getIsLevelSet()) {
                            this->choiceWidget->setIsChoiceDo();
                        }
                    } else {
                        this->isWidgetLoaded = false;
                        this->status = "inGame";
                        this->isSceneLoaded = false;
                    }
                }
            }
        }
    } else if(this->status == "inGame"){
        if(!this->isSceneLoaded){
            if (startScene->getRequest() == "Solo") {
                this->loadSolo(); //On charge le niveau en solo
            } else if (startScene->getRequest() == "Multi") {
                this->loadMulti();
            }
            this->isSceneLoaded = true; //On indique qu'elle l'est
            timeLabel = new QLabel();
            timeLabel->setAttribute(Qt::WA_NoSystemBackground);
            timeLabel->setFixedSize(200, 40);
            timeLabel->move(this->width()-230, 10);
            globalScene->addWidget(timeLabel);
        } else if(isSceneLoaded) {
            timeLabel->move(this->width()-230, 10); //Ajustement de la position du chronomètre en fonction de la taille de la fenêtre
            parent->resize(this->width(),this->height()); //Ajustement de la taille du widget qui contient la scène de jeu en fonction de la taille de la fenêtre
            globalScene->setSceneRect(0, 0, this->width()-5, this->height()-5); //Ajustement de la taille de la scène qui contient le widget qui contient la scène du jeu
            if(gameScene->getStatus() == "InGame"){ //Si le jeu est en cours
                if(!gameScene->getIsTimerLaunched()){ //Si le chronomètre n'est pas lancé
                    QString str = "0:00:000"; //On affiche qu'il n'est pas commencé
                    timeLabel->setText(str);
                } else {
                    QString str = gameScene->getTime(); //On récupère la valeur du chronomètre actuelle
                    timeLabel->setText(str); //On l'affiche
                }
            }else if(gameScene->getStatus() == "Paused"){ //Si le jeu est en pause
                if(!gameScene->getIsWidgetLoaded()) { //Et que le widget de pause n'est pas chargé
                    this->pauseWidget = new PauseWidget(); //On le crée
                    this->globalScene ->addWidget(pauseWidget); //On l'affiche
                    this->pauseWidget->move((this->width())/2 - (pauseWidget->width())/2,(this->height())/2 - (pauseWidget->height())/2); //On le place
                    this->gameScene->setIsWidgetLoaded(true); //On indique qu'il est chargé
                } else { //Si le widget de pause est chargé
                    this->pauseWidget->move((this->width())/2 - (pauseWidget->width())/2,(this->height())/2 - (pauseWidget->height())/2); //Ajustement de la position du widget en fonction de la taille de la fenêtre
                    if(gameScene->getRequest() == "Resume"){ //Si le jeu demande a reprendre
                        delete pauseWidget; //Le widget est supprimé
                        this->gameScene->setIsWidgetLoaded(false); //Il n'est plus chargé
                    } else if(pauseWidget->getRequest() == "Resume") { //Si le widget demande à reprendre la partie
                        this->gameScene->setRequest("Resume"); //On indique que le jeu doit reprendre
                        delete pauseWidget; //Le widget est supprimé
                        this->gameScene->setIsWidgetLoaded(false); //Il n'est plus chargé
                    } else if (pauseWidget->getRequest() == "End") { //Si le widget demande la fin de la partie
                        delete gameScene; //On supprime la scène du jeu
                        delete choiceWidget; //On supprime le widget
                        this->status = "inStart"; //
                        this->isSceneLoaded = false; //La scène de jeu n'est plus chargé
                    }
                }
            } else if(gameScene->getStatus() == "EndScene") { //Si le jeu est sur la scène de fin
                if(!gameScene->getIsWidgetLoaded()){ //Si le widget de fin n'est pas chargé
                    this->endWidget = new EndWidget(); //Il est créé
                    this->globalScene ->addWidget(endWidget); //Il est ajouté à la scène globale
                    this->endWidget->move((this->width())/2 - (endWidget->width())/2,(this->height())/2 - (endWidget->height())/2); //Il est placé
                    this->gameScene->setIsWidgetLoaded(true); //Le widget est indiqué comme chargé
                } else {
                    this->endWidget->move((this->width())/2 - (endWidget->width())/2,(this->height())/2 - (endWidget->height())/2); //Ajustement de la position du widget en fonction de la taille de la fenêtre
                    if(endWidget->getRequest()=="End"){ //Si le widget demande la fin du jeu
                        delete gameScene; //On supprime la scene du jeu
                        delete choiceWidget; //On supprime le widget
                        this->status = "inStart"; //Le jeu revient sur le menu de démarrage
                        this->isSceneLoaded = false; //La scène n'est plus chargée
                    } else if(endWidget->getRequest()=="Restart"){ //Si le widget demande à ce que la partie recommence
                        delete gameScene; //On supprime la scène
                        this->isSceneLoaded = false; //La scène n'est plus chargée
                    }
                }
            }
        }
    } else if(this->status == "inSettings"){ //Si le programme est dans les paramètres
        if(!isSceneLoaded){ //Si la scène n'est pas chargée
            this->loadSettings(); //On la charge
            this->isSceneLoaded = true; //On indique qu'elle est chargée
        } else if(this->isSceneLoaded){ //Si la scène est chargée
            this->settingsScene->adjustSize(this->width(),this->height()); //On ajuste la taille de celle-ci en fonction de la fenêtre
            if(settingsScene->getStatus()=="Ended") { //Si la scène demande de revenir au menu de démarrage
                this->status = "inStart"; //Le programme y retourne
                this->settingsScene->setStatus("doNothing"); //La scène ne demande plus rien
                this->isSceneLoaded = false; //La scène n'est plus chargée
            }
        }
    } else if(this->status == "inScores"){ //Si le programme est dans les scores
        if(!isSceneLoaded){ //Si la scène n'est pas chargée
            this->loadScores(); //On la charge
            this->isSceneLoaded = true; //On indique qu'elle est chargée
        } else if(this->isSceneLoaded){ //Si elle est chargée
            this->scoresScene->adjustSize(this->width(),this->height()); //On ajuste sa taille en fonction de la fenêtre
            if(scoresScene->getStatus()=="Ended") { //Si la scène demande à revenir au menu de démarrage
                this->status = "inStart"; //Le programme y retourne
                this->scoresScene->setStatus("doNothing"); //La scène ne demande plus rien
                this->isSceneLoaded = false; //La scène n'est plus chargée
            }
        }
    }
}


//Chargement des scènes
void Window::loadStart() {
    startScene = new StartScene();
    mainView->setScene(startScene);
}

void Window::loadSolo() {
    if(this->choiceWidget->getRequest()=="FirstLevel"){
        gameScene = new FirstLevel(this->settingsScene->getKeys(),1,this->choiceWidget->getNamePlayer1()); //Création de la scène du niveau 1 avec un joueur
    } else if(this->choiceWidget->getRequest()=="SecondLevel"){
        gameScene = new SecondLevel(this->settingsScene->getKeys(),1,this->choiceWidget->getNamePlayer1()); //Création de la scène du niveau 2 avec un joueur
    } else if(this->choiceWidget->getRequest()=="ThirdLevel"){
        gameScene = new ThirdLevel(this->settingsScene->getKeys(),1,this->choiceWidget->getNamePlayer1()); //Création de la scène du niveau 3 avec un joueur
    }
    globalScene = new Scene();
    QGraphicsView* view = new QGraphicsView();
    view->setScene(gameScene);
    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(view);
    parent = new QWidget();
    parent->setLayout(hBox);
    globalScene->addWidget(parent);
    mainView->setScene(globalScene); //Attribution de la vue à la scène
}

void Window::loadMulti() {
    if(this->choiceWidget->getRequest()=="FirstLevel"){
        gameScene = new FirstLevel(this->settingsScene->getKeys(),2,this->choiceWidget->getNamePlayer1(),this->choiceWidget->getNamePlayer2()); //Création de la scène niveau 1 avec 2 joueurs
    } else if(this->choiceWidget->getRequest()=="SecondLevel"){
        gameScene = new SecondLevel(this->settingsScene->getKeys(),2,this->choiceWidget->getNamePlayer1(),this->choiceWidget->getNamePlayer2()); //Création de la scène niveau 2 avec 2joueurs
    } else if(this->choiceWidget->getRequest()=="ThirdLevel"){
        gameScene = new ThirdLevel(this->settingsScene->getKeys(),2,this->choiceWidget->getNamePlayer1(),this->choiceWidget->getNamePlayer2()); //Création de la scène niveau 3 avec 2 joueurs
    }
    globalScene = new Scene();
    QGraphicsView* view1 = new QGraphicsView();
    view1->setScene(gameScene);
    QGraphicsView* view2 = new QGraphicsView();
    view2->setScene(gameScene);
    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(view1);
    hBox->addWidget(view2);
    parent = new QWidget();
    parent->setLayout(hBox);
    globalScene ->addWidget(parent);
    mainView->setScene(globalScene);
}

void Window::loadSettings() {
    mainView->setScene(settingsScene); //Ajout de la scène à la vue
}

void Window::loadScores() {
    scoresScene = new ScoresScene(); //Création de la scène
    mainView->setScene(scoresScene); //Ajout de la scène à la vue
}

void Window::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape){ //Si la touche espace est pressée
        if(this->status=="inStart"){ //Si on est dans le menu de démarrage
            if(this->isWidgetLoaded){ //Si un widget est chargé (forcément celui du choix du niveau)
                delete this->choiceWidget; //On supprime le widget
                this->isWidgetLoaded=false; //On dit que le widget est déchargé
                this->startScene->setRequest("doNothing"); //La scène de départ ne demande plus rien
                this->startScene->enableButtons(); //Les boutons de la scène de départ sont réactivés
            } else { //Sinon
                qApp->quit(); //On quitte le programme
            }
        } else if(this->status=="inGame"){ //Si on est dans le jeu
            if(this->isWidgetLoaded){ //Si un widget est chargé (forcément celui de pause)
                this->isWidgetLoaded=false; //Il ne l'est plus
            }
        }
    }
}
