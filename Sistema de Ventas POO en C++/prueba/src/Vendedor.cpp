#include <iostream>
#include "Vendedor.h"
#include <fstream>

int Vendedor::contadorID = 0;

Vendedor::Vendedor() : Entidad(TipoEntidad::Vendedor) {
    contadorID++;
    idVendedor = contadorID;
}

int Vendedor::getIdVendedor() const {
    return idVendedor;
}


void Vendedor::ingresarRegistro() {
    crearVendedor();
}
void Vendedor::listarRegistros(const std::vector<Entidad*>& registros)const {
    mostrarVendedor();
}
void Vendedor::actualizarRegistro() {
    modificarVendedor();
}


/*void Vendedor::eliminarRegistro(const std::vector<Entidad*>& registros) const {
    eliminarVendedor(dynamic_cast<std:vector<Vendedor*>& (registro));
}*/

void Vendedor::crearVendedor() {
    std::cout << "|| Ingrese el nombre del vendedor: ";
    std::cin.ignore();
    std::getline(std::cin, nombre);

    std::cout << "|| Ingrese la fecha de nacimiento del vendedor (DD/MM/AAAA): ";
    int dia, mes, anio;
    std::cin >> dia >> mes >> anio;
    Fecha fechaNac;
    fechaNac.setFecha(dia, mes, anio);
    setFechaNacimiento(fechaNac);
    std::cin.ignore();

    bool caracteres_numericos;

    do {
        std::cout << "|| Ingrese el telefono del vendedor (10 caracteres): ";
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

    std::cout << "|| Ingrese la direccion del vendedor: ";
    std::getline(std::cin, direccion);

    std::cout << "|| Ingrese el correo del vendedor: ";
    std::getline(std::cin, correo);

    std::cout << "|| Ingrese el area del vendedor: ";
    std::getline(std::cin, area);

    system("cls");
    std::cout << "|| Vendedor registrado con exito. ID asignado: " << idVendedor << std::endl;
}

void Vendedor::mostrarVendedor() const {
    std::cout << "|| ID del vendedor: " << idVendedor << std::endl;
    std::cout << "|| Nombre del vendedor: " << nombre << std::endl;
    std::cout << "|| Fecha de nacimiento: " << fechaNacimiento.getFecha() << std::endl;
    std::cout << "|| Telefono del vendedor: " << telefono << std::endl;
    std::cout << "|| Direccion del vendedor: " << direccion << std::endl;
    std::cout << "|| Correo del vendedor: " << correo << std::endl;
    std::cout << "|| Area del vendedor: " << area << std::endl;
}

void Vendedor::mostrarVendedor(std::ofstream& archivo) const {
    archivo << "|| ID del vendedor: " << idVendedor << std::endl;
    archivo << "|| Nombre del vendedor: " << nombre << std::endl;
    archivo << "|| Fecha de nacimiento: " << fechaNacimiento.getFecha() << std::endl;
    archivo << "|| Telefono del vendedor: " << telefono << std::endl;
    archivo << "|| Direccion del vendedor: " << direccion << std::endl;
    archivo << "|| Correo del vendedor: " << correo << std::endl;
    archivo << "|| Area del vendedor: " << area << std::endl;
}

void Vendedor::modificarVendedor() {
    std::cout << "|| Modificar vendedor - ID: " << idVendedor << std::endl;
    std::cout << "|| Señor usuario recuerde dejar en blanco para mantener el actual dato" << std::endl;

    std::string nuevoNombre;
    std::cout << "|| Ingrese el nuevo nombre del vendedor: ";
    std::cin.ignore();
    std::getline(std::cin, nuevoNombre);
    if (!nuevoNombre.empty()) {
        nombre = nuevoNombre;
    }

    std::string nuevaFechaNacimiento;
    std::cout << "|| Ingrese la nueva fecha de nacimiento del vendedor (DD/MM/AAAA): ";
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
        std::cout << "|| Ingrese el nuevo telefono del vendedor (10 caracteres): ";
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
    std::cout << "|| Ingrese la nueva direccion del vendedor: ";
    std::getline(std::cin, nuevaDireccion);
    if (!nuevaDireccion.empty()) {
        direccion = nuevaDireccion;
    }

    std::string nuevoCorreo;
    std::cout << "|| Ingrese el nuevo correo del vendedor: ";
    std::getline(std::cin, nuevoCorreo);
    if (!nuevoCorreo.empty()) {
        correo = nuevoCorreo;
    }

    std::string nuevaArea;
    std::cout << "|| Ingrese la nueva area del vendedor: ";
    std::getline(std::cin, nuevaArea);
    if (!nuevaArea.empty()) {
        area = nuevaArea;
    }

    std::cout << "|| Vendedor modificado correctamente." << std::endl;
}

bool buscarVendedor(const std::vector<Vendedor>& vendedores, const std::string& criterio, bool buscarPorID, Vendedor& vendedorEncontrado) {
    for (const Vendedor& vendedor : vendedores) {
        if (buscarPorID) {
            if (vendedor.getIdVendedor() == std::stoi(criterio)) {
                vendedorEncontrado = vendedor;
                return true;
            }
        } else {
            if (vendedor.getNombre() == criterio) {
                vendedorEncontrado = vendedor;
                return true;
            }
        }
    }
    return false;
}

void Vendedor::eliminarVendedor(std::vector<Vendedor>& vendedores) {
    std::cout << "|| Eliminar vendedor - ID: " << idVendedor << std::endl;
    std::cout << "|| ¿Esta seguro que desea eliminar este vendedor? (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "|| Vendedor eliminado correctamente." << std::endl;
        if (vendedores.size() == 1) {
            contadorID = 0;
        }
    } else {
        std::cout << "|| Operacion de eliminacion cancelada." << std::endl;
    }
}

