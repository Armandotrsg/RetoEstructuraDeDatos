#include "Date.h"

/**
 * @brief Constructor default de la clase Date
 * 
 */
Date::Date() {
    this->day = 0;
    this->month = std::pair<std::string, int>{"", 0};
    this->hour = 0;
    this->minute = 0;
    this->second = 0;
};
/**
 * @brief Constructor de la clase Date
 * 
 * @param month- string con el mes de 3 letras
 * @param day- string con el día
 * @param hour- string con la hora
 * @param minute- string con el minuto
 * @param second- string con el segundo
 */
Date::Date(std::string month, std::string day, std::string hour, std::string minute, std::string second) {
    this->month.first = month;
    this->month.second = this->MONTHS.at(month);
    this->day = std::stoi(day);
    this->hour = std::stoi(hour);
    this->minute = std::stoi(minute);
    this->second = std::stoi(second);
};

/**
 * @brief Obtener el día
 * 
 * @return int con el día 
 */
int Date::getDay() {
    return this->day;
};

/**
 * @brief Obtener el número del mes
 * 
 * @return int con el número del mes
 */
int Date::getMonthNumber() {
    return this->month.second;
};

/**
 * @brief Obtener el nombre del mes
 * 
 * @return string con el nombre del mes
 */
std::string Date::getMonthName() {
    return this->month.first;
};

/**
 * @brief Obtener la hora
 * 
 * @return int con la hora
 */
int Date::getHour() {
    return this->hour;
};

/**
 * @brief Obtener el minuto
 * 
 * @return int con el minuto
 */
int Date::getMinute() {
    return this->minute;
};

/**
 * @brief Obtener el segundo
 * 
 * @return int con el segundo
 */
int Date::getSecond() {
    return this->second;
};

/**
 * @brief Sobrecarga del operador ==
 * 
 * @param date- objeto Date con el que se va a comparar
 * @return true si son iguales
 * @return false si no son iguales
 */
bool Date::operator==(Date* date) {
    return this->month.second == date->getMonthNumber() && this->day == date->getDay() && this->hour == date->getHour() &&
           this->minute == date->getMinute() && this->second == date->getSecond();
};

/**
 * @brief Sobrecarga del operador !=
 * 
 * @param date- objeto Date con el que se va a comparar
 * @return true si son diferentes
 * @return false si son iguales
 */
bool Date::operator!=(Date* date) {
    return !(*this == date);
};

/**
 * @brief Sobrecarga del operador <
 * 
 * @param date- objeto Date con el que se va a comparar
 * @return true si es menor
 * @return false si no es menor
 */
bool Date::operator<(Date* date) {
    if (this->getMonthNumber() < date->getMonthNumber()){
        return true;
    } else if (this->getMonthNumber() == date->getMonthNumber()){
        if (this->getDay() < date->getDay()){
            return true;
        } else if (this->getDay() == date->getDay()){
            if (this->getHour() < date->getHour()){
                return true;
            } else if (this->getHour() == date->getHour()){
                if (this->getMinute() < date->getMinute()){
                    return true;
                } else if (this->getMinute() == date->getMinute()){
                    if (this->getSecond() < date->getSecond()){
                        return true;
                    }
                }
            }
        }
    }
    return false;
};

/**
 * @brief Sobrecarga del operador >
 * 
 * @param date- objeto Date con el que se va a comparar
 * @return true si es mayor
 * @return false si no es mayor
 */
bool Date::operator>(Date* date) {
    return !(*this < date) && !(*this == date);
};

/**
 * @brief Sobrecarga del operador <=
 * 
 * @param date- objeto Date con el que se va a comparar
 * @return true si es menor o igual
 * @return false si no es menor o igual
 */
bool Date::operator<=(Date* date) {
    return *this < date || *this == date;
};

/**
 * @brief Sobrecarga del operador >=
 * 
 * @param date- objeto Date con el que se va a comparar
 * @return true si es mayor o igual
 * @return false si no es mayor o igual
 */
bool Date::operator>=(Date* date) {
    return *this > date || *this == date;
};

/**
 * @brief Sobrecarga del operador <<
 * 
 * @param os- objeto ostream
 * @param date- objeto Date
 * @return ostream& 
 */
std::ostream& operator<<(std::ostream& os, Date& date) {
    os << date.getMonthName() << " " << date.day << ", " << date.hour << ":" << date.minute << ":" << date.second;
    return os;
}