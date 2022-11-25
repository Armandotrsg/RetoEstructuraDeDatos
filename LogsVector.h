#ifndef LOGSVECTOR_H
#define LOGSVECTOR_H

#include "Logs.h"
#include <vector>

/**
 * @brief Clase que representa un BST de Logs
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
        ~LogsVector();
        int size();
        std::vector<Logs*> getLogs();
        void add(Logs* log);
        void mergeSort();
        Logs* at(int i);
        Logs* operator[](int i);
        friend std::ostream& operator<<(std::ostream&, LogsVector&);
};

#endif