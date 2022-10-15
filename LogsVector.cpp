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
void LogsVector::insert(Logs *log) {
    insert(log, &(this->root));
}

/**
 * @brief Método que inserta un objeto Logs en el vector
 * @complexity O(log n)
 *
 * @param log- apuntador de un objeto Logs
 * @param node- apuntador a un apuntador de un objeto Logs
 */
void LogsVector::insert(Logs *log, Logs **node) {
    if (*node == nullptr) {  // Si el nodo no existe
        Logs *tmp = new Logs(log->getDate(), log->ip->toString(), log->getRequest());
        *node = tmp;
        this->size++;
    } else {
        if (*log->ip > (*node)->ip) {
            insert(log, &(*node)->right);
        } else if (*log->ip < (*node)->ip) {
            insert(log, &(*node)->left);
        } else {
            (*node)->repeat++; // Si el ip es igual, solo incrementamos el contador
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
        std::cout << node->toString() << "Repeticiones: " << node->repeat << std::endl;
        printInorder(node->right);
    }
}
