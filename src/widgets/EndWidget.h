//
// Created by Remi on 20/04/2020.
//

#ifndef JEU_ENDWIDGET_H
#define JEU_ENDWIDGET_H


#include <QtWidgets/QWidget>

class EndWidget : public QWidget{

    Q_OBJECT

private:
    QPushButton* restartButton; //Bouton de redémarrage de la partie
    QPushButton* quitButton; //Bouton pour quitter le jeu
    QPushButton* menuButton; //Bouton de retour au menu
    std::string request;

public:
    //Constructeur
    EndWidget();

    //Getters
    std::string getRequest();

public slots:
    //Interactions
    void setRestart();
    void setEnd();
};


#endif //JEU_ENDWIDGET_H
