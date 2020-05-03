//
// Created by Remi on 21/04/2020.
//

#include <QtWidgets/QVBoxLayout>
#include <fstream>
#include <iostream>
#include "ChoiceWidget.h"

using namespace std;

ChoiceWidget::ChoiceWidget(int nbPlayers){
    //StyleSheet
    QString style = "QPushButton { border-image:url(../img/buttons/button.png); color : #442A12; }"
                    "QPushButton:hover { border-image:url(../img/buttons/buttonHover.png); color : #543D2B }"
                    "QPushButton:pressed { border-image:url(../img/buttons/buttonOnClick.png); color : #2D2117}";

    this->nbPlayers = nbPlayers;

    QHBoxLayout* hBox = new QHBoxLayout();

    QVBoxLayout* vBox1 = new QVBoxLayout();
    this->inputPlayer1 = new QLineEdit("Player1");
    this->validPlayer1 = new QPushButton("Valid");
    this->validPlayer1->setStyleSheet(style);
    vBox1->addWidget(inputPlayer1);
    vBox1->addWidget(validPlayer1);
    hBox->addLayout(vBox1);

    connect(validPlayer1,SIGNAL(clicked()),this,SLOT(setPlayerOneValid()));
    this->isPlayer1Valid = false;

    QWidget* parentHBox = new QWidget();
    parentHBox->setLayout(hBox);
    parentHBox->setAttribute(Qt::WA_NoSystemBackground);

    this->firstLevel = new QPushButton();
    this->firstLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel1.png); }"
                                    "QPushButton:hover { border-image:url(../img/buttons/iconLevel1Hover.png); }"
                                    "QPushButton:pressed { border-image:url(../img/buttons/iconLevel1Pressed.png); }");

    this->secondLevel = new QPushButton();
    this->secondLevel->setEnabled(false);
    this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevelBlocked.png); }");

    this->thirdLevel = new QPushButton();
    this->thirdLevel->setEnabled(false);
    this->thirdLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevelBlocked.png); }");

    connect(firstLevel,SIGNAL(clicked()),this,SLOT(setFirstLevel()));
    connect(secondLevel,SIGNAL(clicked()),this,SLOT(setSecondLevel()));
    connect(thirdLevel,SIGNAL(clicked()),this,SLOT(setThirdLevel()));

    if(this->nbPlayers == 2){
        QVBoxLayout* vBox2 = new QVBoxLayout();
        this->inputPlayer2 = new QLineEdit("Player2");
        this->validPlayer2 = new QPushButton("Valid");
        this->validPlayer2->setStyleSheet(style);
        vBox2->addWidget(inputPlayer2);
        vBox2->addWidget(validPlayer2);
        hBox->addLayout(vBox2);
        connect(validPlayer1,SIGNAL(clicked()),this,SLOT(setPlayerTwoValid()));
        this->isPlayer2Valid = false;

        this->firstLevel->setFixedHeight(225);
        this->secondLevel->setFixedHeight(225);
        this->thirdLevel->setFixedHeight(225);
    } else if(this->nbPlayers==1){
        this->firstLevel->setFixedHeight(120);
        this->secondLevel->setFixedHeight(120);
        this->thirdLevel->setFixedHeight(120);
    }

    //Lecture du fichier
    ifstream scoresFile("../config/levels.txt");
    if(scoresFile){
        string line;
        while(getline(scoresFile,line)){
            if(line=="kj3c7_DahY"){
                this->secondLevel->setEnabled(true);
                this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel2.png); }"
                                                 "QPushButton:hover { border-image:url(../img/buttons/iconLevel2Hover.png); }"
                                                 "QPushButton:pressed { border-image:url(../img/buttons/iconLevel2Pressed.png); }");
            } else if(line=="b74r8_aLAnZ"){
                this->secondLevel->setEnabled(true);
                this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel2.png); }"
                                                 "QPushButton:hover { border-image:url(../img/buttons/iconLevel2Hover.png); }"
                                                 "QPushButton:pressed { border-image:url(../img/buttons/iconLevel2Pressed.png); }");
                this->thirdLevel->setEnabled(true);
                this->thirdLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel3.png); }"
                                                "QPushButton:hover { border-image:url(../img/buttons/iconLevel3Hover.png); }"
                                                "QPushButton:pressed { border-image:url(../img/buttons/iconLevel3Pressed.png); }");
            }
        }
    } else {
        ofstream file("../config/levels.txt");
        file << "zK7k9_vYmN";
    }

    this->isLevelSet = false;

    QHBoxLayout* hBoxLevels = new QHBoxLayout();
    QWidget* parentHBoxLevels = new QWidget();
    hBoxLevels->addWidget(firstLevel);
    hBoxLevels->addWidget(secondLevel);
    hBoxLevels->addWidget(thirdLevel);
    parentHBoxLevels->setLayout(hBoxLevels);
    parentHBoxLevels->setAttribute(Qt::WA_NoSystemBackground);

    QVBoxLayout* vBoxGlobal = new QVBoxLayout();
    vBoxGlobal->addWidget(parentHBox);
    vBoxGlobal->addWidget(parentHBoxLevels);

    this->setLayout(vBoxGlobal);
    this->setStyleSheet("background-color:rgba(0, 0, 0, 50);");
}

void ChoiceWidget::setPlayerOneValid() {
    this->namePlayer1 = this->inputPlayer1->text();
    this->isPlayer1Valid = true;
}

void ChoiceWidget::setPlayerTwoValid() {
    this->namePlayer2 = this->inputPlayer2->text();
    this->isPlayer2Valid = true;
}

bool ChoiceWidget::getIsPlayersValid() {
    if(this->nbPlayers==1){
        return this->isPlayer1Valid;
    } else if(this->nbPlayers==2){
        return this->isPlayer1Valid && this->isPlayer2Valid;
    }
}

QString ChoiceWidget::getNamePlayer1() {
    return this->namePlayer1;
}

QString ChoiceWidget::getNamePlayer2() {
    return this->namePlayer2;
}

std::string ChoiceWidget::getRequest() {
    return this->request;
}

void ChoiceWidget::setFirstLevel() {
    this->isLevelSet = true;
    this->firstLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel1Validate.png); }");
    this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel2.png); }"
                                     "QPushButton:hover { border-image:url(../img/buttons/iconLevel2Hover.png); }"
                                     "QPushButton:pressed { border-image:url(../img/buttons/iconLevel2Pressed.png); }");
    this->thirdLevel->setEnabled(true);
    this->thirdLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel3.png); }"
                                    "QPushButton:hover { border-image:url(../img/buttons/iconLevel3Hover.png); }"
                                    "QPushButton:pressed { border-image:url(../img/buttons/iconLevel3Pressed.png); }");
    this->request = "FirstLevel";
}

void ChoiceWidget::setSecondLevel() {
    this->isLevelSet = true;
    this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel2Validate.png); }");
    this->firstLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel1.png); }"
                                     "QPushButton:hover { border-image:url(../img/buttons/iconLevel1Hover.png); }"
                                     "QPushButton:pressed { border-image:url(../img/buttons/iconLevel1Pressed.png); }");
    this->thirdLevel->setEnabled(true);
    this->thirdLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel3.png); }"
                                    "QPushButton:hover { border-image:url(../img/buttons/iconLevel3Hover.png); }"
                                    "QPushButton:pressed { border-image:url(../img/buttons/iconLevel3Pressed.png); }");
    this->request = "SecondLevel";
}

void ChoiceWidget::setThirdLevel() {
    this->isLevelSet = true;
    this->thirdLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel3Validate.png); }");
    this->firstLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel1.png); }"
                                    "QPushButton:hover { border-image:url(../img/buttons/iconLevel1Hover.png); }"
                                    "QPushButton:pressed { border-image:url(../img/buttons/iconLevel1Pressed.png); }");
    this->thirdLevel->setEnabled(true);
    this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel2.png); }"
                                    "QPushButton:hover { border-image:url(../img/buttons/iconLevel2Hover.png); }"
                                    "QPushButton:pressed { border-image:url(../img/buttons/iconLevel2Pressed.png); }");
    this->request = "ThirdLevel";
}

bool ChoiceWidget::getIsLevelSet() {
    return this->isLevelSet;
}

