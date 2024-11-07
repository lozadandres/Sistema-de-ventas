#include "Persona.h"

Persona::Persona() {}

void Persona::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Persona::setFechaNacimiento(const Fecha& fecha) {
    fechaNacimiento = fecha;
}

void Persona::setTelefono(const std::string& telefono) {
    this->telefono = telefono;
}

void Persona::setDireccion(const std::string& direccion) {
    this->direccion = direccion;
}

void Persona::setCorreo(const std::string& correo) {
    this->correo = correo;
}

const std::string& Persona::getNombre() const {
    return nombre;
}

const Fecha& Persona::getFechaNacimiento() const {
    return fechaNacimiento;
}

const std::string& Persona::getTelefono() const {
    return telefono;
}

const std::string& Persona::getDireccion() const {
    return direccion;
}

const std::string& Persona::getCorreo() const {
    return correo;
}
