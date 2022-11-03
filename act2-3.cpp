/**
 * @file act1-3.cpp
 * @author Armando Terrazas Gómez -- A01640924
 *         Oliver Hérnandez Rebollar -- A01641922
 *         Diego Martínez Medrano -- A01634562
 * @brief Programa que parsea un archivo de logs y los ordena por mes y día. El usuario puede elegir 2 fechas
 *       para ver los logs que ocurrieron entre esas fechas y los guarda en un archivo de texto.
 * @version 0.2
 * @date 08-10-2022
 */

#include "DataBase.h"

int main() {
    DataBase *db = new DataBase("bitacora2.txt");
    db->printByReps(38);

    return 0;
}

/*
Referencias:

González, L. H., Salinas, E. G., & Cueva, V. M. (2020). Estructura de Datos y
Algoritmos Fundamentales (1.a ed.). Editorial Digital Tecnológico de Monterrey.
*/