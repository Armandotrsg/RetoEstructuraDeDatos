#include "Ip.h"

/**
 * @brief Constructor default de la clase Ip
 *
 * 
 */
Ip::Ip() {
    this->first = 0;
    this->second = 0;
    this->third = 0;
    this->fourth = 0;
    this->port = 0;
}

/**
 * @brief Constructor de la clase Ip
 *
 * @param ip- string con el ip
 * @pre La dirección IP debe tener el formato: XXX.XXX.XXX.XXX:XXXX
 */
Ip::Ip(std::string ip) {
    //Replace all the dots with spaces
    std::replace(ip.begin(), ip.end(), '.', ' ');
    //Replace all the colons with spaces
    std::replace(ip.begin(), ip.end(), ':', ' ');

    //Create a stream from the string
    std::istringstream iss(ip);
    if (!(iss >> this->first >> this->second >> this->third >> this->fourth >> this->port)) {
        throw std::invalid_argument("Ingresaste un ip inválido");
    }
}

/**
 * @brief Convierte el objeto Ip a un string
 * 
 * @return std::string 
 */
std::string Ip::toString() {
    std::string s = "";
    s += std::to_string(this->first) + "." + std::to_string(this->second) + "." + std::to_string(this->third) + "." + std::to_string(this->fourth) + ":" + std::to_string(this->port);
    return s;
}

/**
 * @brief Obtener el primer dígito del ip
 * 
 * @return int 
 */
int Ip::getFirstDigit() {
    return this->first/100;
}

/**
 * @brief Comparar si el objeto Ip es igual a otro
 * 
 * @param ip 
 * @return true si es igual
 * @return false si no es igual
 */
bool Ip::operator==(Ip* ip) {
    return this->first == ip->first && this->second == ip->second && this->third == ip->third && this->fourth == ip->fourth && this->port == ip->port;
}

/**
 * @brief Comparar si el objeto Ip es diferente a otro
 * 
 * @param ip 
 * @return true si es diferente
 * @return false si es igual
 */
bool Ip::operator!=(Ip* ip) {
    return !(*this == ip); // ? Funciona asi
}

/**
 * @brief Comparar si el objeto Ip es mayor a otro
 * 
 * @param ip 
 * @return true si es mayor
 * @return false si no es mayor
 */
bool Ip::operator > (Ip* ip) {
    if (this->first > ip->first) {
        return true;
    } else if (this->first == ip->first) {
        if (this->second > ip->second) {
            return true;
        } else if (this->second == ip->second) {
            if (this->third > ip->third) {
                return true;
            } else if (this->third == ip->third) {
                if (this->fourth > ip->fourth) {
                    return true;
                } else if (this->fourth == ip->fourth) {
                    if (this->port > ip->port) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/**
 * @brief Comparar si el objeto Ip es menor a otro
 * 
 * @param ip 
 * @return true si es menor
 * @return false si no es menor
 */
bool Ip::operator < (Ip* ip) {
    return !(*this > ip) && !(*this == ip);
}

/**
 * @brief Comparar si el objeto Ip es mayor o igual a otro
 * 
 * @param ip 
 * @return true si es mayor o igual
 * @return false si no es mayor o igual
 */
bool Ip::operator >= (Ip* ip) {
    return (*this > ip) || (*this == ip);
}

/**
 * @brief Comparar si el objeto Ip es menor o igual a otro
 * 
 * @param ip 
 * @return true si es menor o igual
 * @return false si no es menor o igual
 */
bool Ip::operator <= (Ip* ip) {
    return (*this < ip) || (*this == ip);
}

/**
 * @brief Sobrecarga del operador << para imprimir el objeto Ip
 * 
 * @param os 
 * @param ip 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, Ip& ip) {
    os << ip.toString();
    return os;
}

