//
// Created by Remi on 09/04/2020.
//

#include <iostream>
#include "Window.h"

Window::Window(){
    //Loop
    this->timer = new QTimer(this);
    this->timer->start(30);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    //Scenes
    this->settingsScene = new SettingsScene();
    this->status = "inStart";
    this->isSceneLoaded = false;

    this->isWidgetLoaded = false;
    this->isChoiceDo = false;

    //Vues
    this->mainView = new QGraphicsView();
    this->setCentralWidget(mainView); //La vue devient le widget central de la fenête
    this->setMinimumSize(1280,720);
    this->resize(1280,720);

}

void Window::update() {
    //std::cout << this->width() << " " << this->height() << std::endl;
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
                this->status = "inGame";
                this->isSceneLoaded = false;
            }
        }
    } else if(this->status == "inGame"){
        if(!isSceneLoaded){
            if(!this->isChoiceDo) {
                if (!this->isWidgetLoaded) {
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
                    this->startScene->adjustSize(this->width(),this->height());
                    this->choiceWidget->move((this->width()/2)-(this->choiceWidget->width())/2,(this->height())/2-(this->choiceWidget->height())/2);
                    if (this->choiceWidget->getIsPlayersValid() && this->choiceWidget->getIsLevelSet()) {
                        this->isChoiceDo = true;
                        this->isWidgetLoaded = false;
                    }
                }
            } else {
                if (startScene->getRequest() == "Solo") {
                    this->isSceneLoaded = true; //On indique qu'elle l'est
                    this->loadSolo(); //On charge le niveau en solo
                } else if (startScene->getRequest() == "Multi") {
                    this->isSceneLoaded = true; //On indique qu'elle l'est
                    this->loadMulti();
                }
                timeLabel = new QLabel();
                timeLabel->setAttribute(Qt::WA_NoSystemBackground);
                timeLabel->setFixedSize(200, 40);
                timeLabel->move(this->width()-230, 10);
                globalScene->addWidget(timeLabel);
            }
        } else if(isSceneLoaded) {
            timeLabel->move(this->width()-230, 10);
            parent->resize(this->width(),this->height());
            globalScene->setSceneRect(0, 0, this->width()-5, this->height()-5);
            if(gameScene->getStatus() == "InGame"){
                if(!gameScene->getIsTimerLaunched()){
                    QString str = "0:00:000";
                    timeLabel->setText(str);
                } else {
                    QString str = gameScene->getTime();
                    timeLabel->setText(str);
                }
            }else if(gameScene->getStatus() == "Paused"){
                if(!gameScene->getIsWidgetLoaded()) {
                    this->pauseWidget = new PauseWidget();
                    this->globalScene ->addWidget(pauseWidget);
                    this->gameScene->setIsWidgetLoaded(true);
                    this->pauseWidget->move((this->width())/2 - (pauseWidget->width())/2,(this->height())/2 - (pauseWidget->height())/2);
                } else {
                    if(gameScene->getRequest() == "Resume"){
                        delete pauseWidget;
                        this->gameScene->setIsWidgetLoaded(false);
                    } else if(pauseWidget->getRequest() == "Resume") {
                        this->gameScene->setRequest("Resume");
                        delete pauseWidget;
                        this->gameScene->setIsWidgetLoaded(false);
                    } else if (pauseWidget->getRequest() == "End") {
                        delete gameScene;
                        this->isChoiceDo = false;
                        delete this->choiceWidget;
                        this->status = "inStart";
                        this->isSceneLoaded = false;
                    }
                }
            } else if(gameScene->getStatus() == "EndScene") {
                if(!gameScene->getIsWidgetLoaded()){
                    this->endWidget = new EndWidget();
                    this->globalScene ->addWidget(endWidget);
                    this->endWidget->move((this->width())/2 - (endWidget->width())/2,(this->height())/2 - (endWidget->height())/2);
                    this->gameScene->setIsWidgetLoaded(true);
                } else {
                    if(endWidget->getRequest()=="End"){
                        delete gameScene;
                        this->isChoiceDo = false;
                        delete this->choiceWidget;
                        this->status = "inStart";
                        this->isSceneLoaded = false;
                    } else if(endWidget->getRequest()=="Restart"){
                        delete gameScene;
                        this->isSceneLoaded = false;
                    }
                }
            }
        }
    } else if(this->status == "inSettings"){
        if(!isSceneLoaded){
            this->loadSettings();
            this->isSceneLoaded = true;
        } else if(this->isSceneLoaded){
            this->settingsScene->adjustSize(this->width(),this->height());
            if(settingsScene->getStatus()=="Ended") {
                this->status = "inStart";
                this->settingsScene->setStatus("doNothing");
                this->isSceneLoaded = false;
            }
        }
    } else if(this->status == "inScores"){
        if(!isSceneLoaded){
            this->loadScores();
            this->isSceneLoaded = true;
        } else if(this->isSceneLoaded){
            this->scoresScene->adjustSize(this->width(),this->height());
            if(scoresScene->getStatus()=="Ended") {
                this->status = "inStart";
                this->scoresScene->setStatus("doNothing");
                this->isSceneLoaded = false;
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
        gameScene = new FirstLevel(this->settingsScene->getKeys(),1,this->choiceWidget->getNamePlayer1()); //Création de la scène du jeu
    } else if(this->choiceWidget->getRequest()=="SecondLevel"){
        gameScene = new SecondLevel(this->settingsScene->getKeys(),1,this->choiceWidget->getNamePlayer1()); //Création de la scène du jeu
    } else if(this->choiceWidget->getRequest()=="ThirdLevel"){
        gameScene = new ThirdLevel(this->settingsScene->getKeys(),1,this->choiceWidget->getNamePlayer1()); //Création de la scène du jeu
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
        gameScene = new FirstLevel(this->settingsScene->getKeys(),2,this->choiceWidget->getNamePlayer1(),this->choiceWidget->getNamePlayer2()); //Création de la scène du jeu
    } else if(this->choiceWidget->getRequest()=="SecondLevel"){
        gameScene = new SecondLevel(this->settingsScene->getKeys(),2,this->choiceWidget->getNamePlayer1(),this->choiceWidget->getNamePlayer2()); //Création de la scène du jeu
    } else if(this->choiceWidget->getRequest()=="ThirdLevel"){
        gameScene = new ThirdLevel(this->settingsScene->getKeys(),2,this->choiceWidget->getNamePlayer1(),this->choiceWidget->getNamePlayer2()); //Création de la scène du jeu
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
    //std::cout << "Load Settings" << std::endl;
    mainView->setScene(settingsScene);
}

void Window::loadScores() {
    //std::cout << "Scores" << std::endl;
    scoresScene = new ScoresScene();
    mainView->setScene(scoresScene);
}

void Window::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape){
        if(this->status=="inStart"){
            qApp->quit();
        } else if(this->status=="inGame" && this->isWidgetLoaded){
            this->isWidgetLoaded=false;
            this->status="inStart";
        }
    }
}
