//
// Created by Remi on 20/04/2020.
//

#ifndef JEU_SCORESSCENE_H
#define JEU_SCORESSCENE_H
#include "Scene.h"
#include "../utils.h"

class ScoresScene : public Scene{

    Q_OBJECT

private:
    //Style
    QString style;

    //Boutons
    QPushButton* returnButton; //Boutons de retour au menu start
    QPushButton* nextButton; //Boutons pour passer à la liste d'après
    QPushButton* previousButton; //Boutons pour passer à la liste d'avant
    QWidget* buttonPanel; //Pannel de boutons

    //Liste
    QWidget* currentList; //Liste actuellement à l'écran
    int currentScoreList; //Numéro de la liste actuelle
    bool isListLoaded;

public:
    ScoresScene(); //Constructeur
    ~ScoresScene();

    //Gestion Liste de score
    QVBoxLayout* createList(const std::string&);
    void displayScore();

    //Ajustement
    void adjustSize(int,int);

    //Interactions
    void keyPressEvent(QKeyEvent*); //Detection des touches appuyées
public slots:
    void setReturn();
    void right();
    void left();
};


#endif //JEU_SCORESSCENE_H
