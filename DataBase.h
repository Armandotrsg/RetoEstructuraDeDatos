#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <vector>
#include <list>

#include "LogsVector.h"

/**
 * @brief Clase que representa una base de datos de Logs. Se utilizará una tabla hash para almacenar los Logs
 *       siendo la llave la ip del log y guardando en el valor una lista ligada de vector de logs
 *
 */
class DataBase {
    private:
        std::list<LogsVector*> *table;
        int size;
        int sizeA;
        int getPos(std::string key);
        void rehashing();
        void put(Logs* log, bool rehash);
    public:
        DataBase();
        void readFile(std::string fileName);
        void put(Logs* log);
        LogsVector* get(std::string key);
        friend std::ostream& operator<<(std::ostream&, DataBase&);
        
};

#endif