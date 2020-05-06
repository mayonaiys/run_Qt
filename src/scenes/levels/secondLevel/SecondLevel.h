//
// Created by Remi on 22/04/2020.
//

#ifndef JEU_SECONDLEVEL_H
#define JEU_SECONDLEVEL_H

#include "../../GameScene.h"

class SecondLevel : public GameScene {

    Q_OBJECT

public:
    SecondLevel(std::vector<Qt::Key>,int,QString,QString = ""); //Constructeur
};


#endif //JEU_SECONDLEVEL_H
