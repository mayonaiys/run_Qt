//
// Created by Remi on 09/04/2020.
//

#include "Scene.h"

using namespace std;

void Scene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    if(!this->background.isNull()){ //Si le fond n'est pas nul
        painter->drawPixmap(QRectF(0,0,this->w, this->h), this->background.scaled(this->w,this->h), sceneRect()); //On le dessine à la taille de la scène
    }
}

void Scene::setBackground(QString background) {
    this->background.load(background); //On charge l'image de fond
    this->setSceneRect(0, 0, this->w, this->h);
}

string Scene::getStatus() {
    return this->status;
}

void Scene::setStatus(string status){
    this->status = status;
}