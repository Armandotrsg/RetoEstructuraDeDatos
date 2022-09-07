#ifndef LOGS_H
#define LOGS_H

#include "Date.h"

/**
 * @brief Clase que representa un log. Tiene un objeto Date, un string con el ip y un string con el request
 * 
 */
class Logs{
    private:
        Date* date;
        std::string ip;
        std::string request;
    public:
        Logs();
        Logs(Date* date, std::string ip, std::string request);
        Date* getDate();
        std::string getIp();
        std::string getRequest();
        std::string toString();
        friend std::ostream& operator<<(std::ostream&, Logs&);
};

#endif