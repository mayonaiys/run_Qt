//
// Created by Remi on 09/04/2020.
//

#ifndef JEU_WINDOW_H
#define JEU_WINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "scenes/GameScene.h"
#include "scenes/SettingsScene.h"
#include "scenes/StartScene.h"
#include "widgets/PauseWidget.h"
#include "widgets/EndWidget.h"
#include "scenes/ScoresScene.h"
#include "scenes/levels/FirstLevel.h"
#include "widgets/ChoiceWidget.h"

class Window : public QMainWindow{

    Q_OBJECT

private:
    //Timer pour la boucle
    QTimer* timer;

    //Timer Jeu
    QLabel* timeLabel;

    //Scenes
    GameScene* gameScene;
    StartScene* startScene;
    SettingsScene* settingsScene;
    ScoresScene* scoresScene;
    Scene* globalScene;

    //Views
    QGraphicsView* mainView;
    //
    std::string status;

    //Widgets
    PauseWidget* pauseWidget;
    EndWidget* endWidget;
    ChoiceWidget* choiceWidget;

    bool isSceneLoaded;
    bool isWidgetLoaded;
    bool isChoiceDo;

public:
    Window();

    void loadSolo();
    void loadMulti();
    void loadSettings();
    void loadScores();
    void loadStart();
    void keyPressEvent(QKeyEvent* event);

public slots:
    void update();

};


#endif //JEU_WINDOW_H
