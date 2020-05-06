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
    //Gestion touches
    std::vector<Qt::Key> keys;
    std::vector<std::string> temp;

    //Boutons joueur 1
    QPushButton* upButton; //Bouton saut
    QPushButton* rightButton; //Bouton aller à droite
    QPushButton* leftButton; //Bouton aller à gauche

    //Boutons joueur 2
    QPushButton* upButton2; //Bouton saut
    QPushButton* rightButton2; //Bouton aller à droite
    QPushButton* leftButton2; //Bouton aller à gauche

    QPushButton* returnButton; //Bouton retour

    QWidget* settingsWidget;

public:
    SettingsScene(); //Constructeur
    ~SettingsScene(); //Destructeur

    void verification(std::string);
    bool isConfigComplete();

    //Getters & Setters
    std::vector<Qt::Key> getKeys();

    //Ajustement
    void adjustSize(int,int);

    //Interactions
    void keyPressEvent(QKeyEvent* event);
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
