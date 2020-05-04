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
#include "../utils.h"
#include <QTimer>


class GameScene : public Scene{

    Q_OBJECT

private:
    QTimer* timer; //Timer pour la boucle update
    std::string request; /*End,Resume,Restart*/
    QTime gameTimer; //Timer de la partie
    std::vector<Qt::Key> keys; //Touches parametrées pour contrôler le(s) joueur(s)
    QTime durationP1; //Temps mit par le premier joueur
    QTime durationP2; //Temp mit par le second joueur
    bool isWidgetLoaded; //
    bool isTimerLaunched; //
    bool isTime1Set; //
    bool isTime2Set; //
    int nbPlayers; //Nombre de joueurs dans la partie (1 ou 2)
protected:
    Player* player; //Premier joueur
    Player* player2; //Second joueur
    std::vector<Obstacle*> obstacles; //Obstacles de la partie
    std::vector<Floor*> floors; //Sols de la partie
    std::vector<MovingFloor*> movingFloors; //Sols mouvants de la partie
    std::vector<MovingObstacle*> movingObstacles; //Obstacles mouvants de la partie
    int xEnd; //Position de fin de partie
    QLabel* labelNamePlayer; //Label contenant le nom du premier joueur
    QLabel* labelNamePlayer2; //Label contenant le nom du second joueur
    std::string path; //Chemin pour les textures
    std::string id; //Id du niveau

public:
    //Constructeur
    GameScene(std::vector<Qt::Key>,int,QString);

    //Actions clavier :
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    //Création niveau
    void addObstacles();
    void addFloors();

    //Getters&Setters
    std::string getStatus();
    void setRequest(std::string request);
    bool getIsWidgetLoaded();
    void setIsWidgetLoaded(bool);
    bool getIsTimerLaunched();
    std::string getRequest();
    QString getTime();

    //Fin de partie
    void result();

public slots:
    void update();
};


#endif //JEU_GAMESCENE_H
