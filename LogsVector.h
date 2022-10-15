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
        Logs* root;
        int size;
        void insert(Logs* log, Logs **node);
        void printInorder(Logs* node);
    public:
        LogsVector();
        int getSize();
        void insert(Logs* log);
        Logs* getRoot();
        void printInorder();
        
};

#endif