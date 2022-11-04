#include "DataBase.h"



DataBase::DataBase(std::string fileName) {
    readFile(fileName);
}

void DataBase::readFile(std::string fileName) {
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
        parse.push_back(logIp);
    }
    file.close();
    
    // Sort logs vector by bubble sort
    bool bandera;
    for (int i = 1; i < parse.size(); i++) {
        bandera = false;
        for (int j = 0; j < parse.size() - i; j++) {
            if (*(parse[j + 1]->getIp()) < parse[j]->getIp()) {
                Logs* temp = parse[j];
                parse[j] = parse[j + 1];
                parse[j + 1] = temp;
                bandera = true;
            }
        }
        if (!bandera) {
            break;
        }
    }

    //Create file with sorted logs
    std::ofstream file2;
    file2.open("bitacora3.txt", std::ios::out);
    for (int i = 0; i < parse.size(); i++) {
        file2 << parse[i]->getIp()->toString() << std::endl;
    }
    
    Logs* current = parse[0];
    int reps = 1;
    for (int i = 1; i < parse.size(); i++) {
        if (*current->getIp() != parse[i]->getIp()) {
            current->setReps(reps);
            this->mainTree->insert(current);
            current = parse[i];
            reps = 1;
        } else {
            reps++;
        }
    }

}

void DataBase::printByReps(int reps) {
    this->mainTree->printInorder();
}
