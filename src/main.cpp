#include <QApplication>
#include <iostream>
#include <QtWidgets/QWidget>
#include "Window.h"

int main(int argc, char **argv) {
    QApplication game(argc,argv);

    //Ajout police pesonnalisée
    QFontDatabase::addApplicationFont("../fonts/Joystick-5KjV.ttf");
    QFont font = QFont("Joystick",50);
    game.setFont(font);

    //Ajout Splash
    QSplashScreen* splash = new QSplashScreen();
    splash->setWindowFlags(Qt::FramelessWindowHint);
    QPixmap pixmap("../img/splash.png");
    splash->setPixmap(pixmap);
    splash->resize(580,361);
    splash->show();

    //Création fenêtre principale
    Window window;

    QTimer::singleShot(10,splash,SLOT(close()));
    QTimer::singleShot(10,&window,SLOT(show()));

    return game.exec();
}