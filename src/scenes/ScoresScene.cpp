//
// Created by Remi on 20/04/2020.
//

#include "ScoresScene.h"
#include <fstream>
#include <iostream>

using namespace std;

ScoresScene::ScoresScene(){

    //Ajout fond
    this->setBackground("../img/settingsBackground.png");

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
            this->currentList->move((this->width())/2 - (this->currentList->width())/2,200);
            this->addWidget(currentList);
            this->buttonPanel->setFixedWidth(this->currentList->width());
            this->buttonPanel->move((this->width())/2 - (this->currentList->width())/2,this->currentList->pos().y()+this->currentList->height() + 10);
            this->currentList->setStyleSheet("background-color:rgba(0, 0, 0, 50);");
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
            this->currentList->move((this->width())/2 - (this->currentList->width())/2,200);
            this->addWidget(currentList);
            this->buttonPanel->setFixedWidth(this->currentList->width());
            this->buttonPanel->move((this->width())/2 - (this->currentList->width())/2,this->currentList->pos().y()+this->currentList->height() + 10);
            this->currentList->setStyleSheet("background-color:rgba(0, 0, 0, 50);");
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
            this->currentList->move((this->width())/2 - (this->currentList->width())/2,200);
            this->addWidget(currentList);
            this->buttonPanel->setFixedWidth(this->currentList->width());
            this->buttonPanel->move((this->width())/2 - (this->currentList->width())/2,this->currentList->pos().y()+this->currentList->height() + 10);
            this->currentList->setStyleSheet("background-color:rgba(0, 0, 0, 50);");
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

vector<string> ScoresScene::cutString(string str){
    vector<string> tempVect;
    int index = str.find(',');
    string strTemp1 = str.substr(0,index);
    string strTemp2 = str.substr(index+1,str.size());
    tempVect.push_back(strTemp1);
    tempVect.push_back(strTemp2);
    return tempVect;
}

void ScoresScene::sort(std::vector<std::vector<std::string> > & temp){
    vector<string> t;
    for(int i = 0; i < temp.size(); i++){
        for(int u = 0; u < temp.size(); u++){
            std::cout << stringToNumber(temp[i][1]) << std::endl;
            if(stringToNumber(temp[i][1]) < stringToNumber(temp[u][1]) && i != u){
                t = temp[i] ;
                temp[i] = temp[u];
                temp[u] = t;
            }
        }
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

QHBoxLayout* ScoresScene::createList(std::string scoreFile) {
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

    if(temp.size()==0){
        vBoxRanking->addWidget(createLabel("Nothing"));
        vBoxName->addWidget(createLabel("to"));
        vBoxTime->addWidget(createLabel("show"));
    } else {
        this->sort(temp);
        this->reWrite(scoreFile.c_str(),temp);
        int end;
        if(temp.size() < 10){
            end = temp.size();
        } else {
            end = 10;
        }
        for(int i = 0; i < end; i++){
            QLabel* part1 = createLabel((to_string(i+1) + "-").c_str());
            QLabel* part2 = createLabel((temp[i][0]).c_str());
            QLabel* part3 = createLabel((temp[i][1]).c_str());
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

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(parentRanking);
    hBox->addWidget(parentName);
    hBox->addWidget(parentTime);

    return hBox;
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

std::vector<std::vector<std::string> > ScoresScene::createTemp(std::string scoreFile) {
    //Lecture du fichier
    std::vector<std::vector<std::string> > temp;
    ifstream scoresFile(scoreFile);
    if(scoresFile){
        string line;
        while(getline(scoresFile,line)){
            temp.push_back(cutString(line));
        }
    } else {
        ofstream file(scoreFile);
    }
    return temp;
}

double charToDouble(char c){
    return (double)c-48;
}

double ScoresScene::stringToNumber(std::string str) {
    return charToDouble(str[0])*600 + charToDouble(str[1])*60 + charToDouble(str[3])*10 + charToDouble(str[4]) + charToDouble(str[6])/10 + charToDouble(str[7])/100;
}
