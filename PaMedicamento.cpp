

#include "PaMedicamento.h"
PaMedicamento::PaMedicamento(int id_num_,std::string id_alpha_, std::string nombre_):
id_num(id_num_),
id_alpha(id_alpha_),
nombre(nombre_)

{}


PaMedicamento::PaMedicamento(const PaMedicamento &orig):
id_num(orig.id_num),
id_alpha(orig.id_alpha),
nombre(orig.nombre)
{}

PaMedicamento::~PaMedicamento() {}



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

