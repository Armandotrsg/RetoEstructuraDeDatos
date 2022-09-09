/**
 * @file act1-3.cpp
 * @author Armando Terrazas Gómez -- A01640924
 *         Oliver Hérnandez Rebollar -- A01641922
 *         Diego Martínez Medrano -- A01634562
 * @brief Programa que parsea un archivo de logs y los ordena por mes y día. El usuario puede elegir 2 fechas
 *       para ver los logs que ocurrieron entre esas fechas y los guarda en un archivo de texto.
 * @version 0.1
 * @date 2022-09-04
 */

#include "DataBase.h"

int main() {
    DataBase* db = new DataBase();
    db->readFile("bitacora.txt"); // Lee el archivo de bitacora.txt

    // Preguntar al usuario las fechas para buscar los logs
    std::cout << "Ingresa una fecha con mes y día (Mmm DD): ";
    std::string date1;
    getline(std::cin, date1);
    std::cout << "Ingresa otra fecha con mes y día (Mmm DD): ";
    std::string date2;
    getline(std::cin, date2);

    // Escribir en un archivo
    try {
        Date* d1 = new Date(date1);
        Date* d2 = new Date(date2);
        db->writeToFile(d1, d2, "bitacoraOrdenada1-3.txt");
    } catch (std::exception& error) {
        std::cerr << error.what() << std::endl;
    }

    return 0;
}

/*
Referencias:

González, L. H., Salinas, E. G., & Cueva, V. M. (2020). Estructura de Datos y
Algoritmos Fundamentales (1.a ed.). Editorial Digital Tecnológico de Monterrey.
*/