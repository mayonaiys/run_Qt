//
// Created by Remi on 21/04/2020.
//

#ifndef JEU_CHOICEWIDGET_H
#define JEU_CHOICEWIDGET_H


#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <fstream>


class ChoiceWidget : public QWidget {

    Q_OBJECT

private:
    QString namePlayer1;
    QString namePlayer2;
    QPushButton* validPlayer1;
    QPushButton* validPlayer2;
    QLineEdit* inputPlayer1;
    QLineEdit* inputPlayer2;
    bool isPlayer1Valid;
    bool isPlayer2Valid;
    bool isLevelSet;
    int nbPlayers;

    //Boutons
    QPushButton* firstLevel;
    QPushButton* secondLevel;
    QPushButton* thirdLevel;

    std::string request;

    bool isChoiceDo;

public:
    //Constructeur
    ChoiceWidget(int);

    //Getters & setters
    bool getIsChoiceDo();
    void setIsChoiceDo();
    bool getIsPlayersValid();
    bool getIsLevelSet();
    QString getNamePlayer1();
    QString getNamePlayer2();
    std::string getRequest();

public slots:
    //Interactions
    void setPlayerOneValid();
    void setPlayerTwoValid();
    void setFirstLevel();
    void setSecondLevel();
    void setThirdLevel();
};


#endif //JEU_CHOICEWIDGET_H
