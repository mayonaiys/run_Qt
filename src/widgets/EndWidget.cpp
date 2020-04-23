//
// Created by Remi on 20/04/2020.
//

#include <QtWidgets/QPushButton>
#include <QtCore/QtCore>
#include <QtWidgets/QVBoxLayout>
#include "EndWidget.h"

EndWidget::EndWidget() {

    //StyleSheet
    QString style = "QPushButton { border-image:url(../img/button.png); color : #442A12; }"
                    "QPushButton:hover { border-image:url(../img/buttonHover.png); color : #543D2B }"
                    "QPushButton:pressed { border-image:url(../img/buttonOnClick.png); color : #2D2117}";

    //Boutons
    restartButton = new QPushButton("Restart");
    this->restartButton->setFixedSize(800,100);
    this->restartButton->setStyleSheet(style);
    quitButton = new QPushButton("Quit");
    this->quitButton->setFixedSize(400,100);
    this->quitButton->setStyleSheet(style);
    menuButton = new QPushButton("Menu");
    this->menuButton->setFixedSize(400,100);
    this->menuButton->setStyleSheet(style);

    //Connects
    connect(quitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(menuButton,SIGNAL(clicked()),this,SLOT(setEnd()));
    connect(restartButton,SIGNAL(clicked()),this,SLOT(setRestart()));

    //Ajout
    QVBoxLayout* vBox = new QVBoxLayout();
    QHBoxLayout* hBox = new QHBoxLayout();
    QWidget* hWidget = new QWidget();
    vBox->addWidget(restartButton);
    hBox->addWidget(menuButton);
    hBox->addWidget(quitButton);
    hWidget->setLayout(hBox);
    vBox->addWidget(hWidget);
    this->setLayout(vBox);
    this->setAttribute(Qt::WA_NoSystemBackground);
}

void EndWidget::setRestart(){
    this->request="Restart";
}

void EndWidget::setEnd(){
    this->request="End";
}

std::string EndWidget::getRequest() {
    return this->request;
}
