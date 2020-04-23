#include <QApplication>
#include "Window.h"

int main(int argc, char **argv) {
    QApplication game(argc,argv);


    //Ajout police pesonnalisée
    //const QFont font("../MachineGunk-nyqg.ttf");
    QFontDatabase::addApplicationFont("../fonts/Joystick-5KjV.ttf");
    QFont font = QFont("Joystick",50);
    game.setFont(font);

    Window window;
    window.show();
    //

    return game.exec();
}
