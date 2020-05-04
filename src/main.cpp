#include <QApplication>
#include "Window.h"

int main(int argc, char **argv) {
    QApplication game(argc,argv); //Création du programme

    //Ajout d'une police personnalisée pour le jeu
    QFontDatabase::addApplicationFont("../fonts/Joystick-5KjV.ttf"); //Ajout de la police
    QFont font = QFont("Joystick",50); //Création de la police
    QApplication::setFont(font); //Attribution de la police au programme

    //Ajout d'un splash au démarrage
    QSplashScreen* splash = new QSplashScreen(); //Création du splash
    splash->setWindowFlags(Qt::FramelessWindowHint); //Suppression des contours de la fenêtre
    QPixmap pixmap("../img/splash/splash.png");
    splash->setPixmap(pixmap); //Ajout d'un background au splash
    splash->resize(580,361); //Modification de la taille du splash
    splash->show(); //Affichage du splash

    //Création fenêtre principale
    Window window;

    QTimer::singleShot(2000,splash,SLOT(close())); //Au bout de 2 secondes le splash se ferme
    QTimer::singleShot(2000,&window,SLOT(show())); //Au bout de 2 secondes le programme s'ouvre

    return QApplication::exec();
}