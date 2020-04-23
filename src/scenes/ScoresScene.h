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

    std::vector<std::vector<std::string> > temp1;
    std::vector<std::vector<std::string> > temp2;
    std::vector<std::vector<std::string> > temp3;

    QHBoxLayout* list1;
    QHBoxLayout* list2;
    QHBoxLayout* list3;

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

    std::vector<std::string> cutString(std::string);

    void sort(std::vector<std::vector<std::string> > & );
    void reWrite(const char *, std::vector<std::vector<std::string> >);

    QLabel* createLabel(QString);
    QHBoxLayout* createList(std::string);

    std::vector<std::vector<std::string> > createTemp(std::string);

public slots:
    void setReturn();
    void right();
    void left();
    void update();
};


#endif //JEU_SCORESSCENE_H
