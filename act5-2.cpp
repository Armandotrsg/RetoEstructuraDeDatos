/**
 * @file act3-4.cpp
 * @author Armando Terrazas Gómez -- A01640924
 *         Oliver Hérnandez Rebollar -- A01641922
 *         Diego Martínez Medrano -- A01634562
 * @brief Programa que parsea un archivo de logs y los ordena por medio de una tabla hash
 *       siendo la llave el ip del log
 * @version 0.3
 * @date 29-11-2022
 */

#include "DataBase.h"

int main() {
    DataBase* db = new DataBase();
    db->readFile("bitacora3-1.txt");
    db->print("10.15.176.227");

    return 0;
}

/*
Referencias:

González, L. H., Salinas, E. G., & Cueva, V. M. (2020). Estructura de Datos y
Algoritmos Fundamentales (1.a ed.). Editorial Digital Tecnológico de Monterrey.

toboqus. (s. f.). BST in C++ with templates. Gist.
Recuperado 14 de octubre de 2022, de https://gist.github.com/toboqus/7a7b3d334c9ac59f3d5a
*/