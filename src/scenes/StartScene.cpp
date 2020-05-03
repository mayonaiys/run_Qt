//
// Created by Remi on 19/04/2020.
//

#include <iostream>
#include "StartScene.h"

StartScene::StartScene() {
    //StyleSheet
    QString style = "QPushButton { border-image:url(../img/buttons/button.png); color : #442A12; }"
                    "QPushButton:hover { border-image:url(../img/buttons/buttonHover.png); color : #543D2B }"
                    "QPushButton:pressed { border-image:url(../img/buttons/buttonOnClick.png); color : #2D2117}";

    //Ajout des boutons
    this->soloButton = new QPushButton("Solo");
    this->soloButton->setStyleSheet(style);
    this->soloButton->setFixedSize(400,100);

    this->multiButton = new QPushButton("Multiplayer");
    this->multiButton->setStyleSheet(style);
    this->multiButton->setFixedSize(400,100);

    this->settingsButton = new QPushButton("Settings");
    this->settingsButton->setStyleSheet(style);
    this->settingsButton->setFixedSize(200,100);

    this->scoresButton = new QPushButton("Scores");
    this->scoresButton->setStyleSheet(style);
    this->scoresButton->setFixedSize(200,100);

    //Ajout label
    QLabel* credit = new QLabel("Rémi ADDE - 2020");

    //Connects
    connect(soloButton,SIGNAL(clicked()),this,SLOT(setSolo()));
    connect(multiButton,SIGNAL(clicked()),this,SLOT(setMulti()));
    connect(settingsButton,SIGNAL(clicked()),this,SLOT(setSettings()));
    connect(scoresButton,SIGNAL(clicked()),this,SLOT(setScores()));

    QVBoxLayout* vBox = new QVBoxLayout();
    QHBoxLayout* hBox = new QHBoxLayout();
    panel = new QWidget();
    panel->setAttribute(Qt::WA_NoSystemBackground);
    QWidget* hWidget = new QWidget();
    vBox->addWidget(soloButton);
    vBox->addWidget(multiButton);
    hBox->addWidget(settingsButton);
    hBox->addWidget(scoresButton);
    hWidget->setLayout(hBox);
    vBox->addWidget(hWidget);
    vBox->addWidget(credit);
    panel->setLayout(vBox);
    this->addWidget(panel);
}

void StartScene::setSolo() {
    this->request = "Solo";
}

void StartScene::setMulti() {
    this->request = "Multi";
}

void StartScene::setSettings() {
    this->request = "Settings";
}

void StartScene::setScores() {
    this->request = "Scores";
}

std::string StartScene::getRequest() {
    return this->request;
}

void StartScene::disableButtons() {
    this->soloButton->setEnabled(false);
    this->multiButton->setEnabled(false);
    this->settingsButton->setEnabled(false);
    this->scoresButton->setEnabled(false);
}

void StartScene::adjustSize(int width, int height) {
    this->w = width-5;
    this->h = height-5;
    this->setBackground("../img/backgrounds/startBackground.png");
    this->panel->move(width/2 - panel->width()/2,height/2 - panel->height()/2);
}
