/**
 * @file act1-3.cpp
 * @author Armando Terrazas Gómez -- A01640924
 *         Oliver Hérnandez Rebollar -- A01641922
 *         Diego Martínez Medrano -- A01634562
 * @brief Programa que parsea un archivo de logs y los ordena por mes y día. El usuario puede elegir 2 fechas
 *       para ver los logs que ocurrieron entre esas fechas y los guarda en un archivo de texto.
 * @version 0.3
 * @date 08-10-2022
 */

#include "DataBase.h"

int main() {
    DataBase* db = new DataBase("bitacora3.txt");

    char option;
    do {
        std::cout << "\nIngresa el número de logs que quieres ver que más se repitan: ";
        int n;
        std::cin >> n;
        try {
            db->getMostRepeated(n);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        std::cout << "¿Quieres ver más logs? (s/n): ";
        std::cin >> option;
    } while (option != 'n');

    return 0;
}

/*
Referencias:

González, L. H., Salinas, E. G., & Cueva, V. M. (2020). Estructura de Datos y
Algoritmos Fundamentales (1.a ed.). Editorial Digital Tecnológico de Monterrey.

toboqus. (s. f.). BST in C++ with templates. Gist.
Recuperado 14 de octubre de 2022, de https://gist.github.com/toboqus/7a7b3d334c9ac59f3d5a
*/