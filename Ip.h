#ifndef IP_H
#define IP_H
#include <sstream>
#include <string>

/**
 * @brief Clase que representa una dirección IP
 * @pre La dirección IP debe tener el formato:
 *      XXX.XXX.XXX.XXX:XXXXX
 */
class Ip {
    private:
        int first;
        int second;
        int third;
        int fourth;
        int port;

    public:
        Ip();
        Ip(std::string ip);
        std::string toString();
        std::string toStringWithoutPort();
        int getFirstDigit();
        // Sobre carga de operadores
        bool operator==(Ip*);
        bool operator!=(Ip*);
        bool operator>(Ip*);
        bool operator<(Ip*);
        bool operator>=(Ip*);
        bool operator<=(Ip*);
        friend std::ostream& operator<<(std::ostream&, Ip&);
};

#endif