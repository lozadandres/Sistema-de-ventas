#include <iostream>
#include "Producto.h"
#include <iomanip>
#include <fstream>
#include <ctime>
#include <chrono>

int Producto::contadorID = 0;

Producto::Producto() : Entidad(TipoEntidad::Producto) {
    contadorID++;
    idProducto = contadorID;
}

void Producto::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Producto::setMarca(const std::string& marca) {
    this->marca = marca;
}

void Producto::setClasificacion(const std::string& clasificacion) {
    this->clasificacion = clasificacion;
}

void Producto::setCantidad(int cantidad) {
    this->cantidad = cantidad;
}

void Producto::setPrecioVenta(float precio) {
    precioVenta = precio;
}

void Producto::setFechaVencimiento(const Fecha& fecha) {
    fechaVencimiento = fecha;
}

int Producto::getIdProducto() const {
    return idProducto;
}

const std::string& Producto::getNombre() const {
    return nombre;
}

const std::string& Producto::getMarca() const {
    return marca;
}

const std::string& Producto::getClasificacion() const {
    return clasificacion;
}

int Producto::getCantidad() const {
    return cantidad;
}

float Producto::getPrecioVenta() const {
    return precioVenta;
}

const Fecha& Producto::getFechaVencimiento() const {
    return fechaVencimiento;
}

void Producto::ingresarRegistro() {
    crearProducto();
}
void Producto::listarRegistros(const std::vector<Entidad*>& registros)const {
    mostrarProducto();
}
void Producto::actualizarRegistro() {
    modificarProducto();
}
/*
void Producto::eliminar(const std::vector<Entidad*>& registros) const {
    eliminarProducto(dynamic_cast<std:vector<Producto*>& (registro));
}*/

void Producto::crearProducto() {
    std::cout << "|| Ingrese el nombre del producto: ";
    std::cin.ignore();
    std::getline(std::cin, nombre);
    std::cout << "|| Ingrese la marca del producto: ";
    std::getline(std::cin, marca);
    std::cout << "|| Ingrese la clasificacion del producto: ";
    std::getline(std::cin, clasificacion);
    std::cout << "|| Ingrese la cantidad inicial del producto: ";
    std::cin >> cantidad;
    std::cout << "|| Ingrese el precio de venta del producto: $";
    std::cin >> precioVenta;
    std::cout << "|| Ingrese la fecha de vencimiento del producto (DD/MM/AAAA): ";
    std::cin.ignore();
    int dia, mes, anio;
    std::cin >> dia >> mes >> anio;
    Fecha fechaVen;
    fechaVen.setFecha(dia, mes, anio);
    setFechaVencimiento(fechaVen);

    // Obtener la fecha actual
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* current_time = std::localtime(&now_time);
    int currentDay = current_time->tm_mday;
    int currentMonth = current_time->tm_mon + 1; // Se suma 1 ya que los meses se cuentan desde 0
    int currentYear = current_time->tm_year + 1900; // Se suma 1900 ya que tm_year cuenta los años desde 1900

    // Establecer el estado del producto
    if (cantidad > 0) {
        estado = DISPONIBLE;
        disponible = true;
    } else {
        estado = AGOTADO;
        disponible = false;
    }

    // Calcular si la fecha de vencimiento es igual a la fecha actual
    if (fechaVencimiento.getDia() == currentDay && fechaVencimiento.getMes() == currentMonth && fechaVencimiento.getAnio() == currentYear) {
        estado = POR_VENCER;
    } else if (fechaVencimiento.getAnio() < currentYear || (fechaVencimiento.getAnio() == currentYear && fechaVencimiento.getMes() < currentMonth) || (fechaVencimiento.getAnio() == currentYear && fechaVencimiento.getMes() == currentMonth && fechaVencimiento.getDia() < currentDay)) {
        estado = VENCIDO;
    }

     system("cls");
     std::cout << "|| Producto registrado con exito. ID asignado: " << idProducto << std::endl;

    /*std::ifstream archivoCSV_lectura("productos.csv"); // Abrir el archivo CSV en modo de lectura
    std::ofstream archivoCSV_escritura("productos.csv", std::ios::app); // Abrir el archivo CSV en modo de añadir al final
    if (archivoCSV_lectura.is_open() && archivoCSV_escritura.is_open()) {
        // Validar si el ID ya existe
        std::string linea;
        int ultimoID = 0;
        while (std::getline(archivoCSV_lectura, linea)) {
            std::istringstream ss(linea);
            std::string idStr;
            std::getline(ss, idStr, ',');
            int id = std::stoi(idStr);
            if (id > ultimoID) {
                ultimoID = id;
            }
        }
        archivoCSV_lectura.close();

        // Asignar el nuevo ID
        idProducto = ultimoID + 1;

        // Escribir los datos del producto en el archivo CSV
        archivoCSV_escritura << idProducto << ";";
        archivoCSV_escritura << nombre << ";";
        archivoCSV_escritura << marca << ";";
        archivoCSV_escritura << clasificacion << ";";
        archivoCSV_escritura << cantidad << ";";
        archivoCSV_escritura << precioVenta << ";";
        archivoCSV_escritura << fechaVencimiento.getFecha() << ";";
        archivoCSV_escritura << estado << std::endl;
        archivoCSV_escritura.close();
        std::cout << "|| Producto registrado con exito. ID asignado: " << idProducto << std::endl;
    } else {
        std::cout << "|| Error al abrir el archivo CSV para guardar los datos del producto." << std::endl;
    }*/
}

void Producto::generarInformeEstado(const std::vector<Entidad*>& registro) const {
    if (estado == AGOTADO || estado == POR_VENCER || estado == VENCIDO) {
        std::ofstream archivo("Informe_Producto_Estado.txt", std::ios::app);
        if (archivo.is_open()) {
            archivo << "|| Informe de productos según estado ||\n";
            for (const Entidad* entidad : registro) {
                const Producto* producto = dynamic_cast<const Producto*>(entidad);
                if (producto && producto->getIdProducto() == idProducto) {
                    archivo << "ID del producto: " << producto->getIdProducto() << std::endl;
                    archivo << "Nombre del producto: " << producto->getNombre() << std::endl;
                    archivo << "Marca: " << producto->getMarca() << std::endl;
                    archivo << "Clasificacion: " << producto->getClasificacion() << std::endl;
                    archivo << "Cantidad: " << producto->getCantidad() << std::endl;
                    archivo << "Precio de venta: " << std::fixed << std::setprecision(3) << producto->getPrecioVenta() << std::endl;
                    archivo << "Fecha de vencimiento: " << producto->getFechaVencimiento().getFecha() << std::endl;
                    archivo << "Estado del producto: ";
                    switch (producto->getEstado()) {
                        case AGOTADO:
                            archivo << "Agotado" << std::endl;
                            break;
                        case POR_VENCER:
                            archivo << "Por vencer" << std::endl;
                            break;
                        case VENCIDO:
                            archivo << "Vencido" << std::endl;
                            break;
                        default:
                            archivo << "Desconocido" << std::endl;
                    }
                    archivo << "-------------------------------------------" << std::endl;
                }
            }
            archivo.close();
            std::cout << "|| Informe generado correctamente." << std::endl;
        } else {
            std::cout << "|| Error al abrir el archivo para generar el informe." << std::endl;
        }
    } else {
        std::cout << "|| El producto no está en estado de agotado, por vencer o vencido, no se generará el informe." << std::endl;
    }
}




void Producto::mostrarProducto() const {
    std::cout << "|| ID del producto: " << idProducto << std::endl;
    std::cout << "|| Nombre del producto: " << nombre << std::endl;
    std::cout << "|| Marca: " << marca << std::endl;
    std::cout << "|| Clasificacion: " << clasificacion << std::endl;
    std::cout << "|| Cantidad: " << cantidad << std::endl;
    std::cout << "|| Precio de venta: "<< std::fixed << std::setprecision(3) << precioVenta << std::endl;
    std::cout << "|| Fecha de vencimiento: " << fechaVencimiento.getFecha() << std::endl;
    std::cout << "|| Estado del producto: ";

    // Obtener la fecha actual
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* current_time = std::localtime(&now_time);
    int currentDay = current_time->tm_mday;
    int currentMonth = current_time->tm_mon + 1; // Se suma 1 ya que los meses se cuentan desde 0
    int currentYear = current_time->tm_year + 1900; // Se suma 1900 ya que tm_year cuenta los años desde 1900

    switch (estado) {
        case DISPONIBLE:
            std::cout << "Disponible" << std::endl;
            break;
        case AGOTADO:
            std::cout << "Agotado" << std::endl;
            break;
        case POR_VENCER:
            std::cout << "Por vencer" << std::endl;
            break;
        case VENCIDO:
            std::cout << "Vencido" << std::endl;
            break;
        default:
            std::cout << "Desconocido" << std::endl;
    }
}

void Producto::modificarProducto() {
    std::cout << "|| Modificar producto - ID: " << idProducto << std::endl;
    std::cout << "|| Señor usuario recuerde dejar en blanco para mantener el actual dato" << std::endl;

    std::string nuevoNombre;
    std::cout << "|| Ingrese el nuevo nombre del producto: ";
    std::cin.ignore();
    std::getline(std::cin, nuevoNombre);
    if (!nuevoNombre.empty()) {
        nombre = nuevoNombre;
    }

    std::string nuevaMarca;
    std::cout << "|| Ingrese la nueva marca del producto: ";
    std::getline(std::cin, nuevaMarca);
    if (!nuevaMarca.empty()) {
        marca = nuevaMarca;
    }

    std::string nuevaClasificacion;
    std::cout << "|| Ingrese la nueva clasificacion del producto: ";
    std::getline(std::cin, nuevaClasificacion);
    if (!nuevaClasificacion.empty()) {
        clasificacion = nuevaClasificacion;
    }

    int nuevaCantidad;
    std::cout << "|| Ingrese la nueva cantidad del producto: ";
    std::string cantidadStr;
    std::getline(std::cin, cantidadStr);
    if (!cantidadStr.empty()) {
        std::istringstream(cantidadStr) >> nuevaCantidad;
        cantidad = nuevaCantidad;
    }

    double nuevoPrecioVenta;
    std::cout << "|| Ingrese el nuevo precio de venta del producto: ";
    std::string precioVentaStr;
    std::getline(std::cin, precioVentaStr);
    if (!precioVentaStr.empty()) {
        std::istringstream(precioVentaStr) >> nuevoPrecioVenta;
        precioVenta = nuevoPrecioVenta;
    }

    std::string nuevaFechaVencimiento;
    std::cout << "|| Ingrese la nueva fecha de vencimiento del producto (DD/MM/AAAA): ";
    std::getline(std::cin, nuevaFechaVencimiento);
    int dia, mes, anio;
    std::cin >> dia >> mes >> anio;
    if (!std::cin.fail()) {
        Fecha nuevaFechaVen;
        nuevaFechaVen.setFecha(dia, mes, anio);
        setFechaVencimiento(nuevaFechaVen);
    } else {
        std::cout << "|| Formato de fecha incorrecto. No se modificó la fecha de vencimiento.\n";
        std::cin.clear();
        std::cin.ignore();
    }

    if (cantidad <= 0) {
        estado = AGOTADO;
        disponible = false;
    } else {
        estado = DISPONIBLE;
        disponible = true;
    }

    std::cout << "|| Producto modificado correctamente." << std::endl;
}

// Función para buscar un producto por ID y Nombre
bool buscarProducto(const std::vector<Producto>& productos, const std::string& criterio, bool buscarPorID, Producto& productoEncontrado) {
    for (const Producto &producto : productos) {
        if (buscarPorID) {
            if (producto.getIdProducto() == std::stoi(criterio)) {
                productoEncontrado = producto;
                return true;
            }
        } else {
            if (producto.getNombre() == criterio) {
                productoEncontrado = producto;
                return true;
            }
        }
    }
    return false;
}

bool buscarPorMarcaOClasificacion(const std::vector<Producto>& productos, const std::string& criterio, bool buscarPorMarca, Producto& productoEncontrado) {
    for (const Producto &producto : productos) {
        if (buscarPorMarca) {
            if (producto.getMarca() == criterio) {
                productoEncontrado = producto;
                return true;
            }
        } else {
            if (producto.getClasificacion() == criterio) {
                productoEncontrado = producto;
                return true;
            }
        }
    }
    return false;
}

void Producto::generarInformeAgotado(const std::vector<Entidad*>& registro) const {
    if (estado == AGOTADO) {
        std::ofstream archivo("Informe_Producto_Agotado.txt", std::ios::app);
        if (archivo.is_open()) {
            archivo << "|| Informe de productos agotados ||\n";
            for (const Entidad* entidad : registro) {
                const Producto* producto = dynamic_cast<const Producto*>(entidad);
                if (producto && producto->getIdProducto() == idProducto) {
                    archivo << "ID del producto: " << producto->getIdProducto() << std::endl;
                    archivo << "Nombre del producto: " << producto->getNombre() << std::endl;
                    archivo << "Marca: " << producto->getMarca() << std::endl;
                    archivo << "Clasificacion: " << producto->getClasificacion() << std::endl;
                    archivo << "Cantidad: " << producto->getCantidad() << std::endl;
                    archivo << "Precio de venta: " << std::fixed << std::setprecision(3) << producto->getPrecioVenta() << std::endl;
                    archivo << "Fecha de vencimiento: " << producto->getFechaVencimiento().getFecha() << std::endl;
                    archivo << "Estado del producto: Agotado" << std::endl;
                    archivo << "-------------------------------------------" << std::endl;
                }
            }
            archivo.close();
            std::cout << "|| Informe de productos agotados generado correctamente." << std::endl;
        } else {
            std::cout << "|| Error al abrir el archivo para generar el informe." << std::endl;
        }
    } else {
        std::cout << "|| El producto no está agotado, no se generará el informe de productos agotados." << std::endl;
    }
}


void Producto::eliminarProducto(std::vector<Producto>& productos) {
    std::cout << "|| Eliminar producto - ID: " << idProducto << std::endl;
    std::cout << "|| ¿Esta seguro que desea eliminar este producto? (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "|| Producto eliminado correctamente." << std::endl;
        if (productos.size() == 1) {
            contadorID = 0;
        }
    } else {
        std::cout << "|| Operacion de eliminacion cancelada." << std::endl;
    }
    estado = AGOTADO;
    disponible = false;
}


