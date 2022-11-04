#include "LogsVector.h"

/**
 * @brief Constructor default de la clase LogsVector
 *
 */
LogsVector::LogsVector() {
    this->root = nullptr;
    this->size = 0;
}

/**
 * @brief Método que regresa el tamaño del vector
 *
 * @return int
 */
int LogsVector::getSize() {
    return this->size;
}

/**
 * @brief Regresa el nodo raíz del vector
 *
 * @return Logs*
 */
Logs *LogsVector::getRoot() {
    return this->root;
}

/**
 * @brief Método que inserta un nuevo log en el vector
 * @complexity O(log n)
 *
 * @param log- Log a insertar
 */
void LogsVector::insert(Logs *log) {
    return insert(log, &(this->root));
}

/**
 * @brief Método que inserta un objeto Logs en el árbol
 * @complexity O(log n)
 *
 * @param log*- apuntador de un objeto Logs
 * @param node**- apuntador a un apuntador de un objeto Logs
 */
void LogsVector::insert(Logs *log, Logs **node) {
    if (*node == nullptr) {  // Si el nodo no existe
        Logs *tmp = new Logs(log->getDate(), log->ip->toString(), log->getRequest(), log->repeat);
        *node = tmp;
        this->size++;
    } else {
        if (log->repeat > (*node)->repeat) {
            insert(log, &(*node)->right);
        } else if (log->repeat < (*node)->repeat) {
            insert(log, &(*node)->left);
        } else {
            insert(log, &(*node)->right);
        }
    }
}

// * (toboqus, s. f.)

