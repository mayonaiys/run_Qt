//
// Created by Remi on 17/04/2020.
//

#ifndef JEU_FIRSTLEVEL_H
#define JEU_FIRSTLEVEL_H


#include "../../GameScene.h"
#include "../../../utils.h"

class FirstLevel : public GameScene{

    Q_OBJECT

public:
    FirstLevel(std::vector<Qt::Key>,int,QString,QString = ""); //Constructeur

};


#endif //JEU_FIRSTLEVEL_H
