/**
 * @file act1-3.cpp
 * @author Armando Terrazas Gómez -- A01640924
 *         Oliver Rebollar
 *         Diego
 * @brief Programa que parsea un archivo de logs y los ordena por mes y día. El usuario puede elegir 2 fechas
 *       para ver los logs que ocurrieron entre esas fechas y los guarda en un archivo de texto.
 * @version 0.1
 * @date 2022-09-04
 * 
 */

#include "DataBase.h"

int main() {
    /* DataBase db;
    db.readFile("bitacora.txt");
    std::cout << *db["Sep"] << std::endl; */
    DataBase* db = new DataBase();
    db->readFile("bitacora.txt");
    //Count every slot in the map
    std::cout << "Jan: " << db->at("Jan")->getLogs().size() << std::endl;
    std::cout << "Feb: " << db->at("Feb")->getLogs().size() << std::endl;
    std::cout << "Mar: " << db->at("Mar")->getLogs().size() << std::endl;
    std::cout << "Apr: " << db->at("Apr")->getLogs().size() << std::endl;
    std::cout << "May: " << db->at("May")->getLogs().size() << std::endl;
    std::cout << "Jun: " << db->at("Jun")->getLogs().size() << std::endl;
    std::cout << "Jul: " << db->at("Jul")->getLogs().size() << std::endl;
    std::cout << "Aug: " << db->at("Aug")->getLogs().size() << std::endl;
    std::cout << "Sep: " << db->at("Sep")->getLogs().size() << std::endl;
    std::cout << "Oct: " << db->at("Oct")->getLogs().size() << std::endl;
    std::cout << "Nov: " << db->at("Nov")->getLogs().size() << std::endl;
    std::cout << "Dec: " << db->at("Dec")->getLogs().size() << std::endl;

    
    return 0;
}
