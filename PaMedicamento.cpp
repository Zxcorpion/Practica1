

#include "PaMedicamento.h"
/**
 * @brief Constructor por defecto y parametrizado
 * @param int id_num numero de identificación de medicamento que por defecto es 0
 * @param string id_alpha numero otra forma de identificación del medicamento que por defecto es " "
 * @param string nombre_ numero nombre del medicamento que por defecto es " "
 */
PaMedicamento::PaMedicamento(int id_num_,std::string id_alpha_, std::string nombre_):
id_num(id_num_),
id_alpha(id_alpha_),
nombre(nombre_)

{}

/**
 * @brief Constructor de copia
 * @param orig Objeto que se quiere copiar
 * @post Se crea un nuevo objeto de clase PaMedicamento con los atributos de orig
 */
PaMedicamento::PaMedicamento(const PaMedicamento &orig):
id_num(orig.id_num),
id_alpha(orig.id_alpha),
nombre(orig.nombre)
{}
/**
 * @brief Destructor de la clase PaMedicamento
 */
PaMedicamento::~PaMedicamento() {}


/**
 * @brief Constructor de copia
 * @param orig Objeto que se quiere copiar
 * @post Se crea un nuevo objeto de clase PaMedicamento con los atributos de orig
 */
int PaMedicamento::get_id_num() const {
    return id_num;
}

void PaMedicamento::set_id_num(int id_num) {
    this->id_num = id_num;
}

std::string PaMedicamento::get_id_alpha() const {
    return id_alpha;
}

void PaMedicamento::set_id_alpha(const std::string &id_alpha) {
    this->id_alpha = id_alpha;
}

std::string PaMedicamento::get_nombre() const {
    return nombre;
}

void PaMedicamento::set_nombre(const std::string &nombre) {
    this->nombre = nombre;
}

bool PaMedicamento::operator<(const PaMedicamento &orig) const {
    return id_num < orig.id_num;
}

PaMedicamento &PaMedicamento::operator=(const PaMedicamento &orig) {
    if (this != &orig) {
        id_num = orig.id_num;
        id_alpha = orig.id_alpha;
        nombre = orig.nombre;
    }
    return (*this);
}

bool PaMedicamento::operator==(const PaMedicamento &orig) const {
    return orig.id_num == this->id_num;
}


