#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <vector>

#include "LogsVector.h"

/**
 * @brief Clase que representa una base de datos de Logs. Esta ordena los objetos LogsVector en un map
 *        para que sea más fácil la búsqueda de los objetos LogsVector.
 *
 */
class DataBase {
    private:
        // std::map<int, LogsVector* > logsByDate;
        LogsVector* mainTree;

        void sortByReps(Logs* current);
        void getMostRepeated(int n, Logs* current, std::vector<Logs*>& vec);
        void quickSort(std::vector<Logs*>& vec);
        void quickSort(std::vector<Logs*>& vec, int inicio, int fin);
        int partition(std::vector<Logs*>& vec, int inicio, int fin);

    public:
        DataBase(std::string fileName);
        void readFile(std::string fileName);
        // void addLogByDate(Logs* log);
        void addLogByIp(Logs* log);
        // LogsVector* atMonth(std::string month);
        LogsVector* atIp(int firstDigit);

        void getMostRepeated(int n);  // TODO implementar
                                      // Buscar logs entre 2 fechas
        // LogsVector* getLogsBetweenDates(Date* date1,Date* date2);
        // Buscar logs entre 2 ips
        // LogsVector* getLogsBetweenIps(Ip* ip1,Ip* ip2);
        // Buscar logs entre 2 fechas y guardarlos en un archivo
        // void writeToFile(Date* date1,Date* date2,std::string fileName);
        // Buscar logs entre 2 ips y guardarlos en un archivo
        // void writeToFile(Ip* ip1,Ip* ip2);
};

#endif