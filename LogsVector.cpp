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
Logs* LogsVector::getRoot() {
    return this->root;
}

/**
 * @brief Método que inserta un nuevo log en el vector
 * @complexity O(log n)
 *
 * @param log- Log a insertar
 */
int LogsVector::insert(Logs *log) {
    std::cout << "Inserting " << *log->getIp() << std::endl;
    return insert(log, &(this->root));
}

/**
 * @brief Método que inserta un objeto Logs en el árbol
 * @complexity O(log n)
 *
 * @param log*- apuntador de un objeto Logs
 * @param node**- apuntador a un apuntador de un objeto Logs
 */
int LogsVector::insert(Logs *log, Logs **node) {
    if (*node == nullptr) {  // Si el nodo no existe
        Logs *tmp = new Logs(log->getDate(), log->ip->toString(), log->getRequest(), log->repeat);
        *node = tmp;
        this->size++;
        return 1;
    } else {
        if (log->repeat > (*node)->repeat) {
            return insert(log, &(*node)->right);
        } else if (log->repeat < (*node)->repeat) {
             return insert(log, &(*node)->left);
        } else {
            return insert(log, &(*node)->right);
        }
    }
}

// * (toboqus, s. f.)

void LogsVector::printInorder() {
    printInorder(this->root);
}

void LogsVector::printInorder(Logs *node) {
    if (node != nullptr) {
        printInorder(node->left);
        std::cout << node->toString() << std::endl;
        printInorder(node->right);
    }
}
