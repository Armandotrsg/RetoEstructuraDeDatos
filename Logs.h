#ifndef LOGS_H
#define LOGS_H

#include "Date.h"
#include "Ip.h"

/**
 * @brief Clase que representa un log. Tiene un objeto Date, un objeto Ip y un string con el request
 *
 */
class Logs {
    public:
        // Atributos
        Date* date;
        Ip* ip;
        std::string request;
        // Métodos
        Logs();
        Logs(Date* date, std::string ip, std::string request);
        ~Logs();
        Date* getDate();
        Ip* getIp();
        std::string getRequest();
        std::string toString();
        friend std::ostream& operator<<(std::ostream&, Logs&);
};

#endif