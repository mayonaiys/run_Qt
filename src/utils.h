//
// Created by Remi on 30/04/2020.
//

#ifndef JEU_UTILS_H
#define JEU_UTILS_H

#include <string>
#include <vector>
#include <fstream>

double charToDouble(char);

double stringToNumber(std::string);

void sort(std::vector<std::vector<std::string> > & );

std::vector<std::vector<std::string> > createTemp(std::string);

std::vector<std::string> cutString(std::string);

#endif //JEU_UTILS_H
