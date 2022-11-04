#include "DataBase.h"
#include <vector>


DataBase::DataBase(std::string fileName) {
    LogsVector* mainTree = readFile(fileName);
    sortByReps(mainTree->getRoot());
}

LogsVector* DataBase::readFile(std::string fileName) {
    std::ifstream file;
    std::string line;  // line = month day hour:minute:second ip request
    std::string month, day,
        time,  // time = hour:minute:second
        ip, request;

    file.open(fileName);

    if (file.fail()) {
        std::cout << "Error al abrir el archivo" << std::endl;
        exit(1);
    }

    LogsVector *mainTree = new LogsVector();
    int max = 0, //Servirá para saber el tamaño del arreglo
        possibleMax = 0;
    
    //Create logs vector
    std::vector<Logs*> parse;


    while (file >> month >> day >> time >> ip) {
        getline(file, request);

        if (month.length() == 0) {
            continue;
        }
        if (month.length() > 3) {
            month = month.substr(3, 3);
        }
        
        Date* date = new Date(month, day, time.substr(0, 2), time.substr(3, 2), time.substr(6, 2));

        // Remove first space
        request = request.substr(1, request.length());
        Logs* logIp = new Logs(date, ip, request);
        possibleMax = mainTree->insert(logIp);
        if (possibleMax > max) {
            max = possibleMax;
        }
    }
    file.close();
    this->logsByIp = new LogsVector[max];
    for (int i = 0; i < max; i++) {
        this->logsByIp[i] = LogsVector();
    }
    this->maxReps = max;
    return mainTree;
   
}

void DataBase::sortByReps(Logs* current){ //Recorrido en preorden
    if (current != nullptr) {
        Logs* tmp = current->copy();
        this->logsByIp[tmp->repeat - 1].insert(tmp);
        sortByReps(current->left);
        sortByReps(current->right);
    }
}

void DataBase::printByReps(int reps) {
    this->logsByIp[reps - 1].printInorder();
}
