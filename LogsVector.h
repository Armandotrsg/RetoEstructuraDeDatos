#ifndef LOGSVECTOR_H
#define LOGSVECTOR_H

#include "Logs.h"


/**
 * @brief Clase que representa un vector de Logs
 *        con sus respectivos métodos de ordenamiento y búsqueda
 * 
 */
class LogsVector {
    private:
        Logs* first;
        Logs* last;
        int size;
        void swap(Logs*, Logs*);
    public:
        LogsVector();
        int getSize();
        Logs* getFirst();
        Logs* getLast();
        void setLast(Logs*);
        void push_back(Logs* log);
        Logs* at(int i);
        void bubbleSortIp();
        void bubbleSortDate();
        //Sobrecarga de operadores
        Logs* operator[](int index);
        friend std::ostream& operator<<(std::ostream& os,LogsVector& logs);
};

#endif