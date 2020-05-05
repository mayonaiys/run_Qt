//
// Created by Remi on 19/04/2020.
//

#include "SettingsScene.h"
#include <fstream>
#include <QKeyEvent>
#include <iostream>

using namespace std;

//Constructeur
SettingsScene::SettingsScene() {

    //StyleSheet
    QString style = "QPushButton { border-image:url(../img/buttons/button.png); color : #442A12; }"
                    "QPushButton:hover { border-image:url(../img/buttons/buttonHover.png); color : #543D2B }"
                    "QPushButton:pressed { border-image:url(../img/buttons/buttonOnClick.png); color : #2D2117}";

    //Boutons
    this->upButton = new QPushButton();
    this->upButton->setFixedSize(400,100);
    this->upButton->setStyleSheet(style);
    this->leftButton = new QPushButton();
    this->leftButton->setFixedSize(400,100);
    this->leftButton->setStyleSheet(style);
    this->rightButton = new QPushButton();
    this->rightButton->setFixedSize(400,100);
    this->rightButton->setStyleSheet(style);

    this->upButton2 = new QPushButton();
    this->upButton2->setFixedSize(400,100);
    this->upButton2->setStyleSheet(style);
    this->leftButton2 = new QPushButton();
    this->leftButton2->setFixedSize(400,100);
    this->leftButton2->setStyleSheet(style);
    this->rightButton2 = new QPushButton();
    this->rightButton2->setFixedSize(400,100);
    this->rightButton2->setStyleSheet(style);

    this->returnButton = new QPushButton("←");
    this->returnButton->setFixedSize(40,40);
    this->returnButton->setStyleSheet(style);
    this->returnButton->setAttribute(Qt::WA_NoSystemBackground);
    this->returnButton->move(10,10);


    //Labels
    QLabel* player1 = new QLabel("PLAYER 1");
    player1->setAttribute(Qt::WA_NoSystemBackground);
    player1->setAlignment(Qt::AlignHCenter);
    player1->setStyleSheet("color:#DB0000;");
    QLabel* player2 = new QLabel("PLAYER 2");
    player2->setAlignment(Qt::AlignHCenter);
    player2->setAttribute(Qt::WA_NoSystemBackground);
    player2->setStyleSheet("color:#0055FF;");

    //Connexion des boutons à leurs slots
    connect(this->upButton,SIGNAL(clicked()),this,SLOT(setUp()));
    connect(this->leftButton,SIGNAL(clicked()),this,SLOT(setLeft()));
    connect(this->rightButton,SIGNAL(clicked()),this,SLOT(setRight()));

    connect(this->upButton2,SIGNAL(clicked()),this,SLOT(setUp2()));
    connect(this->leftButton2,SIGNAL(clicked()),this,SLOT(setLeft2()));
    connect(this->rightButton2,SIGNAL(clicked()),this,SLOT(setRight2()));

    connect(this->returnButton,SIGNAL(clicked()),this,SLOT(setReturn()));

    //Création du widget des paramètres
    QVBoxLayout* vBoxPlayer1 = new QVBoxLayout();
    QWidget* parentPlayer1 = new QWidget();
    parentPlayer1->setAttribute(Qt::WA_NoSystemBackground);
    vBoxPlayer1->addWidget(player1);
    vBoxPlayer1->addWidget(this->upButton);
    vBoxPlayer1->addWidget(this->leftButton);
    vBoxPlayer1->addWidget(this->rightButton);
    parentPlayer1->setLayout(vBoxPlayer1);

    QVBoxLayout* vBoxPlayer2 = new QVBoxLayout();
    QWidget* parentPlayer2 = new QWidget();
    parentPlayer2->setAttribute(Qt::WA_NoSystemBackground);
    vBoxPlayer2->addWidget(player2);
    vBoxPlayer2->addWidget(this->upButton2);
    vBoxPlayer2->addWidget(this->leftButton2);
    vBoxPlayer2->addWidget(this->rightButton2);
    parentPlayer2->setLayout(vBoxPlayer2);

    QVBoxLayout* vBoxIndications = new QVBoxLayout();
    QWidget* parentIndications = new QWidget();
    parentIndications->setAttribute(Qt::WA_NoSystemBackground);
    QLabel* empty = new QLabel("");
    empty->setAttribute(Qt::WA_NoSystemBackground);
    vBoxIndications->addWidget(empty);
    QLabel* up = new QLabel("Jump");
    up->setAlignment(Qt::AlignTop);
    up->setAttribute(Qt::WA_NoSystemBackground);
    vBoxIndications->addWidget(up);
    QLabel* left = new QLabel("Run left");
    left->setAlignment(Qt::AlignTop);
    left->setAttribute(Qt::WA_NoSystemBackground);
    vBoxIndications->addWidget(left);
    QLabel* right = new QLabel("Run right");
    right->setAlignment(Qt::AlignTop);
    right->setAttribute(Qt::WA_NoSystemBackground);
    vBoxIndications->addWidget(right);
    parentIndications->setLayout(vBoxIndications);

    QHBoxLayout* hBox = new QHBoxLayout();
    this->settingsWidget = new QWidget();
    hBox->addWidget(parentIndications);
    hBox->addWidget(parentPlayer1);
    hBox->addWidget(parentPlayer2);
    this->settingsWidget->setLayout(hBox);
    this->settingsWidget->move(250,200);
    this->settingsWidget->setStyleSheet("background-color:rgba(0, 0, 0, 50);");

    this->addWidget(this->settingsWidget); //Ajout du widget de parametrage
    this->addWidget(this->returnButton); //Ajout du bouton de retour

    ifstream configFile("../config/config.txt"); //Ouverture du fichier de configuration des touches
    int i = 0;
    if(!configFile){
        ofstream file("../config/config.txt"); //On le crée et on ajoute les ids des touches par défaut
        file << "16777235" << endl;
        file << "16777234" << endl;
        file << "16777236" << endl;
        file << "90" << endl;
        file << "81" << endl;
        file << "68" << endl;
        string line;
    }
    ifstream File("../config/config.txt"); //Ouverture du fichier de configuration des touches
    string line;
    while(getline(File,line) && i<6){ //On le parcoure
        this->keys.push_back(Qt::Key(stoi(line))); //On ajoute au tableau de touches les touches enregistrées dans le fichier
        this->temp.push_back(line); //On ajoute au tableau temporaire les ids des touches enregistrées dans le fichier
        i++;
    }

    this->upButton->setText(QKeySequence(stoi(this->temp[0])).toString());
    this->leftButton->setText(QKeySequence(stoi(this->temp[1])).toString());
    this->rightButton->setText(QKeySequence(stoi(this->temp[2])).toString());

    this->upButton2->setText(QKeySequence(stoi(this->temp[3])).toString());
    this->leftButton2->setText(QKeySequence(stoi(this->temp[4])).toString());
    this->rightButton2->setText(QKeySequence(stoi(this->temp[5])).toString());

}

void SettingsScene::verification(string key){ //Vérifie si la touche est déjà enregistrée sur une autre touche, si oui, la remplace par une touche vide
    if(key == this->temp[0]){
        this->temp[0]="";
        this->upButton->setText("");
    } else if(key == this->temp[1]){
        this->temp[1]="";
        this->leftButton->setText("");
    } else if(key == this->temp[2]){
        this->temp[2]="";
        this->rightButton->setText("");
    } else if(key == this->temp[3]){
        this->temp[3]="";
        this->upButton2->setText("");
    } else if(key == temp[4]){
        this->temp[4]="";
        this->leftButton2->setText("");
    } else if(key == this->temp[5]){
        this->temp[5]="";
        this->rightButton2->setText("");
    }
}

bool SettingsScene::isConfigComplete() { //Vérifie si toute les touches sont bien paramétrées
    for(int i = 0; i < this->temp.size(); i++){
        if(this->temp[i]==""){ //Si une touche est vide
            return false;
        }
    }
    return true;
}

//Interactions
void SettingsScene::keyPressEvent(QKeyEvent *event) {
    if(this->status=="IsSettingUp"){ //Si on est en train de modifier la touche pour sauter
        if(event->key() != Qt::Key_Escape) { //Si on essaie pas de quitter
            verification(to_string(event->key())); //On vérifie que la touche entrée n'est pas déjà enregistrée pour une autre action
            this->temp[0] = to_string(event->key()); //On ajoute l'id' de la touche au tableau temporaire
            this->upButton->setText(QKeySequence(event->key()).toString()); //On donne le nom de la touche au bouton correspondant
            this->keys[0] = Qt::Key(event->key()); //On ajoute la touche au tableau de touches
        }
        this->status ="doNothing";
    } else if(this->status=="IsSettingLeft"){
        if(event->key() != Qt::Key_Escape) { //Si on essaie pas de quitter
            verification(to_string(event->key())); //On vérifie que la touche entrée n'est pas déjà enregistrée pour une autre action
            this->temp[1] = to_string(event->key()); //On ajoute l'id' de la touche au tableau temporaire
            this->leftButton->setText(QKeySequence(event->key()).toString()); //On donne le nom de la touche au bouton correspondant
            this->keys[1] = Qt::Key(event->key()); //On ajoute la touche au tableau de touches
        }
        this->status ="doNothing";
    } else if(this->status=="IsSettingRight"){
        if(event->key() != Qt::Key_Escape) { //Si on essaie pas de quitter
            verification(to_string(event->key())); //On vérifie que la touche entrée n'est pas déjà enregistrée pour une autre action
            this->temp[2] = to_string(event->key()); //On ajoute l'id' de la touche au tableau temporaire
            this->rightButton->setText(QKeySequence(event->key()).toString()); //On donne le nom de la touche au bouton correspondant
            this->keys[2] = Qt::Key(event->key()); //On ajoute la touche au tableau de touches
        }
        this->status ="doNothing";
    } else if(this->status=="IsSettingUp2"){
        if(event->key() != Qt::Key_Escape) { //Si on essaie pas de quitter
            verification(to_string(event->key())); //On vérifie que la touche entrée n'est pas déjà enregistrée pour une autre action
            this->temp[3] = to_string(event->key()); //On ajoute l'id' de la touche au tableau temporaire
            this->upButton2->setText(QKeySequence(event->key()).toString()); //On donne le nom de la touche au bouton correspondant
            this->keys[3] = Qt::Key(event->key()); //On ajoute la touche au tableau de touches
        }
        this->status ="doNothing";
    } else if(this->status=="IsSettingLeft2"){
        if(event->key() != Qt::Key_Escape) { //Si on essaie pas de quitter
            verification(to_string(event->key())); //On vérifie que la touche entrée n'est pas déjà enregistrée pour une autre action
            this->temp[4] = to_string(event->key()); //On ajoute l'id' de la touche au tableau temporaire
            this->leftButton2->setText(QKeySequence(event->key()).toString()); //On donne le nom de la touche au bouton correspondant
            this->keys[4] = Qt::Key(event->key()); //On ajoute la touche au tableau de touches
        }
        this->status ="doNothing";
    } else if(this->status=="IsSettingRight2"){
        if(event->key() != Qt::Key_Escape){ //Si on essaie pas de quitter
            verification(to_string(event->key())); //On vérifie que la touche entrée n'est pas déjà enregistrée pour une autre action
            this->temp[5]=to_string(event->key()); //On ajoute l'id' de la touche au tableau temporaire
            this->rightButton2->setText(QKeySequence(event->key()).toString()); //On donne le nom de la touche au bouton correspondant
            this->keys[5]=Qt::Key(event->key()); //On ajoute la touche au tableau de touches
        }
        this->status ="doNothing";
    }
    if(event->key()==Qt::Key_Escape){ //Si on essaie de quitter
        this->setReturn();  //On quitte la scene
    }
}

void SettingsScene::setUp() {
    this->status = "IsSettingUp";
}

void SettingsScene::setLeft() {
    this->status = "IsSettingLeft";
}

void SettingsScene::setRight() {
    this->status = "IsSettingRight";
}

void SettingsScene::setUp2() {
    this->status = "IsSettingUp2";
}

void SettingsScene::setLeft2() {
    this->status = "IsSettingLeft2";
}

void SettingsScene::setRight2() {
    this->status = "IsSettingRight2";
}

void SettingsScene::setReturn() {
    if(isConfigComplete()){ //Si toute les touches ont étés bien paramétrées
        remove("../config/config.txt"); //On supprime le fichier de configuration
        ofstream file("../config/config.txt"); //On le recrée
        for(int i = 0; i < 6; i++){
            file << temp[i] << endl; //Ajout des ids des touches au fichier
        }
        this->status="Ended"; //Modification du status pour revenir au menu
    }
}

vector<Qt::Key> SettingsScene::getKeys() {
    return this->keys;
}


//Ajustement
void SettingsScene::adjustSize(int width, int height) {
    //Initialisation de la taille de la scène en fonction de la taille de la fenêtre
    this->w = width-5;
    this->h = height-5;
    this->setBackground("../img/backgrounds/settingsBackground.png"); //Application du fond d'écran en fonction de la nouvelle taille de fenêtre
    this->settingsWidget->move(width/2 - this->settingsWidget->width()/2,height/2 - this->settingsWidget->height()/2); //Modification de la position du widget des paramètres en fonction de la taille de la fenêtre
}

SettingsScene::~SettingsScene() {
    delete this->upButton; //Bouton saut
    delete this->rightButton; //Bouton aller à droite
    delete this->leftButton; //Bouton aller à gauche
    delete this->upButton2; //Bouton saut
    delete this->rightButton2; //Bouton aller à droite
    delete this->leftButton2; //Bouton aller à gauche
    delete this->returnButton; //Bouton retour
    delete this->settingsWidget;
}
