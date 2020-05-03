//
// Created by Remi on 09/04/2020.
//

#include "Scene.h"
#include <QGraphicsView>
#include <iostream>

using namespace std;

void Scene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    if(!this->background.isNull()){
        painter->drawPixmap(QRectF(0,0,this->w, this->h), background.scaled(this->w,this->h), sceneRect());
    }
}

void Scene::setBackground(QString bc) {
    background.load(bc);
    this->setSceneRect(0, 0, this->w, this->h);
}