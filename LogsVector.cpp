#include "LogsVector.h"

/**
 * @brief Constructor default de la clase LogsVector
 *
 */
LogsVector::LogsVector() {
    this->first = nullptr;
    this->last = nullptr;
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
 * @brief Agregar un objeto Logs al vector de su atributo
 *
 * @param logs- vector de apuntadores a Logs
 */
void LogsVector::push_back(Logs* log) {
    if (this->first == nullptr) {
        this->first = log;
        this->last = log;
    } else {
        this->last->next = log;
        this->last = log;
    }
    this->size++;
}

/**
 * @brief Obtener un objeto Logs en la posición i
 *
 * @param i- posición del objeto Logs
 * @return Logs* con el objeto Logs
 */
Logs* LogsVector::at(int i) {
    Logs* temp = this->first;
    for (int j = 0; j < i; j++) {
        temp = temp->next;
    }
    return temp;
}

/**
 * @brief Método que regresa el primer objeto Logs del vector
 *
 * @return Logs* con el objeto Logs
 */
Logs* LogsVector::getFirst() {
    return this->first;
}

/**
 * @brief Método que regresa el último objeto Logs del vector
 *
 * @return Logs* con el objeto Logs
 */
Logs* LogsVector::getLast() {
    return this->last;
}

/**
 * @brief Método que actualiza el último objeto Logs del vector
 *
 * @return Logs* con el objeto Logs
 */
void LogsVector::setLast(Logs* log) {
    this->last = log;
}

/**
 * @brief Sobrecarga del operador []
 * @param i-int índice del vector
 * @return Logs* con el objeto Logs
 */
Logs* LogsVector::operator[](int i) {
    return this->at(i);
}

/**
 * @brief Sobrecarga del operador <<
 *
 * @param os- ostream
 * @param logs- objeto LogsVector
 * @return ostream&
 */
std::ostream& operator<<(std::ostream& os, LogsVector& logs) {
    Logs* temp = logs.first;
    while (temp != nullptr) {
        os << temp->toString() << std::endl;
        temp = temp->next;
    }
    return os;
}

void LogsVector::swap(Logs* a, Logs* b) {
    Date* tempDate = a->date;
    Ip* tempIp = a->ip;
    std::string tempRequest = a->request;
    a->date = b->date;
    a->ip = b->ip;
    a->request = b->request;
    b->date = tempDate;
    b->ip = tempIp;
    b->request = tempRequest;
}

/**
 * @brief Ordenar el vector de Logs con el algoritmo de burbuja
 * @complexity O(n^2)
 */
void LogsVector::bubbleSortIp() {
    bool bandera;
    Logs* actual = nullptr;
    for (int i = 1; i < this->size; i++) {
        bandera = false;
        actual = this->first;
        for (int j = 0; j < this->size - i; j++) {
            if (*(actual->getIp()) > actual->next->getIp()) {
                this->swap(actual, actual->next);
                bandera = true;
            }
            actual = actual->next;
        }
        if (!bandera) {
            break;
        }
    }
}

/**
 * @brief Ordenar la lista de Logs con el algoritmo de bubble
 * @complexity O(n^2)
 */
void LogsVector::bubbleSortDate() {
    bool bandera;
    Logs* actual = nullptr;
    for (int i = 1; i < this->size; i++) {
        bandera = false;
        actual = this->first;
        for (int j = 0; j < this->size - i; j++) {
            if (*(actual->date) > actual->next->date) {
                this->swap(actual, actual->next);
                bandera = true;
            }
            actual = actual->next;
        }
        if (!bandera) {
            break;
        }
    }
}

// * (González et al., 2020)