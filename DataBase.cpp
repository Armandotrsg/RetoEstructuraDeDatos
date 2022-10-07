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
    this->currentFile = 1;
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

    // Busca que el archivo de los logs ordenados por ip aún no exista
    std::ifstream file2;
    file2.open("bitacoraOrdenadaIP-Eq7.txt");
    bool file2NotExists = file2.fail();

    while (file >> month >> day >> time >> ip) {
        getline(file, request);
        Date* date = new Date(month, day, time.substr(0, 2), time.substr(3, 5), time.substr(6, 7));
        // Remove first space
        request = request.substr(1, request.length());
        Logs* logDate = new Logs(date, ip, request);
        this->addLogByDate(logDate);
        if (file2NotExists) {
            Logs* logIp = new Logs(date, ip, request);
            this->addLogByIp(logIp);
        }
    }
    file.close();
    // Sort the logs
    // Ordena los logs por fecha
    /* for (auto& month : this->logsByDate) {
        month.second->bubbleSortDate();
    } */

    if (file2NotExists) {  // Si no existe el archivo de logs ordenados, se crea y se ordenan los logs por ip
        for (int i = 0; i < 10; i++) {
            this->logsByIp[i]->bubbleSortIp();
        }
        // Escribir en un archivo los logs ordenados por ip
        std::ofstream fileIp;
        fileIp.open("bitacoraOrdenadaIP-Eq7.txt", std::ios::out);
        if (fileIp.fail()) {
            std::cout << "Error al abrir el archivo" << std::endl;
            exit(1);
        }
        for (int i = 0; i < 10; i++) {
            Logs* temp = this->logsByIp[i]->getFirst();
            while (temp != nullptr) {
                fileIp << temp->toString() << std::endl;
                temp = temp->next;
            }
        }
    } else {
        while (file2 >> month >> day >> time >> ip) {
            getline(file2, request);
            Date* date = new Date(month, day, time.substr(0, 2), time.substr(3, 5), time.substr(6, 7));
            // Remove first space
            request = request.substr(1, request.length());
            Logs* logIp = new Logs(date, ip, request);
            this->addLogByIp(logIp);
        }
    }
    file2.close();
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

/**
 * @brief Agrega a una lista ligada de Logs los logs que estén entre las 2 ip's dadas
 *
 * @param ip1- Ip* con la ip inicial
 * @param ip2- Ip* con la ip final
 * @complexity O(n)
 *
 * @return LogsVector* Regresa un objeto LogsVector con los logs que estén entre las 2 ip's dadas
 */
LogsVector* DataBase::getLogsBetweenIps(Ip* ip1, Ip* ip2) {
    if (*ip1 > ip2) {
        Ip* temp = ip1;
        ip1 = ip2;
        ip2 = temp;
    }

    // Verificar que ip1 tenga el formato correcto
    if (ip1->getFirstDigit() < 0) {
        ip1 = this->logsByIp[0]->getFirst()->getIp();
    } else if (ip1->getFirstDigit() > 9) {
        ip1 = this->logsByIp[9]->getLast()->getIp();
    }

    // Verificar que ip2 tenga el formato correcto
    if (ip2->getFirstDigit() < 0) {
        ip2 = this->logsByIp[0]->getFirst()->getIp();
    } else if (ip2->getFirstDigit() > 9) {
        ip2 = this->logsByIp[9]->getLast()->getIp();
    }

    LogsVector* logsBetween = new LogsVector();
    if (ip1->getFirstDigit() == ip2->getFirstDigit()) {
        Logs* temp = this->logsByIp[ip1->getFirstDigit()]->getFirst();
        for (int i = 0; i < this->logsByIp[ip1->getFirstDigit()]->getSize(); i++) {
            if (temp->next == nullptr) {
                logsBetween->push_back(temp);
                break;
            } else {
                if (*temp->ip >= ip1 && *temp->ip <= ip2) {
                    logsBetween->push_back(temp);
                }
                if (*temp->next->ip > ip2) {
                    return logsBetween;
                }
                temp = temp->next;
            }
        }
    } else {
        Logs* temp = this->logsByIp[ip1->getFirstDigit()]->getFirst();
        for (int i = 0; i < this->logsByIp[ip1->getFirstDigit()]->getSize(); i++) {  // Agregar los logs que faltan en el vector donde se encuentra ip1
            if (temp->next == nullptr) {
                Logs* temp2 = new Logs(temp->getDate(), temp->getIp()->toString(), temp->getRequest());
                logsBetween->push_back(temp2);
                break;
            } else {
                if (*temp->ip >= ip1 && temp->next->next != nullptr) {
                    logsBetween->push_back(temp);
                }
                if (temp->next->next == nullptr) {
                    // Crear copia del último valor de la lista
                    Logs* temp2 = new Logs(temp->next->getDate(), temp->next->getIp()->toString(), temp->next->getRequest());
                    logsBetween->push_back(temp2);
                    break;
                }
            }
            temp = temp->next;
        }
        for (int j = ip1->getFirstDigit() + 1; j <= ip2->getFirstDigit(); j++) {  // Agregar los logs que faltan en todos los vectores hasta el vector donde se encuentra ip2
            Logs* temp2 = this->logsByIp[j]->getFirst();
            for (int k = 0; k < this->logsByIp[j]->getSize(); k++) {
                if (*temp2->ip <= ip2) {
                    logsBetween->push_back(temp2);
                } else if (*temp2->ip > ip2) {
                    return logsBetween;
                }
                temp2 = temp2->next;
            }
        }
        return logsBetween;
    }
    return logsBetween;
}

/**
 * @brief Escribe un archivo con los logs ordenados por ip que proporciona el usuario y aumenta el contador de
 *       los archivos que se han creado
 *
 * @param ip1- Ip* con la ip inicial
 * @param ip2- Ip* con la ip final
 */
void DataBase::writeToFile(Ip* ip1, Ip* ip2) {
    std::ofstream file;
    std::string fileName = "salida" + std::to_string(this->currentFile) + "-Eq7.txt";
    file.open(fileName, std::ios::out);
    if (file.fail()) {
        std::cout << "Error al abrir el archivo" << std::endl;
        exit(1);
    }
    LogsVector* logsBetween = this->getLogsBetweenIps(ip1, ip2);
    Logs* temp = logsBetween->getFirst();
    for (int i = 0; i < logsBetween->getSize(); i++) {
        file << temp->toString() << std::endl;
        temp = temp->next;
    }
    this->currentFile++;
    file.close();
}
