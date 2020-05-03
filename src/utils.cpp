//
// Created by Remi on 30/04/2020.
//

#include "utils.h"

double charToDouble(char c){
    return (double)c-48;
}

double stringToNumber(std::string str){
    return charToDouble(str[0])*600 + charToDouble(str[1])*60 + charToDouble(str[3])*10 + charToDouble(str[4]) + charToDouble(str[6])/10 + charToDouble(str[7])/100;
}

std::vector<std::vector<std::string> > createTemp(std::string scoreFile,int end) {
    //Lecture du fichier
    std::vector<std::vector<std::string> > temp;
    std::ifstream scoresFile(scoreFile);
    if(scoresFile){
        std::string line;
        while(getline(scoresFile,line)){
            temp.push_back(cutString(line,end));
        }
    } else {
        std::ofstream file(scoreFile);
    }
    return temp;
}

void sort(std::vector<std::vector<std::string> > & temp){
    std::vector<std::string> t;
    for(int i = 0; i < temp.size(); i++){
        for(int u = 0; u < temp.size(); u++){
            if(stringToNumber(temp[i][1]) < stringToNumber(temp[u][1]) && i != u){
                t = temp[i] ;
                temp[i] = temp[u];
                temp[u] = t;
            }
        }
    }
}

std::vector<std::string> cutString(std::string str,int end){
    std::vector<std::string> tempVect;
    for(int i = 0; i < end; i++){
        int index = str.find(',');
        std::string strTemp = str.substr(0,index);
        str = str.substr(index+1,str.size());
        tempVect.push_back(strTemp);
    }
    return tempVect;
}