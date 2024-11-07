#include <iostream>
#include <fstream> // Asegúrate de incluir este encabezado para ifstream
#include <sstream>
#include "Proveedor.h"

int Proveedor::contadorID = 0;

Proveedor::Proveedor() /*: Entidad(TipoEntidad::Proveedor)*/ {
    contadorID++;
    idProveedor = contadorID;
}

int Proveedor::getIdProveedor() const {
    return idProveedor;
}

std::string Proveedor::getRut() const {
    return rut;
}

/*void Proveedor::ingresarRegistro() {
    crearProveedor();
}
void Proveedor::listarRegistros(const std::vector<Entidad*>& registros)const {
    mostrarProveedor();
}
void Proveedor::actualizarRegistro() {
    modificarProveedor();
}
void Proveedor::eliminar(const std::vector<Entidad*>& registros) const {
    eliminarProveedor(dynamic_cast<std:vector<Proveedor*>& (registro));
}*/

void Proveedor::mostrarProductosProveedor() const {
    if (idProveedor == 1) { // Solo el primer proveedor leerá y mostrará los productos
        std::cout << "||----------------------------------------------------------------------------------" << std::endl;
        cout << "|| Listado de Productos del Proveedor:\n";
        std::cout << "||----------------------------------------------------------------------------------" << std::endl;
        std::ifstream archivo("productosproveedor.csv", std::ios::in);

        if (!archivo) {
            cerr << "|| Error al abrir el archivo de productos del proveedor\n";
        } else {
            cout << "|| Archivo de productos del proveedor abierto con exito\n";
            string id, nombre, marca, clasificacion, cantidad, precio, fechaVencimiento;
            string registro;

            // Omitir la primera fila
            getline(archivo, registro);

            while (getline(archivo, registro)) {
                std::stringstream token(registro);
                getline(token, id, ';');
                getline(token, nombre, ';');
                getline(token, marca, ';');
                getline(token, clasificacion, ';');
                getline(token, cantidad, ';');
                getline(token, precio, ';');
                getline(token, fechaVencimiento, ';');

                cout << "\n|| ID: " << id << endl;
                cout << "|| Nombre: " << nombre << endl;
                cout << "|| Marca: " << marca << endl;
                cout << "|| Clasificacion: " << clasificacion << endl;
                cout << "|| Cantidad: " << cantidad << endl;
                cout << "|| Precio: " << precio << endl;
                cout << "|| Fecha de vencimiento: " << fechaVencimiento << endl;
                std::cout << "||----------------------------------------------------------------------------------" << std::endl;
            }
            archivo.close();
        }
    }
}


void Proveedor::crearProveedor() {
    std::cout << "|| Ingrese el RUT del proveedor: ";
    std::cin.ignore();
    std::getline(std::cin, rut);

    std::cout << "|| Ingrese el nombre del proveedor: ";
    std::getline(std::cin, nombre);

    std::cout << "|| Ingrese la fecha de nacimiento del proveedor (DD/MM/AAAA): ";
    int dia, mes, anio;
    std::cin >> dia >> mes >> anio;
    Fecha fechaNac;
    fechaNac.setFecha(dia, mes, anio);
    setFechaNacimiento(fechaNac);
    std::cin.ignore();

    bool caracteres_numericos;

    do {
        std::cout << "|| Ingrese el telefono del proveedor (10 caracteres): ";
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

    std::cout << "|| Ingrese la direccion del proveedor: ";
    std::getline(std::cin, direccion);

    std::cout << "|| Ingrese el correo del proveedor: ";
    std::getline(std::cin, correo);

    std::cout << "|| Ingrese el tipo de producto del proveedor: ";
    std::getline(std::cin, tipoProducto);

    system("cls");
    std::cout << "|| Proveedor registrado con exito. ID asignado: " << idProveedor << std::endl;
}

void Proveedor::mostrarProveedor() const {
    std::cout << "|| ID del proveedor: " << idProveedor << std::endl;
    std::cout << "|| RUT del proveedor: " << rut << std::endl;
    std::cout << "|| Nombre del proveedor: " << nombre << std::endl;
    std::cout << "|| Fecha de nacimiento: " << fechaNacimiento.getFecha() << std::endl;
    std::cout << "|| Telefono del proveedor: " << telefono << std::endl;
    std::cout << "|| Direccion del proveedor: " << direccion << std::endl;
    std::cout << "|| Correo del proveedor: " << correo << std::endl;
    std::cout << "|| Tipo de producto del proveedor: " << tipoProducto << std::endl;
    // Llamar a la función para mostrar productos solo para el primer proveedor
    if (idProveedor == 1) {
        mostrarProductosProveedor();
    }
}

void Proveedor::modificarProveedor() {
    std::cout << "|| Modificar proveedor - ID: " << idProveedor << std::endl;
    std::cout << "|| Señor usuario recuerde dejar en blanco para mantener el actual dato" << std::endl;

    std::string nuevoRut;
    std::cout << "|| Ingrese el nuevo RUT del proveedor: ";
    std::getline(std::cin, nuevoRut);
    if (!nuevoRut.empty()) {
        rut = nuevoRut;
    }

    std::string nuevoNombre;
    std::cout << "|| Ingrese el nuevo nombre del proveedor: ";
    std::cin.ignore();
    std::getline(std::cin, nuevoNombre);
    if (!nuevoNombre.empty()) {
        nombre = nuevoNombre;
    }

    std::string nuevaFechaNacimiento;
    std::cout << "|| Ingrese la nueva fecha de nacimiento del proveedor (DD/MM/AAAA): ";
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
        std::cout << "|| Ingrese el nuevo telefono del proveedor (10 caracteres): ";
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
    std::cout << "|| Ingrese la nueva direccion del proveedor: ";
    std::getline(std::cin, nuevaDireccion);
    if (!nuevaDireccion.empty()) {
        direccion = nuevaDireccion;
    }

    std::string nuevoCorreo;
    std::cout << "|| Ingrese el nuevo correo del proveedor: ";
    std::getline(std::cin, nuevoCorreo);
    if (!nuevoCorreo.empty()) {
        correo = nuevoCorreo;
    }

    std::string nuevoTipoProducto;
    std::cout << "|| Ingrese el nuevo tipo de producto del proveedor: ";
    std::getline(std::cin, nuevoTipoProducto);
    if (!nuevoTipoProducto.empty()) {
        tipoProducto = nuevoTipoProducto;
    }

    std::cout << "|| Proveedor modificado correctamente." << std::endl;
}

bool buscarProveedor(const std::vector<Proveedor>& proveedores, const std::string& criterio, bool buscarPorID, Proveedor& proveedorEncontrado) {
    for (const Proveedor& proveedor : proveedores) {
        if (buscarPorID) {
            if (proveedor.getIdProveedor() == std::stoi(criterio)) {
                proveedorEncontrado = proveedor;
                return true;
            }
        } else {
            if (proveedor.getNombre() == criterio) {
                proveedorEncontrado = proveedor;
                return true;
            }
        }
    }
    return false;
}

void Proveedor::eliminarProveedor(std::vector<Proveedor>& proveedores) {
    std::cout << "|| Eliminar proveedor - ID: " << idProveedor << std::endl;
    std::cout << "|| ¿Esta seguro que desea eliminar este proveedor? (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "|| Proveedor eliminado correctamente." << std::endl;
        if (proveedores.size() == 1) {
            contadorID = 0;
        }
    } else {
        std::cout << "|| Operacion de eliminacion cancelada." << std::endl;
    }
}
