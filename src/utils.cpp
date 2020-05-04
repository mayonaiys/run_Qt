//
// Created by Remi on 30/04/2020.
//

#include "utils.h"

double charToDouble(char c){
    return (double)c-48; //Conversion d'un caractère en un double
}

double stringToNumber(std::string str){
    return charToDouble(str[0])*600 + charToDouble(str[1])*60 + charToDouble(str[3])*10 + charToDouble(str[4]) + charToDouble(str[6])/10 + charToDouble(str[7])/100; //Conversion d'une chaîne de caractère en double
}

std::vector<std::vector<std::string> > createTemp(std::string pathfile,int end) {
    //Lecture du fichier
    std::vector<std::vector<std::string> > temp; //Création d'un tableau de tableaux de chaînes de caractère
    std::ifstream file(pathfile); //Ouverture du fichier de scores
    if(file){ //Si le fichier existe
        std::string line;
        while(getline(file,line)){
            temp.push_back(cutString(line,end)); //Alors on ajoute les lignes découpées au tableau
        }
    } else { //Sinon
        std::ofstream newFile(pathfile); //On crée le fichier
    }
    return temp;
}

void sort(std::vector<std::vector<std::string> > & temp){
    std::vector<std::string> tempVect; //Création d'un tableau de chaînes de caractères temporaire
    for(int i = 0; i < temp.size(); i++){
        for(int u = 0; u < temp.size(); u++){
            if(stringToNumber(temp[i][1]) < stringToNumber(temp[u][1]) && i != u){ //Swap des valeurs de manière croissante
                tempVect = temp[i] ;
                temp[i] = temp[u];
                temp[u] = tempVect;
            }
        }
    }
}

std::vector<std::string> cutString(std::string str,int end){
    std::vector<std::string> tempVect; //Création d'un tableau de chaînes de caractères temporaire
    for(int i = 0; i < end; i++){
        int index = str.find(','); //Recherche de l'index ou se trouve la virgule dans la ligne
        std::string strTemp = str.substr(0,index); //Création d'une chaîne de caractère temporaire qui part de 0 jusqu'a l'index
        str = str.substr(index+1,str.size()); //La chaîne de caractère initiale devient la chaîne de caractère qui part de l'index jusqu'à la fin
        tempVect.push_back(strTemp); //On ajoute la chaîne de caractère temporaire au tableau temporaire
    }
    return tempVect;
}

void reWrite(const char *pathFile, std::vector<std::vector<std::string> > temp) {
    remove(pathFile); //On supprime le fichier existant
    std::ofstream file(pathFile); //On le recrée
    for(auto & i : temp){ //Pour tous les éléments du tableau
        std::string str = i[0] + "," + i[1]; //On crée une chaîne de caractères
        file << str << std::endl; //On écrit la ligne
    }
}

QLabel* createLabel(QString str) {
    QLabel* newLabel = new QLabel(str); //Création d'un label
    newLabel->setAttribute(Qt::WA_NoSystemBackground); //Suppression du fond de ce label
    newLabel->setAlignment(Qt::AlignHCenter); //Alignement du texte du label au centre
    return newLabel;
}