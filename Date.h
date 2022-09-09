#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <utility>
#include <string>
#include <map>

/**
 * @brief Clase que representa una fecha, con el mes, día, hora, minuto y segundo
 * 
 */
class Date {
    private:
        int day;
        int hour, minute, second;
        std::pair<std::string, int> month;
    public:
        Date();
        Date(std::string monthDay);
        Date(std::string month, std::string day, std::string hour, std::string minute, std::string second);
        int getDay();
        int getMonthNumber();
        std::string getMonthName();
        int getHour();
        int getMinute();
        int getSecond();
        std::string toString();
        // Sobrecarga de operadores
        bool operator==(Date*);
        bool operator!=(Date*);
        bool operator<(Date*);
        bool operator>(Date*);
        bool operator<=(Date*);
        bool operator>=(Date*);
        friend std::ostream& operator<<(std::ostream&, Date&);
};

#endif