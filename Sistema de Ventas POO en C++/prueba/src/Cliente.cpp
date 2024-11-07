#include <iostream>
#include "Entidad.h"
#include "Cliente.h"
#include <fstream>

int Cliente::contadorID = 0;

Cliente::Cliente() : Entidad(TipoEntidad::Cliente) {
    contadorID++;
    idCliente = contadorID;
}

int Cliente::getIdCliente() const {
    return idCliente;
}


void Cliente::ingresarRegistro() {
    crearCliente();
}
void Cliente::listarRegistros(const std::vector<Entidad*>& registros)const {
    mostrarCliente();
}

void Cliente::actualizarRegistro() {
    modificarCliente();
}
/*
void Cliente::eliminar(const std::vector<Entidad*>& registros) const {
    eliminarCliente(dynamic_cast<std:vector<Cliente*>& (registro));
}*/

void Cliente::crearCliente() {
    std::cout << "|| Ingrese el nombre del cliente: ";
    std::cin.ignore();
    std::getline(std::cin, nombre);
    std::cout << "|| Ingrese la fecha de nacimiento del cliente (DD/MM/AAAA): ";
    int dia, mes, anio;
    std::cin >> dia >> mes >> anio;
    Fecha fechaNac;
    fechaNac.setFecha(dia, mes, anio);
    setFechaNacimiento(fechaNac);
    std::cin.ignore();

    bool caracteres_numericos;

    do {
        std::cout << "|| Ingrese el telefono del cliente (10 caracteres): ";
        std::getline(std::cin, telefono);
        if (telefono.length() < 10) {
            std::cout << "|| El telefono debe tener al menos 10 caracteres. Intente nuevamente.\n";
        } else if (telefono.length() > 10) {
            std::cout << "|| El telefono no puede tener mas de 10 caracteres. Intente nuevamente.\n";
        }

        // Reiniciar la variable caracteres_numericos antes de la verificación
        caracteres_numericos = true;

        // Verificar si todos los caracteres son numéricos
        for (char c : telefono) {
            if (!std::isdigit(c)) {
                caracteres_numericos = false;
                break; // No es necesario seguir revisando si se encuentra un carácter no numérico
            }
        }

        if (!caracteres_numericos) {
            std::cout << "|| El telefono solo puede contener caracteres numericos. Intente nuevamente.\n";
        }
    } while (telefono.length() != 10 || !caracteres_numericos);

    std::cout << "|| Ingrese la direccion del cliente: ";
    std::getline(std::cin, direccion);

    std::cout << "|| Ingrese el correo del cliente: ";
    std::getline(std::cin, correo);

    system("cls");
    std::cout << "|| Cliente registrado con exito. ID asignado: " << idCliente << std::endl;
}

void Cliente::mostrarCliente() const {
    std::cout << "|| ID del cliente: " << idCliente << std::endl;
    std::cout << "|| Nombre del cliente: " << nombre << std::endl;
    std::cout << "|| Fecha de nacimiento: " << fechaNacimiento.getFecha() << std::endl;
    std::cout << "|| Telefono del cliente: " << telefono << std::endl;
    std::cout << "|| Direccion del cliente: " << direccion << std::endl;
    std::cout << "|| Correo del cliente: " << correo << std::endl;
}

void Cliente::mostrarCliente(std::ofstream& archivo) const {
    archivo << "|| ID del cliente: " << idCliente << std::endl;
    archivo << "|| Nombre del cliente: " << nombre << std::endl;
    archivo << "|| Fecha de nacimiento: " << fechaNacimiento.getFecha() << std::endl;
    archivo << "|| Telefono del cliente: " << telefono << std::endl;
    archivo << "|| Direccion del cliente: " << direccion << std::endl;
    archivo << "|| Correo del cliente: " << correo << std::endl;
}


void Cliente::modificarCliente() {
    std::cout << "|| Modificar cliente - ID: " << idCliente << std::endl;
    std::cout << "|| Señor usuario recuerde dejar en blanco para mantener el actual dato" << std::endl;


    std::string nuevoNombre;
    std::cout << "|| Ingrese el nuevo nombre del cliente: ";
    std::cin.ignore();
    std::getline(std::cin, nuevoNombre);
    if (!nuevoNombre.empty()) {
        nombre = nuevoNombre;
    }

    std::string nuevaFechaNacimiento;
    std::cout << "|| Ingrese la nueva fecha de nacimiento del cliente (DD/MM/AAAA): ";
    int dia, mes, anio;
    std::cin >> dia >> mes >> anio;
    if (!std::cin.fail()) {
        Fecha nuevaFechaNac;
        nuevaFechaNac.setFecha(dia, mes, anio);
        setFechaNacimiento(nuevaFechaNac);
    } else {
        std::cout << "|| Formato de fecha incorrecto. No se modificó la fecha de nacimiento.\n";
        std::cin.clear();
        std::cin.ignore();
    }


    std::string nuevoTelefono;
    bool caracteres_numericos;
    do {
        std::cout << "|| Ingrese el nuevo telefono del cliente (10 caracteres): ";
        std::getline(std::cin, nuevoTelefono);
        if (nuevoTelefono.length() < 10) {
            std::cout << "|| El telefono debe tener al menos 10 caracteres. Intente nuevamente.\n";
        } else if (nuevoTelefono.length() > 10) {
            std::cout << "|| El telefono no puede tener mas de 10 caracteres. Intente nuevamente.\n";
        }

        // Reiniciar la variable caracteres_numericos antes de la verificación
        caracteres_numericos = true;

        // Verificar si todos los caracteres son numéricos
        for (char c : nuevoTelefono) {
            if (!std::isdigit(c)) {
                caracteres_numericos = false;
                break; // No es necesario seguir revisando si se encuentra un carácter no numérico
            }
        }

        if (!caracteres_numericos) {
            std::cout << "|| El nuevo telefono solo puede contener caracteres numericos. Intente nuevamente.\n";
        }
    } while (nuevoTelefono.length() != 10 || !caracteres_numericos);

    if (!nuevoTelefono.empty()) {
        telefono = nuevoTelefono;
    }

    std::string nuevaDireccion;
    std::cout << "|| Ingrese la nueva direccion del cliente: ";
    std::getline(std::cin, nuevaDireccion);
    if (!nuevaDireccion.empty()) {
        direccion = nuevaDireccion;
    }

    std::string nuevaCorreo;
    std::cout << "|| Ingrese el nuevo correo del cliente: ";
    std::getline(std::cin, nuevaCorreo);
    if (!nuevaCorreo.empty()) {
        correo = nuevaCorreo;
    }

    std::cout << "|| Cliente modificado correctamente." << std::endl;
}

// Función para buscar un cliente por ID y Nombre
bool buscarCliente(const std::vector<Cliente>& clientes, const std::string& criterio, bool buscarPorID, Cliente& clienteEncontrado) {
    for (const Cliente &cliente : clientes) {
        if (buscarPorID) {
            if (cliente.getIdCliente() == std::stoi(criterio)) {
                clienteEncontrado = cliente;
                return true;
            }
        } else {
            if (cliente.getNombre() == criterio) {
                clienteEncontrado = cliente;
                return true;
            }
        }
    }
    return false;
}

void Cliente::eliminarCliente(std::vector<Cliente>& clientes) {
    std::cout << "|| Eliminar cliente - ID: " << idCliente << std::endl;
    std::cout << "|| ¿Esta seguro que desea eliminar este cliente? (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "|| Cliente eliminado correctamente." << std::endl;
        if (clientes.size() == 1) {
            contadorID = 0;
        }
    } else {
        std::cout << "|| Operacion de eliminacion cancelada." << std::endl;
    }
}


