#include "DataBase.h"

#include <cmath>
#include <cstddef>

/**
 * @brief Constructor de la clase DataBase
 * @param fileName- string con el nombre del archivo
 */
DataBase::DataBase() {
    this->size = 0;
    this->sizeA = 101;
    this->table = new std::list<LogsVector*>[this->sizeA];
}

/**
 * @brief Obtiene la posición en la tabla hash
 * @complexity O(1)
 *
 * @param key- std::string Recibe la llave (IP)
 * @return int con la posición
 */
int DataBase::getPos(std::string key) {
    std::size_t hashC = std::hash<std::string>{}(key);  // Recibe un string y te da una función hash a un valor numérico size_t
    int hashCode = static_cast<int>(hashC);             // Hacemos un casting del size_t a int
    return std::abs(hashCode) % this->sizeA;            // Comprimimos la función hash a que quepa en el areglo
}

/**
 * @brief Manda a llamar un método sobrecargado para insertar un log en la tabla hash
 * 
 * @param log- Logs* Recibe un log
 */
void DataBase::put(Logs* log) {
    put(log, true);
}

/**
 * @brief Inserta un log en la tabla hash
 * @complexity O(1)
 *
 * @param log- Logs* Recibe un log
 * @param rehash- bool Recibe un booleano para saber si se debe hacer rehashing, esto
 *             para que no se haga rehashing mientras se esté haciendo rehashing y se estén
 *            volviendo a insertar los logs en la tabla hash
 */
void DataBase::put(Logs* log, bool rehash) {
    int pos = getPos(log->getIp()->toStringWithoutPort());  // Obtener la posición

    if (rehash) {
        if ((this->size * 1.0) / (this->sizeA * 1.0) > 0.75) {  // Verificar si hay que hacer el rehashing
            rehashing();
        }
    }

    if (this->table[pos].empty()) {  // Verificamos que la lista ligada en esa posición no esté vacía, para crear un nuevo objeto LogsVector
        LogsVector* logsVector = new LogsVector();
        logsVector->add(log);
        this->table[pos].push_back(logsVector);
        this->size++;
    } else {  // Si no está vacía, se agrega el log al vector de logs
        // Verificamos que no se encuentre la ip del log en la lista ligada
        for (auto it : this->table[pos]) {
            if (*(it->at(0)->getIp()) == log->getIp()) {  // ! CHECAR
                it->add(log);
                return;
            }
        }

        // Si no se encontró la ip del log en los LogsVector, se crea un nuevo LogsVector y se agrega el log
        LogsVector* logsVector = new LogsVector();
        logsVector->add(log);
        this->table[pos].push_back(logsVector);
        this->size++;
    }
}

/**
 * @brief Rebalancea la tabla hash
 * @complexity O(n)
 *
 */
void DataBase::rehashing() {
    int oldSize = this->sizeA;
    this->sizeA = this->sizeA * 2 + 1;
    std::list<LogsVector*>* oldTable = this->table;

    this->table = new std::list<LogsVector*>[sizeA];
    for (int i = 0; i < oldSize; i++) {
        for (auto it : oldTable[i]) {
            for (int j = 0; j < it->size(); j++) {
                put(it->at(j), false);
            }
        }
    }
    delete[] oldTable;
}

/**
 * @brief Lee el archivo y lo parsea para guardar los logs en la tabla hash
 * 
 * @param fileName- std::string Recibe el nombre del archivo 
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

    while (file >> month >> day >> time >> ip) {
        getline(file, request);

        Date* date = new Date(month, day, time.substr(0, 2), time.substr(3, 2), time.substr(6, 2));

        // Remove first space
        request = request.substr(1, request.length());
        Logs* logIp = new Logs(date, ip, request);
        put(logIp);
    }

    file.close();
}

/**
 * @brief Obtiene un LogsVector* de la tabla hash
 * @complexity O(1)
 * 
 */
LogsVector* DataBase::get(std::string key) {
    int pos = getPos(key);
    for (auto it : this->table[pos]) {
        if ((it->at(0)->getIp()->toStringWithoutPort()) == key) {
            return it;
        }
    }
    return nullptr;
}

/**
 * @brief Imprime el LogsVector de la ip
 *
 */
void DataBase::print(std::string key) {
    LogsVector* logsVector = get(key);
    if (logsVector != nullptr) {
        logsVector->mergeSort();
        std::cout << "IP: " << key << std::endl;
        std::cout << "Fechas de acceso:" << std::endl;
        for (int i = 0; i < logsVector->size(); i++) {
            std::cout << "\t" << logsVector->at(i)->getDate()->toString() << std::endl;
        }
    } else {
        throw std::invalid_argument("No se encontró la ip");
    }
}


