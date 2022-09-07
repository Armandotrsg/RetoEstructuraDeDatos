#include "LogsVector.h"

/**
 * @brief Constructor default de la clase LogsVector
 * 
 */
LogsVector::LogsVector() {
    this->logs = std::vector<Logs*>();
}

/**
 * @brief Agregar un objeto Logs al vector de su atributo
 * 
 * @param logs- vector de apuntadores a Logs
 */
void LogsVector::add(Logs* log) {
    this->logs.push_back(log);
}

/**
 * @brief Obtener el vector de Logs
 * 
 * @return vector<Logs*> con el vector de Logs
 */
std::vector<Logs*> LogsVector::getLogs() {
    return this->logs;
}

/**
 * @brief Obtener un objeto Logs en la posición i
 * 
 * @param i- posición del objeto Logs
 * @return Logs* con el objeto Logs
 */
Logs* LogsVector::at(int i) {
    return this->logs.at(i);
}

/**
 * @brief Sobrecarga del operador []
 * @param i-int índice del vector
 * @return Logs* con el objeto Logs
 */
Logs* LogsVector::operator[](int i) {
    return this->logs.at(i);
}

/**
 * @brief Sobrecarga del operador <<
 * 
 * @param os- ostream
 * @param logs- objeto LogsVector
 * @return ostream& 
 */
std::ostream& operator<<(std::ostream& os, LogsVector& logs) {
    for (auto& log : logs.logs) {
        os << *log << std::endl;
    }
    return os;
}

/**
 * @brief Junta 2 sublistas ordenadas
 * 
 * @param inicio-int índice del inicio de la primera sublista
 * @param fin- int índice del final de la segunda sublista
 * 
 * @pre inicio < fin
 * @pre las sublistas están ordenadas
 */
void LogsVector::merge(int inicio, int fin) {
    int centro = (inicio + fin) / 2;
    int j = inicio, k = centro + 1, size = fin - inicio + 1;
    Logs* datosTmp[size];  // Arreglo de datos temporales

    for (int i = 0; i < size; i++) {
        if (j <= centro && k <= fin) {
            if (*this->logs[j]->getDate() < this->logs[k]->getDate()) {
                datosTmp[i] = this->logs[j++];
            } else {
                datosTmp[i] = this->logs[k++];
            }
        } else if (j <= centro) {
            datosTmp[i] = this->logs[j++];
        } else {
            datosTmp[i] = this->logs[k++];
        }
    }

    for (int m = 0; m < size; m++) {
        this->logs[inicio + m] = datosTmp[m];
        

    }
    
}

/**
 * @brief Función que manda a llamar en orden a la función mergeSort con parámetros
 * 
 */
void LogsVector::mergeSort(){
    mergeSort(0, this->logs.size() - 1);
}

/**
 * @brief Ordena el vector de Logs
 * 
 * @param left- int índice del inicio de la sublista
 * @param inicio- int índice del final de la sublista
 * 
 */
void LogsVector::mergeSort(int left, int right) {
    int centro;
    if (left < right) {
        centro = (left + right) / 2;
        mergeSort(left, centro);
        mergeSort(centro + 1, right);
        merge(left, right);
    }
}

// ! Borrar método
void LogsVector::bubbleSort() {
    bool bandera;
    for (int i = 0; i < this->logs.size(); i++) {
        bandera = false;
        for (int j = 0; j < this->logs.size() - 1; j++) {
            if (*this->logs.at(j)->getDate() > this->logs.at(j+1)->getDate()) {
                bandera = true;
                Logs* tmp = this->logs[j];
                this->logs[j] = this->logs[j + 1];
                this->logs[j + 1] = tmp;
            }
        }
        if (!bandera) {
            break;
        }
    }
}

/**
 * @brief Regresa la primera posición en la que haga match con la primera fecha
 * 
 * @param date-Date* con la fecha a buscar
 * @param first-bool si quieres regresar la primera posición o la última
 * @return int con la posición del match
 */
int LogsVector::searchByDate(Date* date,bool first){ // ! Corregir
    int inicio = 0;
    int fin = this->logs.size() -1;
    int centro;
    while (inicio <= fin) {
        centro = (inicio + fin) / 2;
        if (this->logs[centro]->getDate()->getDay() == date->getDay()) {
            break;
        } else if (this->logs[centro]->getDate()->getDay() < date->getDay()) {
            inicio = centro + 1;
        } else {
            fin = centro - 1;
        }
    }
    if (first){ //Regresar la primera posición en la que se encuentre la fecha
        while (centro > 0 && this->logs[centro - 1]->getDate()->getDay() == date->getDay()) {
            centro--;
        }
    } else { //Regresar la última posición en la que se encuentre la fecha
        while (centro < this->logs.size() - 1 && this->logs[centro + 1]->getDate()->getDay() == date->getDay()) {
            centro++;
        }
    }
    
    return centro;

}