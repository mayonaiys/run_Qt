//
// Created by Remi on 21/04/2020.
//

#include "ChoiceWidget.h"

ChoiceWidget::ChoiceWidget(int nbPlayers){
    //Style des boutons de validation
    QString style = "QPushButton { border-image:url(../img/buttons/button.png); color : #442A12; }"
                    "QPushButton:hover { border-image:url(../img/buttons/buttonHover.png); color : #543D2B }"
                    "QPushButton:pressed { border-image:url(../img/buttons/buttonOnClick.png); color : #2D2117}";

    this->nbPlayers = nbPlayers; //Initialisation du nombre de joueurs

    //Création interface joueur 1
    QVBoxLayout* vBox1 = new QVBoxLayout(); //Boite contenant la zone de texte et le bouton de validation pour le premier joueur
    this->inputPlayer1 = new QLineEdit("Player1"); //Création d'une zone de texte pour le nom du premier joueur (initialement "player1")
    this->validPlayer1 = new QPushButton("Valid");
    this->validPlayer1->setStyleSheet(style); //Application du style
    vBox1->addWidget(inputPlayer1);
    vBox1->addWidget(validPlayer1);
    this->isPlayer1Valid = false;

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addLayout(vBox1);

    int buttonSize = 120; //Taille des boutons de choix de niveau
    if(this->nbPlayers == 2){
        //Création interface joueur 2
        QVBoxLayout* vBox2 = new QVBoxLayout(); //Boite contenant la zone de texte et le bouton de validation pour le second joueur
        this->inputPlayer2 = new QLineEdit("Player2"); //Création d'une zone de texte pour le nom du premier joueur (initialement "player2")
        this->validPlayer2 = new QPushButton("Valid"); //Création du bouton de validation pour le secon joueur
        this->validPlayer2->setStyleSheet(style); //Application du style
        vBox2->addWidget(inputPlayer2);
        vBox2->addWidget(validPlayer2);
        hBox->addLayout(vBox2);
        connect(this->validPlayer2,SIGNAL(clicked()),this,SLOT(setPlayerTwoValid())); //Connexion du bouton de validation à son slot
        this->isPlayer2Valid = false;

        buttonSize = 225; //Changement de la taille pour s'adapter à l'interface avec deux joueurs
    }

    //Création boutons de choix du niveau
    this->firstLevel = new QPushButton(); //Création du bouton du premier niveau
    this->firstLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel1.png); }" //Application du style
                                    "QPushButton:hover { border-image:url(../img/buttons/iconLevel1Hover.png); }"
                                    "QPushButton:pressed { border-image:url(../img/buttons/iconLevel1Pressed.png); }");

    this->secondLevel = new QPushButton(); //Création du bouton du second niveau
    this->secondLevel->setEnabled(false); //Désactivation du bouton
    this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevelBlocked.png); }"); //Application du style (bouton bloqué)

    this->thirdLevel = new QPushButton(); //Création du bouton du troisième niveau
    this->thirdLevel->setEnabled(false); //Désactivation du bouton
    this->thirdLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevelBlocked.png); }"); //Application du style (bouton bloqué)

    //Gestion taille des boutons de choix du niveau
    this->firstLevel->setFixedHeight(buttonSize);
    this->secondLevel->setFixedHeight(buttonSize);
    this->thirdLevel->setFixedHeight(buttonSize);

    QHBoxLayout* hBoxLevels = new QHBoxLayout();
    hBoxLevels->addWidget(this->firstLevel);
    hBoxLevels->addWidget(this->secondLevel);
    hBoxLevels->addWidget(this->thirdLevel);

    QWidget* parentHBox = new QWidget(); //Widget qui va contenir le nom et le bouton de validation pour chaque joueur
    parentHBox->setLayout(hBox);
    parentHBox->setAttribute(Qt::WA_NoSystemBackground); //Suppression du fond

    QWidget* parentHBoxLevels = new QWidget(); //Widget qui va contenir les boutons de choix du niveau
    parentHBoxLevels->setLayout(hBoxLevels);
    parentHBoxLevels->setAttribute(Qt::WA_NoSystemBackground); //Suppresion du fond

    QVBoxLayout* vBoxGlobal = new QVBoxLayout(); //Layout qui va contenir toute l'interface (les 2 widgets précédents)
    vBoxGlobal->addWidget(parentHBox);
    vBoxGlobal->addWidget(parentHBoxLevels);

    this->setLayout(vBoxGlobal); //Ajout du layout à ce widget (choice widget)
    this->setStyleSheet("background-color:rgba(0, 0, 0, 50);"); //Aplication d'un style à ce widget (choice widget)

    //Lecture du fichier
    std::ifstream levelFile("../src/scenes/levels/levels.txt"); //Ouverture du fichier contenant un id permettant de savoir quels niveaux sont débloqués
    if(levelFile){ //Si le fichier existe et est ouvert
        std::string line;
        while(getline(levelFile,line)){
            if(line=="kj3c7_DahY"){ //Si la ligne du fichier correspond à cet id
                this->secondLevel->setEnabled(true); //Activation du bouton du niveau 2
                this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel2.png); }" //Application du style
                                                 "QPushButton:hover { border-image:url(../img/buttons/iconLevel2Hover.png); }"
                                                 "QPushButton:pressed { border-image:url(../img/buttons/iconLevel2Pressed.png); }");
            } else if(line=="b74r8_aLAnZ"){ //Si la ligne du fichier correspond à cet id
                this->secondLevel->setEnabled(true); //Activation du bouton du niveau 3
                this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel2.png); }" //Application du style
                                                 "QPushButton:hover { border-image:url(../img/buttons/iconLevel2Hover.png); }"
                                                 "QPushButton:pressed { border-image:url(../img/buttons/iconLevel2Pressed.png); }");
                this->thirdLevel->setEnabled(true);
                this->thirdLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel3.png); }" //Application du style
                                                "QPushButton:hover { border-image:url(../img/buttons/iconLevel3Hover.png); }"
                                                "QPushButton:pressed { border-image:url(../img/buttons/iconLevel3Pressed.png); }");
            }
        }
    } else { //Sinon
        std::ofstream file("../src/scenes/levels/levels.txt"); //Création du fichier
        file << "zK7k9_vYmN"; //Ajout d'un id ne permettant que le débloquage du premier niveau
    }

    //Connexion des boutons à leurs slots
    connect(this->firstLevel,SIGNAL(clicked()),this,SLOT(setFirstLevel()));
    connect(this->secondLevel,SIGNAL(clicked()),this,SLOT(setSecondLevel()));
    connect(this->thirdLevel,SIGNAL(clicked()),this,SLOT(setThirdLevel()));
    connect(this->validPlayer1,SIGNAL(clicked()),this,SLOT(setPlayerOneValid()));

    this->isLevelSet = false; //Le niveau n'est pas encore choisi
    this->isChoiceDo = false; //Aucun choix n'est fait
}

//Getters
bool ChoiceWidget::getIsPlayersValid() {
    if(this->nbPlayers==1){ //Si un seul joueur
        return this->isPlayer1Valid; //On renvoie si le joueur a validé son choix de nom et de niveau
    } else if(this->nbPlayers==2){ //Si deux joueurs
        return this->isPlayer1Valid && this->isPlayer2Valid; //On revnoie s'ils ont validé le choix de leur nom et du niveau
    }
}

QString ChoiceWidget::getNamePlayer1() {
    return this->namePlayer1;
}

QString ChoiceWidget::getNamePlayer2() {
    return this->namePlayer2;
}

std::string ChoiceWidget::getRequest() {
    return this->request;
}

bool ChoiceWidget::getIsLevelSet() {
    return this->isLevelSet;
}

bool ChoiceWidget::getIsChoiceDo() {
    return this->isChoiceDo;
}

void ChoiceWidget::setIsChoiceDo() {
    this->isChoiceDo = true;
}


//Interactions
void ChoiceWidget::setFirstLevel() {
    this->firstLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel1Validate.png); }"); //Application du style du bouton validé

    if(this->secondLevel->isEnabled()) { //Si le second niveau est débloqué, au cas ou il était précédement choisi pour la partie
        this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel2.png); }" //Application du style initial
                                         "QPushButton:hover { border-image:url(../img/buttons/iconLevel2Hover.png); }"
                                         "QPushButton:pressed { border-image:url(../img/buttons/iconLevel2Pressed.png); }");
    }

    if(this->thirdLevel->isEnabled()) { //Si le 3eme niveau est débloqué, au cas ou il était précédement choisi pour la partie
        this->thirdLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel3.png); }" //Application du style initial
                                        "QPushButton:hover { border-image:url(../img/buttons/iconLevel3Hover.png); }"
                                        "QPushButton:pressed { border-image:url(../img/buttons/iconLevel3Pressed.png); }");
    }

    this->request = "FirstLevel"; //On envoie une requête pour jouer sur le premier niveau
    this->isLevelSet = true; //Indique que le choix du niveau est fait
}

void ChoiceWidget::setSecondLevel() {
    this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel2Validate.png); }"); //Application du style du bouton validé

    this->firstLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel1.png); }"
                                     "QPushButton:hover { border-image:url(../img/buttons/iconLevel1Hover.png); }"
                                     "QPushButton:pressed { border-image:url(../img/buttons/iconLevel1Pressed.png); }");

    if(this->thirdLevel->isEnabled()) { //Si le 3eme niveau est débloqué, au cas ou il était précédement choisi pour la partie
        this->thirdLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel3.png); }" //Application du style initial
                                        "QPushButton:hover { border-image:url(../img/buttons/iconLevel3Hover.png); }"
                                        "QPushButton:pressed { border-image:url(../img/buttons/iconLevel3Pressed.png); }");
    }

    this->request = "SecondLevel"; //On envoie une requête pour jouer sur le second niveau
    this->isLevelSet = true; //Indique que le choix du niveau est fait
}

void ChoiceWidget::setThirdLevel() {
    this->thirdLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel3Validate.png); }"); //Application du style du bouton validé

    this->firstLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel1.png); }"
                                    "QPushButton:hover { border-image:url(../img/buttons/iconLevel1Hover.png); }"
                                    "QPushButton:pressed { border-image:url(../img/buttons/iconLevel1Pressed.png); }");

    if(this->secondLevel->isEnabled()) { //Si le second niveau est débloqué, au cas ou il était précédement choisi pour la partie
        this->secondLevel->setStyleSheet("QPushButton { border-image:url(../img/buttons/iconLevel2.png); }" //Application du style initial
                                         "QPushButton:hover { border-image:url(../img/buttons/iconLevel2Hover.png); }"
                                         "QPushButton:pressed { border-image:url(../img/buttons/iconLevel2Pressed.png); }");
    }

    this->request = "ThirdLevel"; //On envoie une requête pour jouer sur le troisième niveau
    this->isLevelSet = true; //Indique que le choix du niveau est fait
}

void ChoiceWidget::setPlayerOneValid() {
    this->namePlayer1 = this->inputPlayer1->text(); //Initialise le pseudo du joueur
    this->isPlayer1Valid = true; //Indique que le joueur a validé son choix
}

void ChoiceWidget::setPlayerTwoValid() {
    this->namePlayer2 = this->inputPlayer2->text(); //Initialise le pseudo du joueur
    this->isPlayer2Valid = true; //Indique que le joueur a validé son choix
}
