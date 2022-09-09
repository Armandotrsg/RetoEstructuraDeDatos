#include "DataBase.h"

/**
 * @brief Constructor default de la clase DataBase
 *
 */
DataBase::DataBase() {
    this->logs = std::map<int, LogsVector*>{
        //? Así se declaran vectores vacíos
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
}

/**
 * @brief Agrega un objeto Logs al objeto LogsVector de acuerdo a su mes en el map
 *
 * @param logs- Log* con los logs
 */
void DataBase::addLog(Logs* log) {
    this->logs[log->getDate()->getMonthNumber()]->add(log);
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
    // Sort the logs
    for (auto& log : this->logs) {
        log.second->mergeSort();
    }
}

/**
 * @brief
 *
 * @param month-int con el mes
 * @return LogsVector* con los logs del mes
 */
LogsVector* DataBase::at(int month) {
    return this->logs.at(month);
}

/**
 * @brief Sobrecarga del operador [] para acceder a los LogsVector de acuerdo a su mes
 *
 * @param month-int con el número del mes
 * @return LogsVector* con los logs del mes
 */
LogsVector* DataBase::operator[](int month) {
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

/**
 * @brief Método que busca los logs entre 2 fechas y los guarda en un objeto LogsVector
 *
 * @param date1-Date* con la fecha inicial
 * @param date2-Date* con la fecha final
 * @return LogsVector*
 * @complejidad O(n)
 */
LogsVector* DataBase::getLogsBetweenDates(Date* date1, Date* date2) {
    // Verificar que date 1 sea menor que date 2
    if (*date2 < date1) {
        Date* temp = date1;
        date1 = date2;
        date2 = temp;
    }
    LogsVector* logsInDates = new LogsVector();
    int i = this->logs[date1->getMonthNumber()]->searchByDate(date1, true);   // Busca el primer log que cumpla con la fecha inicial
    int j = this->logs[date2->getMonthNumber()]->searchByDate(date2, false);  // Busca el último log que cumpla con la fecha final
    // Verificamos que ninguno de los índices sea -1
    if (i == -1 || j == -1) {
        return nullptr;
    }
    if (date1->getMonthNumber() == date2->getMonthNumber()) {  // Si los meses son iguales están en el mismo vector
        while (i != j) {
            logsInDates->add(this->logs[date1->getMonthNumber()]->at(i));  // Agrega hasta que alcance la posición j
            i++;
        }
        return logsInDates;
    } else {                                                                               // Sino son del mismo mes,
        for (int k = i; k < this->logs[date1->getMonthNumber()]->getLogs().size(); k++) {  // Agrega los logs restantes en el vector de date1
            logsInDates->add(this->logs[date1->getMonthNumber()]->at(k));
        }

        bool foundMonth = false;
        for (auto& month : this->logs) {
            if (date1->getMonthNumber() == month.first) {  // hasta encontrar el mes después de date1, se ejecuta el siguiente código:
                foundMonth = true;
                continue;
            }
            if (foundMonth) {                                  // Ya hayamos descartados los otros meses en los que NO está el mes de date1
                if (month.first == date2->getMonthNumber()) {  // Verificamos que el mes de esta iteración sea igual al de date2

                    for (int m = 0; m <= j; m++) {
                        logsInDates->add((month.second->getLogs().at(m)));  // Agrega los logs hasta la posición j
                    }
                    return logsInDates;

                } else {  // Si aún el mes en esta iteración no es igual al mes del date2; agrega todo el vector de ese mes
                    for (int m = 0; m < month.second->getLogs().size(); m++) {
                        logsInDates->add(month.second->getLogs().at(m));
                    }
                }
            }
        }
    }
    return logsInDates;
}

/**
 * @brief Método que busca los logs entre 2 fechas y los escribe en un archivo
 *
 * @param date1-Date* con la fecha inicial
 * @param date2-Date* con la fecha final
 * @param fileName-string con el nombre del archivo
 */
void DataBase::writeToFile(Date* date1, Date* date2, std::string fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::out);
    if (file.fail()) {
        std::cout << "Error al abrir el archivo" << std::endl;
        exit(1);
    }
    LogsVector* logsInDates = this->getLogsBetweenDates(date1, date2);
    if (logsInDates == nullptr) {  // Verifica que no tenga un nullptr
        throw std::invalid_argument("No hay logs entre las fechas ingresadas");
    } else {
        std::cout << "Escribiendo en el archivo..." << std::endl;
        for (int i = 0; i < logsInDates->getLogs().size(); i++) {
            file << logsInDates->getLogs().at(i)->toString() << std::endl;
        }
        file.close();
        std::cout << "Archivo escrito exitosamente" << std::endl;
    }
}