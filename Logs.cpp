#include "Logs.h"

/**
 * @brief Constructor default de la clase Logs
 *
 */
Logs::Logs() {
    this->date = new Date();
    this->ip = new Ip();
    this->request = "";
    this->next = nullptr;
};

/**
 * @brief Constructor de la clase Logs
 *
 * @param date- apuntador de un objeto Date
 * @param ip- string con el ip
 * @param request- string con el request
 */
Logs::Logs(Date* date, std::string ip, std::string request) {
    this->date = date;
    this->ip = new Ip(ip);
    this->request = request;
    this->next = nullptr;
}

/**
 * @brief Obtener el objeto Date
 *
 * @return Date* con el objeto Date
 */
Date* Logs::getDate() {
    return this->date;
}

/**
 * @brief Obtener el ip
 *
 * @return string con el ip
 */
Ip* Logs::getIp() {
    return this->ip;
}

/**
 * @brief Obtener el request
 *
 * @return string con el request
 */
std::string Logs::getRequest() {
    return this->request;
}

/**
 * @brief Obtener un string con la información del objeto Logs
 *
 * @return string con la información del objeto Logs
 */
std::string Logs::toString() {
    return this->date->toString() + " " + this->ip->toString() + " " + this->request;
}

/**
 * @brief Sobrecarga del operador <<
 *
 * @param os- ostream
 * @param log- objeto Logs
 * @return ostream&
 */
std::ostream& operator<<(std::ostream& os, Logs& logs) {
    os << *logs.date << " " << *logs.ip << " " << logs.request;
    return os;
}
