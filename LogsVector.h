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
        Logs* at(int i);
        //Búsqueda
        int searchByDate(Date* date,bool first); //Regresa la posición de la primera fecha que sea igual a la fecha dada
        //Sobrecarga de operadores
        Logs* operator[](int index);
        friend std::ostream& operator<<(std::ostream& os,LogsVector& logs);
};

#endif