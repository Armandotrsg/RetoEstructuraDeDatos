#ifndef LOGSVECTOR_H
#define LOGSVECTOR_H

#include "Logs.h"
#include <vector>

/**
 * @brief Clase que representa un vector de Logs
 *        con sus respectivos métodos de ordenamiento y búsqueda
 * 
 */
class LogsVector {
    private:
        std::vector<Logs*> logs;
        void mergeSort(int, int);
        void merge(int,int);
    public:
        LogsVector();
        std::vector<Logs*> getLogs();
        void add(Logs* log);
        void mergeSort();
        void bubbleSort();
        Logs* at(int i);
        //Sobrecarga de operadores
        Logs* operator[](int index);
        friend std::ostream& operator<<(std::ostream& os,LogsVector& logs);
};

#endif