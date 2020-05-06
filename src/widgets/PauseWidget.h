//
// Created by Remi on 20/04/2020.
//

#ifndef JEU_PAUSEWIDGET_H
#define JEU_PAUSEWIDGET_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>

class PauseWidget : public QWidget {

    Q_OBJECT

private:
    QPushButton* resumeButton; //Bouton de retour en jeu
    QPushButton* quitButton; //Bouton de fermeture du programme
    QPushButton* menuButton; //Bouton de retour au menu
    std::string request;
public:
    PauseWidget(); //Constructeur
    ~PauseWidget(); //Destructeur

    //Getters
    std::string getRequest();

public slots:
    //Interactions
    void setEnd();
    void setResume();
};


#endif //JEU_PAUSEWIDGET_H
