//
// Created by Remi on 20/04/2020.
//

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QApplication>
#include <iostream>
#include "PauseWidget.h"

PauseWidget::PauseWidget() {
    //StyleSheet
    QString style = "QPushButton { border-image:url(../img/button.png); color : #442A12; }"
                    "QPushButton:hover { border-image:url(../img/buttonHover.png); color : #543D2B }"
                    "QPushButton:pressed { border-image:url(../img/buttonOnClick.png); color : #2D2117}";

    //Boutons
    resumeButton = new QPushButton("Resume");
    this->resumeButton->setStyleSheet(style);
    this->resumeButton->setFixedSize(400,100);
    menuButton = new QPushButton("Menu");
    this->menuButton->setStyleSheet(style);
    this->menuButton->setFixedSize(400,100);
    quitButton = new QPushButton("Quit");
    this->quitButton->setStyleSheet(style);
    this->quitButton->setFixedSize(400,100);

    //Connects
    connect(resumeButton,SIGNAL(clicked()),this,SLOT(setResume()));
    connect(menuButton,SIGNAL(clicked()),this,SLOT(setEnd()));
    connect(quitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    //Ajout
    QVBoxLayout* vBox = new QVBoxLayout();
    vBox->addWidget(resumeButton);
    vBox->addWidget(menuButton);
    vBox->addWidget(quitButton);
    this->setLayout(vBox);
    this->setAttribute(Qt::WA_NoSystemBackground);
}

void PauseWidget::setEnd() {
    this->request="End";
}

void PauseWidget::setResume() {
    this->request="Resume";
}

std::string PauseWidget::getRequest() {
    return this->request;
}

