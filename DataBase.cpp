#include "DataBase.h"

/**
 * @brief Constructor default de la clase DataBase
 * 
 */
DataBase::DataBase() {
    this->logs = std::map<std::string, LogsVector*>{
        //? Así se declaran vectores vacíos
        {"Jan", new LogsVector()}, {"Feb", new LogsVector()}, {"Mar", new LogsVector()}, {"Apr", new LogsVector()},
        {"May", new LogsVector()}, {"Jun", new LogsVector()}, {"Jul", new LogsVector()}, {"Aug", new LogsVector()},
        {"Sep", new LogsVector()}, {"Oct", new LogsVector()}, {"Nov", new LogsVector()}, {"Dec", new LogsVector()}};
}

/**
 * @brief Agrega un objeto Logs al objeto LogsVector de acuerdo a su mes en el map
 * 
 * @param logs- Log* con los logs
 */
void DataBase::addLog(Logs* log) {
    this->logs[log->getDate()->getMonthName()]->add(log);
}

/**
 * @brief Método que lee el archivo con formato: Mes Dia Hora:Minutos:Segundos IP Request
 *        y lo guarda en un objeto Logs y lo agrega al objeto LogsVector de acuerdo a su mes
 *        en el map y los ordena de acuerdo a su fecha usando merge sort
 * 
 * @param fileName 
 */
void DataBase::readFile(std::string fileName) {
    std::ifstream file;
    std::string line; // line = month day hour:minute:second ip request
    std::string month, day,
        time,  // time = hour:minute:second
        ip, request;

    file.open(fileName);

    if (file.fail()) {
        std::cout << "Error al abrir el archivo" << std::endl;
        exit(1);
    }

    while (!file.eof()) {
        getline(file, line);
        month = line.substr(0, 3);
        int space = line.find(" ", 4);  // Used to find the first space in the line, given that days are either 1 or 2 digits
        day = line.substr(4, space);
        int space2 = line.find(" ", space + 1);  // Used to find the second space in the line.
        time = line.substr(space + 1, space2);
        int space3 = line.find(" ", space2 + 1);  // Used to find the third space in the line.
        ip = line.substr(space2 + 1, space3);
        request = line.substr(space3 + 1, line.length());  // Used to find the rest of the line.
        Date* date = new Date(month, day, time.substr(0, 2), time.substr(3, 5), time.substr(6, 7));
        Logs* log = new Logs(date, ip, request);
        this->addLog(log);
    }
    file.close();
    //Sort the logs
    for (auto& log : this->logs) {
        log.second->mergeSort();
    }

    
}

/**
 * @brief 
 * 
 * @param month-string con el mes
 * @return LogsVector* con los logs del mes
 */
LogsVector* DataBase::at(std::string month) {
    return this->logs.at(month);
}

/**
 * @brief Sobrecarga del operador [] para acceder a los LogsVector de acuerdo a su mes
 * 
 * @param month-string con el mes
 * @return LogsVector* con los logs del mes
 */
LogsVector* DataBase::operator[](std::string month) {
    return this->at(month);
}

/**
 * @brief Método que imprime los logs de acuerdo a su mes
 * 
 * @param os- ostream
 * @param db- objeto DataBase
 * @return ostream& 
 */
std::ostream& operator<<(std::ostream& os, DataBase& db) {
    for (auto& log : db.logs) {
        os << log.first << std::endl;
        os << *log.second << std::endl;
    }
    return os;
}