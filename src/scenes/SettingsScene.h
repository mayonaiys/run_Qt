//
// Created by Remi on 19/04/2020.
//

#ifndef JEU_SETTINGSSCENE_H
#define JEU_SETTINGSSCENE_H

#include "Scene.h"
#include <fstream>

class SettingsScene : public Scene{

    Q_OBJECT

private:
    std::vector<Qt::Key> keys;
    std::vector<std::string> temp;

    //Joueur 1
    QPushButton* upButton;
    QPushButton* rightButton;
    QPushButton* leftButton;

    //Joueur 2
    QPushButton* upButton2;
    QPushButton* rightButton2;
    QPushButton* leftButton2;

    QPushButton* returnButton;

    QWidget* settingsWidget;

public:
    SettingsScene();
    void keyPressEvent(QKeyEvent* event);
    std::vector<Qt::Key> getKeys();
    std::string getStatus();
    void setStatus(std::string);
    void verification(std::string);
    bool isConfigComplete();
    void adjustSize(int,int);

public slots:
    void setRight();
    void setLeft();
    void setUp();
    void setUp2();
    void setLeft2();
    void setRight2();
    void setReturn();

};


#endif //JEU_SETTINGSSCENE_H
