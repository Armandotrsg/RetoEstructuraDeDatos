#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include "LogsVector.h"

/**
 * @brief Clase que representa una base de datos de Logs. Esta ordena los objetos LogsVector en un map
 *        para que sea más fácil la búsqueda de los objetos LogsVector.
 * 
 */
class DataBase{
    private:
        std::map<int, LogsVector* > logs;
        
    public:
        DataBase();
        void readFile(std::string fileName);
        void addLog(Logs* log);
        LogsVector* at(int month);
        
        //Sobrecarga de []
        LogsVector* operator[](int month);
        friend std::ostream& operator<<(std::ostream& os, DataBase& db);
        //Buscar logs entre 2 fechas
        LogsVector* getLogsBetweenDates(Date* date1,Date* date2); // ! Falta implementar
        //Buscar logs entre 2 fechas y guardarlos en un archivo
        void writeToFile(Date* date1,Date* date2,std::string fileName); // ! Falta implementar
};

#endif