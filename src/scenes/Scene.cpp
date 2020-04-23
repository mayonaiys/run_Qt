//
// Created by Remi on 09/04/2020.
//

#include "Scene.h"
#include <QGraphicsView>
#include <iostream>

using namespace std;

void Scene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

void Scene::setBackground(QString bc) {
    background.load(bc);
    this->setSceneRect(0,0,background.width(),background.height());
}

bool Scene::getIsLoaded() {
    return this->isLoaded;
}

void Scene::setIsLoaded(bool loaded) {
    this->isLoaded = loaded;
}
