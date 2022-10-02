#include "DataBase.h"

/**
 * @brief Constructor default de la clase DataBase
 *
 */
DataBase::DataBase() {
    this->logsByDate = std::map<int, LogsVector*>{
        {1, new LogsVector()},
        {2, new LogsVector()},
        {3, new LogsVector()},
        {4, new LogsVector()},
        {5, new LogsVector()},
        {6, new LogsVector()},
        {7, new LogsVector()},
        {8, new LogsVector()},
        {9, new LogsVector()},
        {10, new LogsVector()},
        {11, new LogsVector()},
        {12, new LogsVector()}};
    for (int i = 0; i < 10; i++) {
        this->logsByIp[i] = new LogsVector();
    }
}

/**
 * @brief Agrega un objeto Logs al objeto LogsVector de acuerdo a su mes en el map
 *
 * @param logs- Log* con los logs
 */
void DataBase::addLogByDate(Logs* log) {
    this->logsByDate[log->getDate()->getMonthNumber()]->push_back(log);
}

/**
 * @brief Agrega un objeto Logs al objeto LogsVector de acuerdo a su primer dígito en el arreglo
 *
 * @param logs- Log* con los logs
 */
void DataBase::addLogByIp(Logs* log) {
    this->logsByIp[log->getIp()->getFirstDigit()]->push_back(log);
}

/**
 * @brief Método que lee el archivo con formato: Mes Dia Hora:Minutos:Segundos IP Request
 *        y lo guarda en un objeto Logs y lo agrega al objeto LogsVector de acuerdo a su mes
 *        en el map y los ordena de acuerdo a su fecha usando merge sort
 *
 * @param fileName
 * @complejidad O(n)
 */
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
    std::cout << "Leyendo archivo..." << std::endl;
    while (file >> month >> day >> time >> ip) {
        getline(file, request);
        Date* date = new Date(month, day, time.substr(0, 2), time.substr(3, 5), time.substr(6, 7));
        //Remove first space
        request = request.substr(1, request.length());
        Logs* logDate = new Logs(date, ip, request);
        Logs* logIp = new Logs(date, ip, request);
        this->addLogByDate(logDate);
        this->addLogByIp(logIp);
    }
    file.close();
    std::cout << "Archivo leido" << std::endl;
    // Sort the logs
    std::cout << "Ordenando..." << std::endl;
    for (int i = 0; i < 10; i++) {
        this->logsByIp[i]->bubbleSortIp();
    }
    for (auto &month : this->logsByDate) {
        month.second->bubbleSortDate();
    }
}

/**
 * @brief
 *
 * @param month-int con el mes
 * @return LogsVector* con los logs del mes
 */
LogsVector* DataBase::atMonth(std::string month) {
    if (month == "Jan") {
        return this->logsByDate[1];
    } else if (month == "Feb") {
        return this->logsByDate[2];
    } else if (month == "Mar") {
        return this->logsByDate[3];
    } else if (month == "Apr") {
        return this->logsByDate[4];
    } else if (month == "May") {
        return this->logsByDate[5];
    } else if (month == "Jun") {
        return this->logsByDate[6];
    } else if (month == "Jul") {
        return this->logsByDate[7];
    } else if (month == "Aug") {
        return this->logsByDate[8];
    } else if (month == "Sep") {
        return this->logsByDate[9];
    } else if (month == "Oct") {
        return this->logsByDate[10];
    } else if (month == "Nov") {
        return this->logsByDate[11];
    } else if (month == "Dec") {
        return this->logsByDate[12];
    } else {
        return nullptr;
    }
}

/**
 * @brief
 *
 * @param firstDigit-int con el primer dígito de la ip
 * @return LogsVector* con los logs del primer dígito de la ip
 */
LogsVector* DataBase::atIp(int firstDigit) {
    return this->logsByIp[firstDigit];
}

/**
 * @brief Método que imprime los logs de acuerdo a su ip
 *
 * @param os- ostream
 * @param db- objeto DataBase
 * @return ostream&
 */
std::ostream& operator<<(std::ostream& os, DataBase& db) {
    for (auto& log : db.logsByIp) {
        os << *log << std::endl;
    }
    return os;
}
