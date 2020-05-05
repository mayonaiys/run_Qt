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

Window::~Window() {
    this->settingsScene->~SettingsScene();
    this->startScene->~StartScene();
    delete this->timer;
    delete this->mainView;
}

void Window::update() {
    if(this->status =="inStart") {
        if(!this->isSceneLoaded){
            this->loadStart();
            this->isSceneLoaded = true;
        } else {
            this->startScene->adjustSize(this->width(),this->height());
            if (this->startScene->getRequest() == "Settings") {
                this->status = "inSettings";
                this->isSceneLoaded = false;
            } else if (this->startScene->getRequest() == "Scores") {
                this->status = "inScores";
                this->isSceneLoaded = false;
            } else if (this->startScene->getRequest() == "Solo" || this->startScene->getRequest() == "Multi") {
                if(!this->isWidgetLoaded){
                    this->startScene->disableButtons();
                    if (this->startScene->getRequest() == "Solo") {
                        this->choiceWidget = new ChoiceWidget(1);
                    } else if (this->startScene->getRequest() == "Multi") {
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
            if (this->startScene->getRequest() == "Solo") {
                this->loadSolo(); //On charge le niveau en solo
            } else if (this->startScene->getRequest() == "Multi") {
                this->loadMulti();
            }
            this->isSceneLoaded = true; //On indique qu'elle l'est
            this->timeLabel = new QLabel();
            this->timeLabel->setAttribute(Qt::WA_NoSystemBackground);
            this->timeLabel->setFixedSize(200, 40);
            this->timeLabel->move(this->width()-230, 10);
            this->globalScene->addWidget(timeLabel);
        } else if(this->isSceneLoaded) {
            this->timeLabel->move(this->width()-230, 10); //Ajustement de la position du chronomètre en fonction de la taille de la fenêtre
            this->parent->resize(this->width(),this->height()); //Ajustement de la taille du widget qui contient la scène de jeu en fonction de la taille de la fenêtre
            this->globalScene->setSceneRect(0, 0, this->width()-5, this->height()-5); //Ajustement de la taille de la scène qui contient le widget qui contient la scène du jeu
            if(this->gameScene->getStatus() == "InGame"){ //Si le jeu est en cours
                if(!this->gameScene->getIsTimerLaunched()){ //Si le chronomètre n'est pas lancé
                    QString str = "0:00:000"; //On affiche qu'il n'est pas commencé
                    this->timeLabel->setText(str);
                } else {
                    QString str = this->gameScene->getTime(); //On récupère la valeur du chronomètre actuelle
                    this->timeLabel->setText(str); //On l'affiche
                }
            }else if(this->gameScene->getStatus() == "Paused"){ //Si le jeu est en pause
                if(!this->gameScene->getIsWidgetLoaded()) { //Et que le widget de pause n'est pas chargé
                    this->pauseWidget = new PauseWidget(); //On le crée
                    this->globalScene ->addWidget(this->pauseWidget); //On l'affiche
                    this->pauseWidget->move((this->width())/2 - (this->pauseWidget->width())/2,(this->height())/2 - (this->pauseWidget->height())/2); //On le place
                    this->gameScene->setIsWidgetLoaded(true); //On indique qu'il est chargé
                } else { //Si le widget de pause est chargé
                    this->pauseWidget->move((this->width())/2 - (this->pauseWidget->width())/2,(this->height())/2 - (this->pauseWidget->height())/2); //Ajustement de la position du widget en fonction de la taille de la fenêtre
                    if(gameScene->getRequest() == "Resume"){ //Si le jeu demande a reprendre
                        this->pauseWidget->~PauseWidget(); //Le widget est supprimé
                        this->gameScene->setIsWidgetLoaded(false); //Il n'est plus chargé
                    } else if(this->pauseWidget->getRequest() == "Resume") { //Si le widget demande à reprendre la partie
                        this->gameScene->setRequest("Resume"); //On indique que le jeu doit reprendre
                        this->pauseWidget->~PauseWidget(); //Le widget est supprimé
                        this->gameScene->setIsWidgetLoaded(false); //Il n'est plus chargé
                    } else if (this->pauseWidget->getRequest() == "End") { //Si le widget demande la fin de la partie
                        this->gameScene->~GameScene(); //On supprime la scène du jeu
                        this->choiceWidget->~ChoiceWidget(); //On supprime le widget
                        this->status = "inStart"; //
                        this->isSceneLoaded = false; //La scène de jeu n'est plus chargé
                    }
                }
            } else if(this->gameScene->getStatus() == "EndScene") { //Si le jeu est sur la scène de fin
                if(!this->gameScene->getIsWidgetLoaded()){ //Si le widget de fin n'est pas chargé
                    this->endWidget = new EndWidget(); //Il est créé
                    this->globalScene ->addWidget(this->endWidget); //Il est ajouté à la scène globale
                    this->endWidget->move((this->width())/2 - (this->endWidget->width())/2,(this->height())/2 - (this->endWidget->height())/2); //Il est placé
                    this->gameScene->setIsWidgetLoaded(true); //Le widget est indiqué comme chargé
                } else {
                    this->endWidget->move((this->width())/2 - (this->endWidget->width())/2,(this->height())/2 - (this->endWidget->height())/2); //Ajustement de la position du widget en fonction de la taille de la fenêtre
                    if(this->endWidget->getRequest()=="End"){ //Si le widget demande la fin du jeu
                        //this->endWidget->~EndWidget();
                        this->gameScene->~GameScene(); //On supprime la scene du jeu
                        this->choiceWidget->~ChoiceWidget(); //On supprime le widget
                        this->status = "inStart"; //Le jeu revient sur le menu de démarrage
                        this->isSceneLoaded = false; //La scène n'est plus chargée
                    } else if(this->endWidget->getRequest()=="Restart"){ //Si le widget demande à ce que la partie recommence
                        //this->endWidget->~EndWidget();
                        this->gameScene->~GameScene(); //On supprime la scène
                        this->isSceneLoaded = false; //La scène n'est plus chargée
                    }
                }
            }
        }
    } else if(this->status == "inSettings"){ //Si le programme est dans les paramètres
        if(!this->isSceneLoaded){ //Si la scène n'est pas chargée
            this->loadSettings(); //On la charge
            this->isSceneLoaded = true; //On indique qu'elle est chargée
        } else if(this->isSceneLoaded){ //Si la scène est chargée
            this->settingsScene->adjustSize(this->width(),this->height()); //On ajuste la taille de celle-ci en fonction de la fenêtre
            if(this->settingsScene->getStatus()=="Ended") { //Si la scène demande de revenir au menu de démarrage
                this->status = "inStart"; //Le programme y retourne
                this->settingsScene->setStatus("doNothing"); //La scène ne demande plus rien
                this->isSceneLoaded = false; //La scène n'est plus chargée
            }
        }
    } else if(this->status == "inScores"){ //Si le programme est dans les scores
        if(!this->isSceneLoaded){ //Si la scène n'est pas chargée
            this->loadScores(); //On la charge
            this->isSceneLoaded = true; //On indique qu'elle est chargée
        } else if(this->isSceneLoaded){ //Si elle est chargée
            this->scoresScene->adjustSize(this->width(),this->height()); //On ajuste sa taille en fonction de la fenêtre
            if(this->scoresScene->getStatus()=="Ended") { //Si la scène demande à revenir au menu de démarrage
                this->status = "inStart"; //Le programme y retourne
                this->scoresScene->~ScoresScene();
                this->isSceneLoaded = false; //La scène n'est plus chargée
            }
        }
    }
}


//Chargement des scènes
void Window::loadStart() {
    this->startScene = new StartScene();
    this->mainView->setScene(this->startScene);
}

void Window::loadSolo() {
    if(this->choiceWidget->getRequest()=="FirstLevel"){
        this->gameScene = new FirstLevel(this->settingsScene->getKeys(),1,this->choiceWidget->getNamePlayer1()); //Création de la scène du niveau 1 avec un joueur
    } else if(this->choiceWidget->getRequest()=="SecondLevel"){
        this->gameScene = new SecondLevel(this->settingsScene->getKeys(),1,this->choiceWidget->getNamePlayer1()); //Création de la scène du niveau 2 avec un joueur
    } else if(this->choiceWidget->getRequest()=="ThirdLevel"){
        this->gameScene = new ThirdLevel(this->settingsScene->getKeys(),1,this->choiceWidget->getNamePlayer1()); //Création de la scène du niveau 3 avec un joueur
    }
    this->globalScene = new Scene();
    QGraphicsView* view = new QGraphicsView();
    view->setScene(gameScene);
    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(view);
    this->parent = new QWidget();
    this->parent->setLayout(hBox);
    this->globalScene->addWidget(this->parent);
    this->mainView->setScene(this->globalScene); //Attribution de la vue à la scène
}

void Window::loadMulti() {
    if(this->choiceWidget->getRequest()=="FirstLevel"){
        this->gameScene = new FirstLevel(this->settingsScene->getKeys(),2,this->choiceWidget->getNamePlayer1(),this->choiceWidget->getNamePlayer2()); //Création de la scène niveau 1 avec 2 joueurs
    } else if(this->choiceWidget->getRequest()=="SecondLevel"){
        this->gameScene = new SecondLevel(this->settingsScene->getKeys(),2,this->choiceWidget->getNamePlayer1(),this->choiceWidget->getNamePlayer2()); //Création de la scène niveau 2 avec 2joueurs
    } else if(this->choiceWidget->getRequest()=="ThirdLevel"){
        this->gameScene = new ThirdLevel(this->settingsScene->getKeys(),2,this->choiceWidget->getNamePlayer1(),this->choiceWidget->getNamePlayer2()); //Création de la scène niveau 3 avec 2 joueurs
    }
    this->globalScene = new Scene();
    QGraphicsView* view1 = new QGraphicsView();
    view1->setScene(this->gameScene);
    QGraphicsView* view2 = new QGraphicsView();
    view2->setScene(this->gameScene);
    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(view1);
    hBox->addWidget(view2);
    this->parent = new QWidget();
    this->parent->setLayout(hBox);
    this->globalScene ->addWidget(this->parent);
    this->mainView->setScene(this->globalScene);
}

void Window::loadSettings() {
    this->mainView->setScene(this->settingsScene); //Ajout de la scène à la vue
}

void Window::loadScores() {
    this->scoresScene = new ScoresScene(); //Création de la scène
    this->mainView->setScene(this->scoresScene); //Ajout de la scène à la vue
}

void Window::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) { //Si la touche espace est pressée
        if (this->status == "inStart") { //Si on est dans le menu de démarrage
            if (this->isWidgetLoaded) { //Si un widget est chargé (forcément celui du choix du niveau)
                this->choiceWidget->~ChoiceWidget(); //On supprime le widget
                this->isWidgetLoaded = false; //On dit que le widget est déchargé
                this->startScene->setRequest("doNothing"); //La scène de départ ne demande plus rien
                this->startScene->enableButtons(); //Les boutons de la scène de départ sont réactivés
            } else { //Sinon
                qApp->quit(); //On quitte le programme
            }
        } else if (this->status == "inGame") { //Si on est dans le jeu
            if (this->isWidgetLoaded) { //Si un widget est chargé (forcément celui de pause)
                this->isWidgetLoaded = false; //Il ne l'est plus
            }
        }
    }
}
