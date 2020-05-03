//
// Created by Remi on 20/04/2020.
//

#include "ScoresScene.h"
#include "../utils.h"
#include <fstream>
#include <iostream>

using namespace std;

ScoresScene::ScoresScene(){
    //StyleSheet
    this->style = "QPushButton { border-image:url(../img/button.png); color : #442A12; }"
                    "QPushButton:hover { border-image:url(../img/buttonHover.png); color : #543D2B }"
                    "QPushButton:pressed { border-image:url(../img/buttonOnClick.png); color : #2D2117}";

    //Ajout bouton
    this->returnButton = new QPushButton("←");
    this->returnButton->setFixedSize(40,40);
    this->returnButton->setStyleSheet(style);
    this->returnButton->setAttribute(Qt::WA_NoSystemBackground);
    this->returnButton->move(10,10);
    this->addWidget(returnButton);

    this->rightButton = new QPushButton("Next");
    this->rightButton->setStyleSheet(style);
    this->leftButton = new QPushButton("Previous");
    this->leftButton->setStyleSheet(style);

    QHBoxLayout* hButtonsBox = new QHBoxLayout();
    this->buttonPanel = new QWidget();
    hButtonsBox->addWidget(this->leftButton);
    hButtonsBox->addWidget(this->rightButton);

    this->buttonPanel->setLayout(hButtonsBox);
    this->buttonPanel->setAttribute(Qt::WA_NoBackground);

    this->addWidget(this->buttonPanel);

    QTimer* timer = new QTimer();
    timer->start(30);

    //Connect
    connect(returnButton,SIGNAL(clicked()),this,SLOT(setReturn()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(right()));
    connect(leftButton,SIGNAL(clicked()),this,SLOT(left()));
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));

    this->currentScoreList = 1; //Liste actuelle
    this->isListLoaded = false;

}


void ScoresScene::update() {
    if(this->currentScoreList==1){
        if(!this->isListLoaded){
            //Gestion boutons
            this->leftButton->setEnabled(false);
            this->leftButton->setStyleSheet("border-image:url(../img/buttonHover.png);");

            //Liste chargée
            this->isListLoaded = true;

            this->currentList = new QWidget();
            this->list1 = createList("../config/scores1.txt");
            this->currentList->setLayout(this->list1);
            this->addWidget(currentList);
            this->buttonPanel->setFixedWidth(this->currentList->width());
            this->currentList->setStyleSheet("background-color:rgba(0, 0, 0, 50);");
            this->currentList->move((this->width())/2 - (this->currentList->width())/2,30);
            this->buttonPanel->move((this->width())/2 - (this->currentList->width())/2,this->currentList->pos().y()+this->currentList->height() + 10);

            if(this->currentList->height() + this->buttonPanel->height() +20 > this->height()){
                this->currentList->setFixedHeight(this->height()-120);
            }
        }
    } else if(this->currentScoreList==2){
        if(!this->isListLoaded){
            //Gestion boutons
            this->rightButton->setEnabled(true);
            this->rightButton->setStyleSheet(this->style);
            this->leftButton->setEnabled(true);
            this->leftButton->setStyleSheet(this->style);

            //Liste chargée
            this->isListLoaded = true;

            this->currentList = new QWidget();
            this->list2 = createList("../config/scores2.txt");
            this->currentList->setLayout(this->list2);
            this->addWidget(currentList);
            this->buttonPanel->setFixedWidth(this->currentList->width());
            this->currentList->setStyleSheet("background-color:rgba(0, 0, 0, 50);");
            this->currentList->move((this->width())/2 - (this->currentList->width())/2,30);
            this->buttonPanel->move((this->width())/2 - (this->currentList->width())/2,this->currentList->pos().y()+this->currentList->height() + 10);
            if(this->currentList->height() + this->buttonPanel->height() +20 > this->height()){
                this->currentList->setFixedHeight(this->height()-120);
            }
        }
    } else if(this->currentScoreList==3){
        if(!this->isListLoaded){
            //Gestion boutons
            this->rightButton->setEnabled(false);
            this->rightButton->setStyleSheet("border-image:url(../img/buttonHover.png);");

            //Liste chargée
            this->isListLoaded = true;

            this->currentList = new QWidget();
            this->list3 = createList("../config/scores3.txt");
            this->currentList->setLayout(this->list3);
            this->addWidget(currentList);
            this->buttonPanel->setFixedWidth(this->currentList->width());
            this->currentList->setStyleSheet("background-color:rgba(0, 0, 0, 50);");
            this->currentList->move((this->width())/2 - (this->currentList->width())/2,30);
            this->buttonPanel->move((this->width())/2 - (this->currentList->width())/2,this->currentList->pos().y()+this->currentList->height() + 10);
            if(this->currentList->height() + this->buttonPanel->height() +20 > this->height()){
                this->currentList->setFixedHeight(this->height()-120);
            }
        }
    }
}

void ScoresScene::setStatus(std::string status) {
    this->status = status;
}

std::string ScoresScene::getStatus(){
    return this->status;
}

void ScoresScene::keyPressEvent(QKeyEvent* event) {
    if(event->key() == Qt::Key_Escape){
        this->status = "Ended";
    }
}

void ScoresScene::reWrite(const char *scoreFile, std::vector<std::vector<std::string> > temp) {
    remove(scoreFile);
    ofstream file(scoreFile);
    for(auto & i : temp){
        string str = i[0] + "," + i[1];
        file << str << std::endl;
    }
}

void ScoresScene::setReturn() {
    this->status = "Ended";
}

QLabel* ScoresScene::createLabel(QString str) {
    QLabel* newLabel = new QLabel(str);
    newLabel->setAttribute(Qt::WA_NoSystemBackground);
    newLabel->setAlignment(Qt::AlignHCenter);
    return newLabel;
}

QVBoxLayout* ScoresScene::createList(std::string scoreFile) {
    //Tableau temp
    std::vector<std::vector<std::string> > temp = createTemp(scoreFile);

    //Affichage
    QVBoxLayout* vBoxRanking = new QVBoxLayout();
    QVBoxLayout* vBoxName = new QVBoxLayout();
    QVBoxLayout* vBoxTime = new QVBoxLayout();

    QLabel* ranking = createLabel("Ranking");
    ranking->setStyleSheet("color:#CECECE;");
    QLabel* name = createLabel("Name");
    name->setStyleSheet("color:#CECECE;");
    QLabel* time = createLabel("Time (mm:ss:ms)");
    time->setStyleSheet("color:#CECECE;");

    vBoxRanking->addWidget(ranking);
    vBoxName->addWidget(name);
    vBoxTime->addWidget(time);

    std::string color;


    sort(temp);
    this->reWrite(scoreFile.c_str(),temp);
    for(int i = 0; i < 10; i++){
        QLabel* part1 = createLabel((to_string(i+1) + "-").c_str());
        QLabel* part2;
        QLabel* part3;
        if(i < temp.size()){
            part2 = createLabel((temp[i][0]).c_str());
            part3 = createLabel((temp[i][1]).c_str());
        } else {
            part2 = createLabel(QString(""));
            part3 = createLabel(QString(""));
        }
        vBoxRanking->addWidget(part1);
        vBoxName->addWidget(part2);
        vBoxTime->addWidget(part3);
        if(i==0){
            color = "#46EA00";
        } else if(i==1){
            color = "#F2A900";
        } else if(i==2){
            color = "#EF0700";
        } else {
            color = "#AFAFAF";
        }
        QString labelStyle = ("color:" + color + ";").c_str();
        part1->setStyleSheet(labelStyle);
        part2->setStyleSheet(labelStyle);
        part3->setStyleSheet(labelStyle);
    }

    QWidget* parentRanking = new QWidget();
    parentRanking->setLayout(vBoxRanking);
    parentRanking->setAttribute(Qt::WA_NoSystemBackground);
    QWidget* parentName = new QWidget();
    parentName->setLayout(vBoxName);
    parentName->setAttribute(Qt::WA_NoSystemBackground);
    QWidget* parentTime = new QWidget();
    parentTime->setLayout(vBoxTime);
    parentTime->setAttribute(Qt::WA_NoSystemBackground);

    QLabel* level = createLabel(("Level " + to_string(this->currentScoreList)).c_str());
    level->setStyleSheet("color:#CECECE;");

    QVBoxLayout* globalVBox = new QVBoxLayout();

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(parentRanking);
    hBox->addWidget(parentName);
    hBox->addWidget(parentTime);

    globalVBox->addWidget(level);
    globalVBox->addLayout(hBox);

    return globalVBox;
}

void ScoresScene::right() {
    delete this->currentList;
    this->currentScoreList++;
    this->isListLoaded = false;
}

void ScoresScene::left() {
    delete this->currentList;
    this->currentScoreList--;
    this->isListLoaded = false;
}

void ScoresScene::adjustSize(int width, int height) {
    this->w = width-5;
    this->h = height-5;
    this->setBackground("../img/settingsBackground.png");
    if(this->isListLoaded){
        this->currentList->move((this->width())/2 - (this->currentList->width())/2,30);
        this->buttonPanel->move((this->width())/2 - (this->currentList->width())/2,this->currentList->pos().y()+this->currentList->height() + 10);
        //std::cout << (this->currentList->height() + this->buttonPanel->height() + 10) << " et " << this->height() << std::endl;
        if(this->currentList->height() + this->buttonPanel->height() +20 > this->height()){
            this->currentList->setFixedHeight(this->height()-120);
        } else if(this->currentList->height()<650){
            this->currentList->setFixedHeight(this->height()-120);
        }
    }
}
