//
// Created by Remi on 14/04/2020.
//

#include "Floor.h"

Floor::Floor(const QString& imgFileName) {
    this->setPixmap(QPixmap(imgFileName)); //Ajout de l'apparence du sol
}
