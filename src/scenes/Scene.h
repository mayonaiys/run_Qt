//
// Created by Remi on 09/04/2020.
//

#ifndef JEU_SCENE_H
#define JEU_SCENE_H

#include <QtWidgets>
#include <QGraphicsScene>
#include "../objects/Player.h"

class Scene : public QGraphicsScene{

    Q_OBJECT

protected: //Attributs privés
    //Image de fond du jeu
    QPixmap background;
    std::string status;
    bool isLoaded;

public: //Méthodes publiques
    void drawBackground(QPainter* painter, const QRectF& rect);
    void setBackground(QString);
    bool getIsLoaded();
    void setIsLoaded(bool);
};


#endif //JEU_SCENE_H
