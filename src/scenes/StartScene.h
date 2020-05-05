//
// Created by Remi on 19/04/2020.
//

#ifndef JEU_STARTSCENE_H
#define JEU_STARTSCENE_H


#include "Scene.h"

class StartScene : public Scene{

    Q_OBJECT

private:
    //Boutons
    QPushButton* soloButton; //Bouton pour acceder au jeu en solo
    QPushButton* multiButton; //Bonton pour accéder au jeu en multijoueur
    QPushButton* settingsButton; //Bouton pour accéder aux paramètres
    QPushButton* scoresButton; //Bouton pour accéder aux scores

    //
    std::string request;

    QWidget* menu; //Pannel des boutons

public:
    StartScene();
    std::string getRequest();
    void disableButtons();

    //Ajustement
    void adjustSize(int,int);

    void setRequest(std::string);
public slots:
    //Interactions
    void setSolo();
    void setMulti();
    void setSettings();
    void setScores();

    void enableButtons();
};


#endif //JEU_STARTSCENE_H
