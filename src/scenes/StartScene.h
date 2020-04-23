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
    QPushButton* soloButton;
    QPushButton* multiButton;
    QPushButton* settingsButton;
    QPushButton* scoresButton;

    //
    std::string request;

public:
    StartScene();
    std::string getRequest();
    void disableButtons();

public slots:
    void setSolo();
    void setMulti();
    void setSettings();
    void setScores();
};


#endif //JEU_STARTSCENE_H
