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
 * @brief Encuentra el pivote para el quicksort
 * 
 * @param vec- std::vector<Log*> con los logs a ordenar 
 * @param inicio- int con el índice del primer elemento del vector 
 * @param fin- int con el índice del último elemento del vector 
 * 
 * @return int Con la posición del pivote
 */
int DataBase::partition(std::vector<Logs*>& vec, int inicio, int fin){
    Logs* p = vec[inicio];
    int i = inicio+1;
    
    for (int j = i; j <= fin; j++){
        if (*vec[j]->getIp() < p->getIp()){
            std::swap(vec[i], vec[j]);
            i++;
        }
    }
    std::swap(vec[inicio], vec[i-1]);
    return i-1;
}

// * (toboqus, s. f.)

/**
 * @brief Ordena un vector de logs por medio del quicksort
 * 
 * @param vec- std::vector<Log*> con los logs a ordenar 
 * @param inicio- int con el índice del primer elemento del vector 
 * @param fin- int con el índice del último elemento del vector
 * @complexity O(n log n) 
 */
void DataBase::quickSort(std::vector<Logs*>& vec) {
    quickSort(vec, 0, vec.size()-1);
}

/**
 * @brief Ordena un vector de logs por medio del quicksort
 * 
 * @param vec- std::vector<Log*> con los logs a ordenar 
 * @param inicio- int con el índice del primer elemento del vector 
 * @param fin- int con el índice del último elemento del vector 
 */
void DataBase::quickSort(std::vector<Logs*>& vec, int inicio, int fin){
    if (inicio < fin){
        int posPiv =  partition(vec, inicio, fin);
        quickSort(vec, inicio, posPiv-1);
        quickSort(vec, posPiv+1, fin);
    }
}

// * (toboqus, s. f.)

/**
 * @brief Leer el archivo, lo ordena en un vector con quick sort y guardar los datos en el árbol teniendo como llave
 *       la cantidad de veces que se repite una IP
 * @param fileName- string con el nombre del archivo
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

    quickSort(parse);
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
