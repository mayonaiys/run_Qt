//
// Created by Remi on 19/04/2020.
//

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

    //Ajout label de crédits
    QLabel* credit = new QLabel("Rémi ADDE - 2020");
    credit->setFont(QFont("Joystick",18));
    credit->setAlignment(Qt::AlignCenter);

    //Connexion des boutons à leurs slots
    connect(this->soloButton,SIGNAL(clicked()),this,SLOT(setSolo()));
    connect(this->multiButton,SIGNAL(clicked()),this,SLOT(setMulti()));
    connect(this->settingsButton,SIGNAL(clicked()),this,SLOT(setSettings()));
    connect(this->scoresButton,SIGNAL(clicked()),this,SLOT(setScores()));

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(this->settingsButton);
    hBox->addWidget(this->scoresButton);
    QWidget* hWidget = new QWidget();
    hWidget->setLayout(hBox);
    QVBoxLayout* vBox = new QVBoxLayout();
    vBox->addWidget(this->soloButton);
    vBox->addWidget(this->multiButton);
    vBox->addWidget(hWidget);
    vBox->addWidget(credit);

    this->menu = new QWidget();
    this->menu->setAttribute(Qt::WA_NoSystemBackground);
    this->menu->setLayout(vBox);
    this->addWidget(this->menu); //Ajout du pannel de boutons
}

void StartScene::disableButtons() {
    this->soloButton->setEnabled(false); //Désactivation du bouton
    this->multiButton->setEnabled(false); //Désactivation du bouton
    this->settingsButton->setEnabled(false); //Désactivation du bouton
    this->scoresButton->setEnabled(false); //Désactivation du bouton
}


//Interactions
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

//Ajustement
void StartScene::adjustSize(int width, int height) {
    //Initialisation de la taille de la scène en fonction de la taille de la fenêtre
    this->w = width-5;
    this->h = height-5;
    this->setBackground("../img/backgrounds/startBackground.png"); //Application du fond d'écran en fonction de la nouvelle taille de fenêtre
    this->menu->move(width/2 - this->menu->width()/2,height/2 - this->menu->height()/2); //Déplacement du pannel en fonction de la taille de la fenêtre
}
