//
// Created by Remi on 30/04/2020.
//

#ifndef JEU_UTILS_H
#define JEU_UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <QLabel>

double charToDouble(char); //Fonction de conversion d'un caractère à un double
double stringToNumber(std::string); //Fonction de conversion d'une chaîne de caractère à un nombre
void sort(std::vector<std::vector<std::string> > & ); //Fonction de tri d'un tableau de tableaux de chaînes de caractères
std::vector<std::vector<std::string> > createTemp(std::string,int); //Fonction de création d'un tableau de tableaux de chaînes de caractères
std::vector<std::string> cutString(std::string,int); //Fonction de découpage d'une chaîne de caractères
void reWrite(const char *, std::vector<std::vector<std::string> >); //Fonction d'écriture dans un fichier .txt
QLabel* createLabel(QString); //Création d'un Label

#endif //JEU_UTILS_H
