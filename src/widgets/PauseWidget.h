//
// Created by Remi on 20/04/2020.
//

#ifndef JEU_PAUSEWIDGET_H
#define JEU_PAUSEWIDGET_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>

class PauseWidget : public QWidget {

    Q_OBJECT

private:
    QPushButton* resumeButton;
    QPushButton* quitButton;
    QPushButton* menuButton;
    std::string request;
public:
    PauseWidget();
    std::string getRequest();

public slots:
    void setEnd();
    void setResume();
};


#endif //JEU_PAUSEWIDGET_H
