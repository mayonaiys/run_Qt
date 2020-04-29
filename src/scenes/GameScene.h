//
// Created by Remi on 10/04/2020.
//

#ifndef JEU_GAMESCENE_H
#define JEU_GAMESCENE_H

#include "Scene.h"
#include "../objects/Obstacle.h"
#include "../objects/Floor.h"
#include "../objects/MovingFloor.h"
#include "../objects/MovingObstacle.h"
#include <QTimer>


class GameScene : public Scene{

    Q_OBJECT

private:
    QTimer* timer;
    std::string request; //End,Resume,Restart
    QTime gameTimer;
    std::vector<Qt::Key> keys;
    QTime durationP1;
    QTime durationP2;
    bool isWidgetLoaded;
    bool isTimerLaunched;

protected:
    Player* player;
    Player* player2;
    int nbPlayers;
    std::vector<Obstacle*> obstacles;
    std::vector<Floor*> floors;
    std::vector<MovingFloor*> movingFloors;
    std::vector<MovingObstacle*> movingObstacles;
    bool isTime1Set;
    bool isTime2Set;
    int xEnd;
    QLabel* labelNamePlayer;
    QLabel* labelNamePlayer2;
    std::string scoreFile;

    std::string id;

public:
    GameScene(std::vector<Qt::Key>,int,QString);
    //Actions clavier :
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    //Création niveau
    virtual void addObstacles();
    virtual void addFloor();

    //Getters&Setters
    std::string getStatus();
    void setRequest(std::string request);

    //
    void result();

    bool getIsWidgetLoaded();
    void setIsWidgetLoaded(bool);

    std::string getRequest();

    QString getTime();

    bool getIsTimerLaunched();

public slots:
    void update();

};


#endif //JEU_GAMESCENE_H
