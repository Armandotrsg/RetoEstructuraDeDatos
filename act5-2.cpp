/**
 * @file act5-2.cpp
 * @author Armando Terrazas Gómez -- A01640924
 *         Oliver Hérnandez Rebollar -- A01641922
 *         Diego Martínez Medrano -- A01634562
 * @brief Programa que parsea un archivo de logs y los ordena por medio de una tabla hash
 *       siendo la llave el ip del log
 * @version 0.4
 * @date 29-11-2022
 */

#include "DataBase.h"

int main() {
    DataBase* db = new DataBase();
    db->readFile("bitacora3-1.txt");
    char option;
    std::string key;
    do {
        std::cout << "\nIngresa la ip que deseas buscar (Formato: XXX.XXX.XXX.XXX): ";
        std::cin >> key;
        try {
            db->print(key);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << "Deseas buscar otra ip? (s/n): ";
        std::cin >> option;
    } while (option == 's');

    return 0;
}

/*
Referencias:

González, L. H., Salinas, E. G., & Cueva, V. M. (2020). Estructura de Datos y
Algoritmos Fundamentales (1.a ed.). Editorial Digital Tecnológico de Monterrey.
*/