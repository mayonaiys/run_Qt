//
// Created by Remi on 14/04/2020.
//

#include "Floor.h"

Floor::Floor(QString imgFileName) {
    this->setPixmap(QPixmap(imgFileName)); //Skin du sol
}
