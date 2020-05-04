//
// Created by Remi on 20/04/2020.
//

#include "PauseWidget.h"

//Constructeur
PauseWidget::PauseWidget() {
    //StyleSheet
    QString style = "QPushButton { border-image:url(../img/buttons/button.png); color : #442A12; }"
                    "QPushButton:hover { border-image:url(../img/buttons/buttonHover.png); color : #543D2B }"
                    "QPushButton:pressed { border-image:url(../img/buttons/buttonOnClick.png); color : #2D2117}";

    //Boutons
    this->resumeButton = new QPushButton("Resume"); //Création du bouton de retour en jeu
    this->resumeButton->setStyleSheet(style); //Application du style
    this->resumeButton->setFixedSize(400,100); //Modification de la taille
    this->menuButton = new QPushButton("Menu"); //Création du bouton de retour au menu
    this->menuButton->setStyleSheet(style); //Application du style
    this->menuButton->setFixedSize(400,100); //Modification de la taille
    this->quitButton = new QPushButton("Quit"); //Création du bouton pour quitter le jeu
    this->quitButton->setStyleSheet(style); //Application du style
    this->quitButton->setFixedSize(400,100); //Modification de la taille

    //Connexion des boutons à leurs slots
    connect(this->resumeButton,SIGNAL(clicked()),this,SLOT(setResume()));
    connect(this->menuButton,SIGNAL(clicked()),this,SLOT(setEnd()));
    connect(this->quitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    //Ajout
    QVBoxLayout* vBox = new QVBoxLayout();
    vBox->addWidget(this->resumeButton);
    vBox->addWidget(this->menuButton);
    vBox->addWidget(this->quitButton);
    this->setLayout(vBox); //Ajout des boutons au widget
    this->setAttribute(Qt::WA_NoSystemBackground); //Suppression du background du widget
}

//Interactions
void PauseWidget::setEnd() {
    this->request="End";
}

void PauseWidget::setResume() {
    this->request="Resume";
}

//Getters
std::string PauseWidget::getRequest() {
    return this->request;
}

