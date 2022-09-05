#ifndef DATABASE_H
#define DATABASE_H

#include "Logs.h"
#include <vector>
#include <map>
#include <fstream>
#include "LogsVector.h"

/**
 * @brief Clase que representa una base de datos de Logs. Esta ordena los objetos LogsVector en un map
 *        para que sea más fácil la búsqueda de los objetos LogsVector.
 * 
 */
class DataBase{
    private:
        std::map<std::string, LogsVector* > logs;
        
    public:
        DataBase();
        void readFile(std::string fileName);
        void addLog(Logs* log);
        LogsVector* at(std::string month);
        
        //Sobrecarga de []
        LogsVector* operator[](std::string month);
        friend std::ostream& operator<<(std::ostream& os, DataBase& db);
        //Buscar logs entre 2 fechas
        LogsVector* seekByDate(std::string date1,std::string date2); // ! Falta implementar
};

#endif