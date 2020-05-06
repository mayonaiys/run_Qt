//
// Created by Remi on 20/04/2020.
//

#include "ScoresScene.h"

using namespace std;

//Constructeur
ScoresScene::ScoresScene(){
    //Style pour les boutons
    this->style = "QPushButton { border-image:url(../img/buttons/button.png); color : #442A12; }"
                    "QPushButton:hover { border-image:url(../img/buttons/buttonHover.png); color : #543D2B }"
                    "QPushButton:pressed { border-image:url(../img/buttons/buttonOnClick.png); color : #2D2117}";

    //Ajout bouton retour
    this->returnButton = new QPushButton("←"); //Création bouton
    this->returnButton->setFixedSize(40,40);
    this->returnButton->setStyleSheet(style); //Application du style
    this->returnButton->setAttribute(Qt::WA_NoSystemBackground);
    this->returnButton->move(10,10);
    this->addWidget(returnButton);

    //Création du panel de boutons précédent/suivant
    this->nextButton = new QPushButton("Next"); //Création bouton
    this->previousButton = new QPushButton("Previous"); //Création bouton
    this->nextButton->setStyleSheet(style); //Application du style
    this->previousButton->setStyleSheet(style); //Application du style

    QHBoxLayout* hButtonsBox = new QHBoxLayout(); //Création d'un layout vertical
    hButtonsBox->addWidget(this->previousButton); //Ajout du bouton au layout
    hButtonsBox->addWidget(this->nextButton); //Ajout du bouton au layout

    this->buttonPanel = new QWidget();//Création du pannel
    this->buttonPanel->setLayout(hButtonsBox); //Ajout du layout au pannel
    this->buttonPanel->setAttribute(Qt::WA_NoBackground);
    this->addWidget(this->buttonPanel); //Ajout du pannel à la scène

    //Connexion des boutons à leur slot
    connect(returnButton,SIGNAL(clicked()),this,SLOT(setReturn()));
    connect(nextButton,SIGNAL(clicked()),this,SLOT(right()));
    connect(previousButton,SIGNAL(clicked()),this,SLOT(left()));

    //Gestion liste de score
    this->currentScoreList = 1; //On affichera la liste du niveau 1 en premier
    this->isListLoaded = false; //Aucune liste n'est chargée
    this->displayScore(); //Affichage de la liste du score du niveau 1

}

//Destructeur
ScoresScene::~ScoresScene() {
    delete this->returnButton; //Boutons de retour au menu start
    delete this->nextButton; //Boutons pour passer à la liste d'après
    delete this->previousButton; //Boutons pour passer à la liste d'avant
    delete this->buttonPanel; //Pannel de boutons
}


//Gestion liste
QVBoxLayout* ScoresScene::createList(const string& scoreFile) { //Création de la liste

    //Affichage
    QVBoxLayout* vBoxRanking = new QVBoxLayout();
    QVBoxLayout* vBoxName = new QVBoxLayout();
    QVBoxLayout* vBoxTime = new QVBoxLayout();

    QLabel* ranking = createLabel("Ranking");
    ranking->setStyleSheet("color:#CECECE;");
    QLabel* name = createLabel("Name");
    name->setStyleSheet("color:#CECECE;");
    QLabel* time = createLabel("Time (mm:ss:ms)");
    time->setStyleSheet("color:#CECECE;");

    vBoxRanking->addWidget(ranking); //Ajout d'une colonne rang
    vBoxName->addWidget(name); //Ajout d'une colonne nom du joueur
    vBoxTime->addWidget(time); //Ajout d'une colonne temps mit par le joueur

    string color;

    vector<vector<string> > temp = createTemp(scoreFile,2); //Création d'un tableau contenant le nom et le temps des joueurs
                                                                            //Chaque chaîne de caractère contient le nom + le temps qu'il a mit à finir le niveau ou s'il est mort
    sort(temp); //Tri du tableau dans l'ordre croissant en fonction du temps
    reWrite(scoreFile.c_str(),temp); //Réécriture du fichier de score en ordre croissant
    for(int i = 0; i < 10; i++){
        QLabel* part1 = createLabel((to_string(i+1) + "-").c_str());
        QLabel* part2;
        QLabel* part3;
        if(i < temp.size()){
            part2 = createLabel((temp[i][0]).c_str());
            part3 = createLabel((temp[i][1]).c_str());
        } else {
            part2 = createLabel(QString(""));
            part3 = createLabel(QString(""));
        }
        //Ajout aux colonnes du rang, du nom et du temps
        vBoxRanking->addWidget(part1);
        vBoxName->addWidget(part2);
        vBoxTime->addWidget(part3);
        if(i==0){ //Pour les 3 premiers, une couleur différente des autres est attribuée
            color = "#46EA00";
        } else if(i==1){
            color = "#F2A900";
        } else if(i==2){
            color = "#EF0700";
        } else {
            color = "#AFAFAF";
        }
        QString labelStyle = ("color:" + color + ";").c_str();
        part1->setStyleSheet(labelStyle);
        part2->setStyleSheet(labelStyle);
        part3->setStyleSheet(labelStyle);
    }

    QWidget* parentRanking = new QWidget();
    parentRanking->setLayout(vBoxRanking);
    parentRanking->setAttribute(Qt::WA_NoSystemBackground);
    QWidget* parentName = new QWidget();
    parentName->setLayout(vBoxName);
    parentName->setAttribute(Qt::WA_NoSystemBackground);
    QWidget* parentTime = new QWidget();
    parentTime->setLayout(vBoxTime);
    parentTime->setAttribute(Qt::WA_NoSystemBackground);

    QLabel* level = createLabel(("Level " + to_string(this->currentScoreList)).c_str()); //Création d'un label du nom du niveau
    level->setStyleSheet("color:#CECECE;");

    QVBoxLayout* globalVBox = new QVBoxLayout();

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(parentRanking);
    hBox->addWidget(parentName);
    hBox->addWidget(parentTime);

    globalVBox->addWidget(level);
    globalVBox->addLayout(hBox);

    return globalVBox;
}

void ScoresScene::displayScore() {
    if(!this->isListLoaded){
        QVBoxLayout* list;
        if(this->currentScoreList==1){
            this->previousButton->setEnabled(false); //Désactivation du bouton pour aller sur la liste précédente (car impossible)
            this->previousButton->setStyleSheet("border-image:url(../img/buttons/buttonHover.png);"); //Modification de l'apparence du bouton
            list = createList("../src/scenes/levels/firstLevel/scores.txt"); //Création d'une liste en fonction du score du niveau 1
        } else if(this->currentScoreList==2){
            this->nextButton->setEnabled(true); //Activation du bouton pour aller sur la liste précédente
            this->nextButton->setStyleSheet(this->style); //Modification de l'apparence du bouton
            this->previousButton->setEnabled(true); //Activation du bouton pour aller sur la liste suivante
            this->previousButton->setStyleSheet(this->style); //Modification de l'apparence du bouton
            list = createList("../src/scenes/levels/secondLevel/scores.txt"); //Création d'une liste en fonction du score du niveau2
        } else if(this->currentScoreList==3){
            this->nextButton->setEnabled(false); //Désactivation du bouton pour aller sur la liste suivante (car impossible)
            this->nextButton->setStyleSheet("border-image:url(../img/buttons/buttonHover.png);"); //Modification de l'apparence du bouton
            list = createList("../src/scenes/levels/thirdLevel/scores.txt"); //Création d'une liste en fonction du score du niveau 3
        }
        this->currentList = new QWidget();
        this->currentList->setLayout(list);
        this->addWidget(currentList); //Ajout de la liste à la scène
        this->buttonPanel->setFixedWidth(this->currentList->width());  //Modification de la  taille du pannel de boutons en fonction de la liste
        this->currentList->setStyleSheet("background-color:rgba(0, 0, 0, 50);"); //Modification de l'apparence de la liste
        this->currentList->move((this->width())/2 - (this->currentList->width())/2,30); //Déplacement de la liste
        this->buttonPanel->move((this->width())/2 - (this->currentList->width())/2,this->currentList->pos().y()+this->currentList->height() + 10); //Déplacement du pannel de boutons en fonction de la liste

        this->isListLoaded = true; //La liste est chargée
    }
}

//Interactions
void ScoresScene::right() {
    this->currentScoreList++; //Augmentation du numero de liste
    delete this->currentList; //Suppression de la liste actuellement affichée
    this->isListLoaded = false; //La liste est déchargée
    this->displayScore(); //Affichage de la liste de score
}

void ScoresScene::left() {
    this->currentScoreList--; //Diminution du numero de liste
    delete this->currentList; //Suppression de la liste actuellement affichée
    this->isListLoaded = false; //La liste est déchargée
    this->displayScore(); //Affichage de la liste de score
}

void ScoresScene::keyPressEvent(QKeyEvent* event) {
    if(event->key() == Qt::Key_Escape){ //Si la touche appuyée est la touche echap
        this->status = "Ended"; //Modification du status
    }
}

void ScoresScene::setReturn() {
    this->status = "Ended"; //Modification du status
}

//Ajustement fenêtre
void ScoresScene::adjustSize(int width, int height) {
    //Initialisation de la taille de la scène en fonction de la taille de la fenêtre
    this->w = width-5;
    this->h = height-5;
    this->setBackground("../img/backgrounds/settingsBackground.png"); //Application du fond d'écran en fonction de la nouvelle taille de fenêtre
    if(this->isListLoaded){ //Si la liste est chargée alors on modifie sa taille/position et celle du pannel de boutons en fonction de la taille d'écran
        this->currentList->move((this->width())/2 - (this->currentList->width())/2,30);
        this->buttonPanel->move((this->width())/2 - (this->currentList->width())/2,this->currentList->pos().y()+this->currentList->height() + 10);
        if((this->currentList->height() + this->buttonPanel->height() +20 > this->height()) || this->currentList->height()<650){
            this->currentList->setFixedHeight(this->height()-120);
        }
    }
}