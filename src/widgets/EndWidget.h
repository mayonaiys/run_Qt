//
// Created by Remi on 20/04/2020.
//

#ifndef JEU_ENDWIDGET_H
#define JEU_ENDWIDGET_H


#include <QtWidgets/QWidget>

class EndWidget : public QWidget{

    Q_OBJECT

private:
    QPushButton* restartButton;
    QPushButton* quitButton;
    QPushButton* menuButton;
    std::string request;

public:
    EndWidget();
    std::string getRequest();

public slots:
    void setRestart();
    void setEnd();
};


#endif //JEU_ENDWIDGET_H
