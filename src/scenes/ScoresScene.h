//
// Created by Remi on 20/04/2020.
//

#ifndef JEU_SCORESSCENE_H
#define JEU_SCORESSCENE_H
#include "Scene.h"

class ScoresScene : public Scene{

    Q_OBJECT

private:
    QString style;

    QVBoxLayout* list1;
    QVBoxLayout* list2;
    QVBoxLayout* list3;

    QPushButton* returnButton;

    QPushButton* rightButton;
    QPushButton* leftButton;

    QWidget* currentList;
    QWidget* buttonPanel;

    int currentScoreList;
    bool isListLoaded;

public:
    ScoresScene();
    std::string getStatus();
    void setStatus(std::string status);

    void keyPressEvent(QKeyEvent*);

    void reWrite(const char *, std::vector<std::vector<std::string> >);

    QLabel* createLabel(QString);
    QVBoxLayout* createList(std::string);

    void adjustSize(int,int);

public slots:
    void setReturn();
    void right();
    void left();
    void update();
};


#endif //JEU_SCORESSCENE_H
