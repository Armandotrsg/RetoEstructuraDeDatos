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
    std::cout << "Ingresa una fecha con mes y día (MMM DD): ";
    std::string date1;
    getline(std::cin, date1);
    std::cout << "Ingresa otra fecha con mes y día (MMM DD): ";
    std::string date2;
    getline(std::cin, date2);
    //Write to file
    try{
        Date* d1 = new Date(date1);
        Date* d2 = new Date(date2);
        db->writeToFile(d1, d2, "bitacoraOrdenada1-3.txt");
    } catch (std::exception& error) {
        std::cerr << error.what() << std::endl;
    }
    

    
    
    
    return 0;
}
