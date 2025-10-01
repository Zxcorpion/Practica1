#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "VDinamico.h"
#include "PaMedicamento.h"

/**
 * @brief La funcion genera un nuevo vector dinamico donde van las direcciones de memoria de aquellos medicamentos que contengan la subcadena en su nombre
 * @param comp La subcadena a bucar
 * @param vMedicamentos Vector de medicamentos
 * @return Devuelve un vector dinamico con las direcciones de memoria de aquellos medicamentos que contengan la subcadena en su nombre
 */
VDinamico<PaMedicamento*> buscarCompuesto(std::string &comp,VDinamico<PaMedicamento> &vMedicamentos) {
    VDinamico<PaMedicamento*> aux; //creo vector auxiliar para almacenar las d.memoria

    for (int i=0; i < vMedicamentos.tamlog_(); i++) {
        std::string nombreMed = vMedicamentos[i].get_nombre();
        if (nombreMed.find(comp) != std::string::npos) {
            aux.insertar(&vMedicamentos[i]);
        }
    }
    return aux;
}

/**
 * @brief La funcion te ordena el vector dinamico de medicamentos segun su nombre (orden alfabetico)
 * @param vector Vector que queremos ordenar
 * @param tam Tamaño del vector
 * @post El vector queda ordenado segun el orden alfabetico
 */
void ordenaPorNombres(VDinamico<PaMedicamento> &vector) {
    for (int i=0; i < vector.tamlog_()-1; i++) {
        for (int j= 0; j < vector.tamlog_() - i - 1; j++) {

            if (vector[j].get_nombre() > vector[j+1].get_nombre()) {
                PaMedicamento aux = vector[j];
                vector[j] = vector[j+1];
                vector[j+1] = aux;
            }
        }
    }
}


/**
 * @brief La funcion muestra por pantalla los datos de un vector dinamico de medicamentos
 * @param vector Vector del que queremos mostrar los datos
 * @param num Numero de elementos que queremos consultar
 * @post El vector es mostrado
 */
void mostrar(VDinamico<PaMedicamento> &vector, const int &num) {
    for (int i=0;i<num;++i) {
        std::cout<<"Datos de medicamento de la posicion "<<i+1<<std::endl;
        std::cout<<"Numero ID:"<<vector[i].get_id_num()<<std::endl;
        std::cout<<"Numero Alpha:"<<vector[i].get_id_alpha()<<std::endl;
        std::cout<<"Nombre:"<<vector[i].get_nombre()<<std::endl;
        std::cout<<"==============================================================="<<std::endl;
    }
}

/**
 * @brief La funcion muestra por pantalla los datos de un vector dinamico de medicamentos
 * @param vector Vector del que queremos mostrar los datos
 * @param num Numero de elementos que queremos consultar
 * @post El vector es mostrado
 */
void mostrar(VDinamico<PaMedicamento*> &vector, const int &num) {
    for (int i=0;i<num;++i) {
        std::cout<<"Datos de medicamento de la posicion "<<i+1<<std::endl;
        std::cout<<"Numero ID:"<<vector[i]->get_id_num()<<std::endl;
        std::cout<<"Numero Alpha:"<<vector[i]->get_id_alpha()<<std::endl;
        std::cout<<"Nombre:"<<vector[i]->get_nombre()<<std::endl;
        std::cout<<"==============================================================="<<std::endl;
    }
}

/**
 * @brief La funcion guarda el numero de vecs que la primera palabra de un vector se repite
 * @param vMedicamentos Vector dinamico de medicamentos
 * @param tam Tamaño del vector
 * @return El numero de veces que se repite la primera palabra de un medicamento
 */

unsigned long int contadorRepeticiones(VDinamico<PaMedicamento> &vMedicamentos, const int &tam) {
    int cont=0;
    bool encontrado = false;

    for (int i=0; i< tam - 1; i++) {
        std::string nombre, nombre2, corte1, corte2;
        std::stringstream ss,ss2;
        nombre=vMedicamentos[i].get_nombre();
        nombre2=vMedicamentos[i+1].get_nombre();
        ss.str(nombre);
        ss2.str(nombre2);
        getline(ss, corte1, ' ');
        getline(ss2,corte2, ' ');

        if (corte1 == corte2 && encontrado == false) {
            encontrado = true;
            cont++;
        }
        if (corte1 != corte2) {
            encontrado = false;
        }
    }
    return cont;
}

/**
 * @author Pablo Rodríguez Gniadek prg00054@red.ujaen.es
 * @author Marco Díaz Vera mdv00011@red.ujaen.es
 */
int main(int argc, const char * argv[]) {

    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string id_number_string = "";
    std::string id_alpha="";
    std::string nombre="";

    VDinamico<PaMedicamento> vecMeds;

    is.open("../pa_medicamentos.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, id_number_string, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, id_alpha,';');
                getline(columnas, nombre,';');

                int id_number = 0;
                try {
                    id_number = std::stoi(id_number_string); ///Esta funcion pasa de string a int
                }catch (std::invalid_argument &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                PaMedicamento medicamento(id_number,id_alpha,nombre);
                try {
                    vecMeds.insertar(medicamento);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.clear();

                std::cout << ++contador
                          << " Medicamento: ( Id_number=" << id_number
                          << " id_alpha=" << id_alpha << " Nombre=" << nombre
                          << ")" << std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    std::cout << std::endl;

    vecMeds.ordenar();
    mostrar(vecMeds,50);
    //Para buscar en O(log n), hago busqueda binaria
    PaMedicamento meds[5]={(350),(409),(820),(9009),(12370)};
    for (int i=0;i<5;++i) {
        int pos = vecMeds.busquedaBinaria(meds[i]);
        if (pos == -1) {
            std::cout<<"El ID "<<meds[i].get_id_num()<<" no esta en el vector"<<std::endl;
        }else {
            std::cout<<"El ID "<<meds[i].get_id_num()<<" se encuentra en la posicion "<<pos<<" del vector"<<std::endl;

        }
    }

    std::string subcadena="ACEITE";
    VDinamico<PaMedicamento*> nuevovector = buscarCompuesto(subcadena,vecMeds);
    std::cout<<"Medicamentos que contienen aceite: "<<std::endl;
    mostrar(nuevovector,nuevovector.tamlog_());


    ordenaPorNombres(vecMeds);
    mostrar(vecMeds,50);
    std::cout<<contadorRepeticiones(vecMeds,vecMeds.tamlog_());

    return 0;
}