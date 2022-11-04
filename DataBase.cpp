#include "DataBase.h"

/**
 * @brief Constructor de la clase DataBase
 * @param fileName- string con el nombre del archivo
 */
DataBase::DataBase(std::string fileName) {
    this->mainTree = new LogsVector();
    readFile(fileName);
}

/**
 * @brief Leer el archivo, lo ordena en un vector con bubble sort y guardar los datos en el árbol teniendo como llave
 *       la cantidad de veces que se repite una IP
 * @param fileName- string con el nombre del archivo
 * @complexity O(n^2)
 */
void DataBase::readFile(std::string fileName) {
    std::ifstream file;
    std::string line;  // line = month day hour:minute:second ip request
    std::string month, day,
        time,  // time = hour:minute:second
        ip, request;

    file.open(fileName);

    if (file.fail()) {
        std::cout << "Error al abrir el archivo" << std::endl;
        exit(1);
    }

    // Create logs vector
    std::vector<Logs*> parse;

    while (file >> month >> day >> time >> ip) {
        getline(file, request);

        if (month.length() == 0) {
            continue;
        }
        if (month.length() > 3) {
            month = month.substr(3, 3);
        }

        Date* date = new Date(month, day, time.substr(0, 2), time.substr(3, 2), time.substr(6, 2));

        // Remove first space
        request = request.substr(1, request.length());
        Logs* logIp = new Logs(date, ip, request);
        parse.push_back(logIp);
    }
    file.close();

    // Sort logs vector by bubble sort
    bool bandera;
    for (int i = 1; i < parse.size(); i++) {
        bandera = false;
        for (int j = 0; j < parse.size() - i; j++) {
            if (*(parse[j + 1]->getIp()) < parse[j]->getIp()) {
                std::swap(parse[j], parse[j + 1]);
                bandera = true;
            }
        }
        if (!bandera) {
            break;
        }
    }

    Logs* current = parse[0];
    int reps = 1;
    for (int i = 1; i < parse.size(); i++) {
        if (*current->getIp() != parse[i]->getIp()) {
            current->setReps(reps);
            this->mainTree->insert(current);
            current = parse[i];
            reps = 1;
        } else {
            reps++;
        }
    }
}

/**
 * @brief Obtiene los n logs que más se repiten
 * @param n- int con la cantidad de logs que se quieren obtener
 * @complexity O(n) en el peor de los casos
 */
void DataBase::getMostRepeated(int n) {
    if (n > this->mainTree->getSize()) {
        n = this->mainTree->getSize();
    } else if (n < 1) {
        throw std::invalid_argument("n debe ser mayor a 0");
    }
    std::vector<Logs*> topRepeated;
    getMostRepeated(n, this->mainTree->getRoot(), topRepeated);
    for (int i = 0; i < topRepeated.size(); i++) {
        std::cout << i + 1 << ". " << topRepeated[i]->getIp()->toStringWithoutPort() << " Repeticiones: " << topRepeated[i]->repeat << std::endl;
    }
}

/**
 * @brief Obtiene los n logs que más se repiten
 * @param n- int con la cantidad de logs que se quieren obtener
 * @param current- Logs* con el nodo actual
 * @param vec- vector de Logs* con los logs que más se repiten
 * @complexity O(n) en el peor de los casos
 */
void DataBase::getMostRepeated(int n, Logs* current, std::vector<Logs*>& vec) {
    if (current != nullptr) {
        getMostRepeated(n, current->right, vec);
        if (vec.size() < n) {
            vec.push_back(current);
        } else {
            return;
        }
        getMostRepeated(n, current->left, vec);
    }
}
