//
// Created by Remi on 20/04/2020.
//

#include <QtWidgets/QPushButton>
#include <QtCore/QtCore>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <iostream>
#include "EndWidget.h"
#include "../utils.h"

EndWidget::EndWidget() {

    //StyleSheet
    QString style = "QPushButton { border-image:url(../img/buttons/button.png); color : #442A12; }"
                    "QPushButton:hover { border-image:url(../img/buttons/buttonHover.png); color : #543D2B }"
                    "QPushButton:pressed { border-image:url(../img/buttons/buttonOnClick.png); color : #2D2117}";

    //Création des boutons
    restartButton = new QPushButton("Restart"); //Création du bouton de redémarrage de la partie
    this->restartButton->setFixedSize(800,100); //Redimensionnement du bouton
    this->restartButton->setStyleSheet(style); //Application du style
    quitButton = new QPushButton("Quit"); //Création du bouton pour quitter le jeu
    this->quitButton->setFixedSize(400,100); //Redimensionnement du bouton
    this->quitButton->setStyleSheet(style); //Application du style
    menuButton = new QPushButton("Menu"); //Création du bouton pour revenir au menu
    this->menuButton->setFixedSize(400,100); //Redimensionnement du bouton
    this->menuButton->setStyleSheet(style); //Application du style

    //Connexion des boutons à leur slot
    connect(quitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(menuButton,SIGNAL(clicked()),this,SLOT(setEnd()));
    connect(restartButton,SIGNAL(clicked()),this,SLOT(setRestart()));

    //Gestion scores
    std::vector<std::vector<std::string> > temp = createTemp("../src/scenes/levels/temp.txt",2); //Création d'un tableau de tableaux de chaînes de caractères temporaire
                                                                                                 //Chaque chaîne de caractère contient le nom + le temps qu'il a mit à finir le niveau ou s'il est mort
    sort(temp); //Tri du tableau dans l'odre croissant en fonction des temps
    QVBoxLayout* vScoreBox = new QVBoxLayout();
    for(int i = 0; i < temp.size(); i++){
        QLabel* label = new QLabel((std::to_string(i+1) + "." + temp[i][0] + " - " + temp[i][1]).c_str());
        vScoreBox->addWidget(label);
    }
    QWidget* scoreWidget = new QWidget(); //Création du widget de scores
    scoreWidget->setLayout(vScoreBox); //Ajout des scores au widget


    //Ajout des boutons
    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(menuButton);
    hBox->addWidget(quitButton);
    QWidget* hWidget = new QWidget();
    hWidget->setLayout(hBox);

    QVBoxLayout* vBox = new QVBoxLayout();
    vBox->addWidget(scoreWidget);
    vBox->addWidget(restartButton);
    vBox->addWidget(hWidget);
    this->setLayout(vBox); //Ajout des boutons au widget
    this->setAttribute(Qt::WA_NoSystemBackground); //Suppression du background

    remove("../src/scenes/levels/temp.txt"); //Suppression du fichier temporaire
}

//Interactions
void EndWidget::setRestart(){
    this->request="Restart";
}

void EndWidget::setEnd(){
    this->request="End";
}

//Getters
std::string EndWidget::getRequest() {
    return this->request;
}
