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

void DataBase::put(Logs* log) {
    put(log, true);
}

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
        /* for (std::list<LogsVector*>::iterator it = this->table[pos].begin(); it != this->table[pos].end(); it++) {
            if ((*it)->at(0)->getIp() == log->getIp()) {  // Si la ip del log es igual a la ip del LogsVector, se agrega el log al LogsVector
                (*it)->add(log);
                found = true;
                break;
            }
        } */

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
