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
    StartScene(); //Constructeur
    ~StartScene(); //Desctructeur

    void disableButtons();
    void enableButtons();

    //Ajustement
    void adjustSize(int,int);

    //Getters & setters
    void setRequest(std::string);
    std::string getRequest();
public slots:
    //Interactions
    void setSolo();
    void setMulti();
    void setSettings();
    void setScores();
};


#endif //JEU_STARTSCENE_H
