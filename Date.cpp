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
 * @brief Constructor de la clase Date para cuando el usuario ingrese el mes y día que busca
 * 
 * @param monthDay-string con el mes y el día: "Jan 1" o "Feb 22"
 */
Date::Date(std::string monthDay) {
    //Verificar que el string ingresado tenga el formato correcto
    if (monthDay.length() < 5) {
        throw std::invalid_argument("El formato del mes y día es incorrecto");
    }
    //Verificar que haya un espacio entre el mes y el día
    if (monthDay[3] != ' ') {
        throw std::invalid_argument("El formato del mes y día es incorrecto");
    }
    std::string month = monthDay.substr(0, 3);
    std::string day = monthDay.substr(4, monthDay.length());
    //Verificar que el mes sea válido
    if (month == "Jan") {
        this->month = std::pair<std::string, int>{"Jan", 1};
    } else if (month == "Feb") {
        this->month = std::pair<std::string, int>{"Feb", 2};
    } else if (month == "Mar") {
        this->month = std::pair<std::string, int>{"Mar", 3};
    } else if (month == "Apr") {
        this->month = std::pair<std::string, int>{"Apr", 4};
    } else if (month == "May") {
        this->month = std::pair<std::string, int>{"May", 5};
    } else if (month == "Jun") {
        this->month = std::pair<std::string, int>{"Jun", 6};
    } else if (month == "Jul") {
        this->month = std::pair<std::string, int>{"Jul", 7};
    } else if (month == "Aug") {
        this->month = std::pair<std::string, int>{"Aug", 8};
    } else if (month == "Sep") {
        this->month = std::pair<std::string, int>{"Sep", 9};
    } else if (month == "Oct") {
        this->month = std::pair<std::string, int>{"Oct", 10};
    } else if (month == "Nov") {
        this->month = std::pair<std::string, int>{"Nov", 11};
    } else if (month == "Dec") {
        this->month = std::pair<std::string, int>{"Dec", 12};
    } else {
        throw std::invalid_argument("El mes no es válido");
    }
    this->day = std::stoi(day);
    //Verificamos que el día sea válido
    if (this->day < 1 || this->day > 31) {
        throw std::invalid_argument("El día no es válido");
    }
    this->hour = 0;
    this->minute = 0;
    this->second = 0;
}

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
 * @brief Transforma el objeto Date a un string
 * 
 * @return std::string 
 */
std::string Date::toString() {
    std::string dayNum = std::to_string(this->day);
    std::string hourNum = std::to_string(this->hour);
    std::string minuteNum = std::to_string(this->minute);
    std::string secondNum = std::to_string(this->second);
    if (dayNum.length() == 1) {
        dayNum = "0" + dayNum;
    }
    if (hourNum.length() == 1) {
        hourNum = "0" + hourNum;
    }
    if (minuteNum.length() == 1) {
        minuteNum = "0" + minuteNum;
    }
    if (secondNum.length() == 1) {
        secondNum = "0" + secondNum;
    }
    return this->month.first + " " + dayNum + " " + hourNum + ":" + minuteNum + ":" + secondNum;
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
    os << date.toString();
    return os;
}