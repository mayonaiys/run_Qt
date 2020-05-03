//
// Created by Remi on 03/05/2020.
//

#ifndef JEU_THIRDLEVEL_H
#define JEU_THIRDLEVEL_H


#include "../GameScene.h"

class ThirdLevel : public GameScene{

    Q_OBJECT

public:
    ThirdLevel(std::vector<Qt::Key>,int,QString,QString = "");
    void addObstacles();
    void addFloor();

};


#endif //JEU_THIRDLEVEL_H
