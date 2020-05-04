//
// Created by Remi on 19/04/2020.
//

#include "SettingsScene.h"
#include <fstream>
#include <QKeyEvent>
#include <iostream>

using namespace std;

//Constructeur
SettingsScene::SettingsScene() {

    //StyleSheet
    QString style = "QPushButton { border-image:url(../img/buttons/button.png); color : #442A12; }"
                    "QPushButton:hover { border-image:url(../img/buttons/buttonHover.png); color : #543D2B }"
                    "QPushButton:pressed { border-image:url(../img/buttons/buttonOnClick.png); color : #2D2117}";

    //Boutons
    this->upButton = new QPushButton();
    this->upButton->setFixedSize(400,100);
    this->upButton->setStyleSheet(style);
    this->leftButton = new QPushButton();
    this->leftButton->setFixedSize(400,100);
    this->leftButton->setStyleSheet(style);
    this->rightButton = new QPushButton();
    this->rightButton->setFixedSize(400,100);
    this->rightButton->setStyleSheet(style);

    this->upButton2 = new QPushButton();
    this->upButton2->setFixedSize(400,100);
    this->upButton2->setStyleSheet(style);
    this->leftButton2 = new QPushButton();
    this->leftButton2->setFixedSize(400,100);
    this->leftButton2->setStyleSheet(style);
    this->rightButton2 = new QPushButton();
    this->rightButton2->setFixedSize(400,100);
    this->rightButton2->setStyleSheet(style);

    this->returnButton = new QPushButton("←");
    this->returnButton->setFixedSize(40,40);
    this->returnButton->setStyleSheet(style);
    this->returnButton->setAttribute(Qt::WA_NoSystemBackground);
    this->returnButton->move(10,10);


    //Labels
    QLabel* player1 = new QLabel("PLAYER 1");
    player1->setAttribute(Qt::WA_NoSystemBackground);
    player1->setAlignment(Qt::AlignHCenter);
    player1->setStyleSheet("color:#DB0000;");
    QLabel* player2 = new QLabel("PLAYER 2");
    player2->setAlignment(Qt::AlignHCenter);
    player2->setAttribute(Qt::WA_NoSystemBackground);
    player2->setStyleSheet("color:#0055FF;");

    //Connects
    connect(upButton,SIGNAL(clicked()),this,SLOT(setUp()));
    connect(leftButton,SIGNAL(clicked()),this,SLOT(setLeft()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(setRight()));

    connect(upButton2,SIGNAL(clicked()),this,SLOT(setUp2()));
    connect(leftButton2,SIGNAL(clicked()),this,SLOT(setLeft2()));
    connect(rightButton2,SIGNAL(clicked()),this,SLOT(setRight2()));

    connect(returnButton,SIGNAL(clicked()),this,SLOT(setReturn()));

    //Ajout
    QVBoxLayout* vBoxPlayer1 = new QVBoxLayout();
    QWidget* parentPlayer1 = new QWidget();
    parentPlayer1->setAttribute(Qt::WA_NoSystemBackground);
    vBoxPlayer1->addWidget(player1);
    vBoxPlayer1->addWidget(upButton);
    vBoxPlayer1->addWidget(leftButton);
    vBoxPlayer1->addWidget(rightButton);
    parentPlayer1->setLayout(vBoxPlayer1);

    QVBoxLayout* vBoxPlayer2 = new QVBoxLayout();
    QWidget* parentPlayer2 = new QWidget();
    parentPlayer2->setAttribute(Qt::WA_NoSystemBackground);
    vBoxPlayer2->addWidget(player2);
    vBoxPlayer2->addWidget(upButton2);
    vBoxPlayer2->addWidget(leftButton2);
    vBoxPlayer2->addWidget(rightButton2);
    parentPlayer2->setLayout(vBoxPlayer2);

    QVBoxLayout* vBoxIndications = new QVBoxLayout();
    QWidget* parentIndications = new QWidget();
    parentIndications->setAttribute(Qt::WA_NoSystemBackground);
    QLabel* empty = new QLabel("");
    empty->setAttribute(Qt::WA_NoSystemBackground);
    vBoxIndications->addWidget(empty);
    QLabel* up = new QLabel("Jump");
    up->setAlignment(Qt::AlignTop);
    up->setAttribute(Qt::WA_NoSystemBackground);
    vBoxIndications->addWidget(up);
    QLabel* left = new QLabel("Run left");
    left->setAlignment(Qt::AlignTop);
    left->setAttribute(Qt::WA_NoSystemBackground);
    vBoxIndications->addWidget(left);
    QLabel* right = new QLabel("Run right");
    right->setAlignment(Qt::AlignTop);
    right->setAttribute(Qt::WA_NoSystemBackground);
    vBoxIndications->addWidget(right);
    parentIndications->setLayout(vBoxIndications);

    QHBoxLayout* hBox = new QHBoxLayout();
    settingsWidget = new QWidget();
    hBox->addWidget(parentIndications);
    hBox->addWidget(parentPlayer1);
    hBox->addWidget(parentPlayer2);
    settingsWidget->setLayout(hBox);
    settingsWidget->move(250,200);
    settingsWidget->setStyleSheet("background-color:rgba(0, 0, 0, 50);");

    this->addWidget(settingsWidget);
    this->addWidget(returnButton);

    ifstream configFile("../config/config.txt");
    int i = 0;
    if(configFile){
        string line;
        while(getline(configFile,line) && i<6){
            keys.push_back(Qt::Key(std::stoi(line)));
            temp.push_back(line);
            i++;
        }
    } else {
        ofstream file("../config/config.txt");
        file << "16777235" << endl;
        file << "16777234" << endl;
        file << "16777236" << endl;
        file << "90" << endl;
        file << "81" << endl;
        file << "68" << endl;
        string line;
        ifstream nfile("../config/config.txt");
        while(getline(nfile,line) && i<6){
            keys.push_back(Qt::Key(std::stoi(line)));
            temp.push_back(line);
            i++;
        }
    }
    this->upButton->setText(QKeySequence(std::stoi(temp[0])).toString());
    this->leftButton->setText(QKeySequence(std::stoi(temp[1])).toString());
    this->rightButton->setText(QKeySequence(std::stoi(temp[2])).toString());

    this->upButton2->setText(QKeySequence(std::stoi(temp[3])).toString());
    this->leftButton2->setText(QKeySequence(std::stoi(temp[4])).toString());
    this->rightButton2->setText(QKeySequence(std::stoi(temp[5])).toString());

}

//
void SettingsScene::keyPressEvent(QKeyEvent *event) {
    if(this->status=="IsSettingUp"){
        if(event->key() != Qt::Key_Escape) {
            verification(to_string(event->key()));
            this->temp[0] = to_string(event->key());
            this->upButton->setText(QKeySequence(event->key()).toString());
            this->keys[0] = Qt::Key(event->key());
        }
        this->status ="doNothing";
    } else if(this->status=="IsSettingLeft"){
        if(event->key() != Qt::Key_Escape) {
            verification(to_string(event->key()));
            this->temp[1] = to_string(event->key());
            this->leftButton->setText(QKeySequence(event->key()).toString());
            this->keys[1] = Qt::Key(event->key());
        }
        this->status ="doNothing";
    } else if(this->status=="IsSettingRight"){
        if(event->key() != Qt::Key_Escape) {
            verification(to_string(event->key()));
            this->temp[2] = to_string(event->key());
            this->rightButton->setText(QKeySequence(event->key()).toString());
            this->keys[2] = Qt::Key(event->key());
        }
        this->status ="doNothing";
    } else if(this->status=="IsSettingUp2"){
        if(event->key() != Qt::Key_Escape) {
            verification(to_string(event->key()));
            this->temp[3] = to_string(event->key());
            this->upButton2->setText(QKeySequence(event->key()).toString());
            this->keys[3] = Qt::Key(event->key());
        }
        this->status ="doNothing";
    } else if(this->status=="IsSettingLeft2"){
        if(event->key() != Qt::Key_Escape) {
            verification(to_string(event->key()));
            this->temp[4] = to_string(event->key());
            this->leftButton2->setText(QKeySequence(event->key()).toString());
            this->keys[4] = Qt::Key(event->key());
        }
        this->status ="doNothing";
    } else if(this->status=="IsSettingRight2"){
        if(event->key() != Qt::Key_Escape){
            verification(to_string(event->key()));
            this->temp[5]=to_string(event->key());
            this->rightButton2->setText(QKeySequence(event->key()).toString());
            this->keys[5]=Qt::Key(event->key());
        }
        this->status ="doNothing";
    }
    if(event->key()==Qt::Key_Escape){
        if(isConfigComplete()){
            remove("../config/config.txt");
            ofstream file("../config/config.txt");
            for(int i = 0; i < 6; i++){
                file << temp[i] << std::endl;
            }
            this->status="Ended";
        }
    }
}

void SettingsScene::verification(std::string key){
    if(key == temp[0]){
        temp[0]="";
        upButton->setText("");
    } else if(key == temp[1]){
        temp[1]="";
        leftButton->setText("");
    } else if(key == temp[2]){
        temp[2]="";
        rightButton->setText("");
    } else if(key == temp[3]){
        temp[3]="";
        upButton2->setText("");
    } else if(key == temp[4]){
        temp[4]="";
        leftButton2->setText("");
    } else if(key == temp[5]){
        temp[5]="";
        rightButton2->setText("");
    }
}

bool SettingsScene::isConfigComplete() {
    for(int i = 0; i < this->temp.size(); i++){
        if(this->temp[i]==""){
            return false;
        }
    }
    return true;
}

//Getters&Setters
void SettingsScene::setUp() {
    this->status = "IsSettingUp";
}

void SettingsScene::setLeft() {
    this->status = "IsSettingLeft";
}

void SettingsScene::setRight() {
    this->status = "IsSettingRight";
}

void SettingsScene::setUp2() {
    this->status = "IsSettingUp2";
}

void SettingsScene::setLeft2() {
    this->status = "IsSettingLeft2";
}

void SettingsScene::setRight2() {
    this->status = "IsSettingRight2";
}

std::vector<Qt::Key> SettingsScene::getKeys() {
    return this->keys;
}

std::string SettingsScene::getStatus() {
    return this->status;
}

void SettingsScene::setStatus(std::string status) {
    this->status = status;
}

void SettingsScene::setReturn() {
    std::cout << "return" << std::endl;
    if(isConfigComplete()){
        remove("../config/config.txt");
        ofstream file("../config/config.txt");
        for(int i = 0; i < 6; i++){
            file << temp[i] << std::endl;
        }
        this->status="Ended";
    }
}


//Ajustement
void SettingsScene::adjustSize(int width, int height) {
    this->w = width-5;
    this->h = height-5;
    this->setBackground("../img/backgrounds/settingsBackground.png");
    this->settingsWidget->move(width/2 - settingsWidget->width()/2,height/2 - settingsWidget->height()/2);
}
