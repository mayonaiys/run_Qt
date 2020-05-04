//
// Created by Remi on 09/04/2020.
//

#ifndef JEU_SCENE_H
#define JEU_SCENE_H

#include <QtWidgets>
#include <QGraphicsScene>
#include "../utils.h"

class Scene : public QGraphicsScene{

    Q_OBJECT

protected: //Attributs privés
    QPixmap background; //Image de fond du jeu
    std::string status; //Status de la scène
    int h; //Hauteur de la scène
    int w; //Largeur de la scène

public: //Méthodes publiques
    void drawBackground(QPainter* painter, const QRectF& rect); //Dessin de l'image de fond

    //Getters & Setters
    void setBackground(QString);
    std::string getStatus();
    void setStatus(std::string status);
};


#endif //JEU_SCENE_H
