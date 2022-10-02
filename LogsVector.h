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
        void push_back(Logs* log);
        Logs* at(int i);
        void bubbleSortIp();
        void bubbleSortDate();
        //Búsqueda
        int searchByDate(Date* date); //Regresa la posición de la primera fecha que sea igual a la fecha dada
        int searchByIp(std::string ip); //Regresa la posición del primer ip que sea igual al ip dado
        //Sobrecarga de operadores
        Logs* operator[](int index);
        friend std::ostream& operator<<(std::ostream& os,LogsVector& logs);
};

#endif