#include <iostream>
#include "Factura.h"
#include <ctime>
#include <iomanip>
#include "Vendedor.h"
#include "Cliente.h"
#include <algorithm>
#include <fstream>

int Factura::contadorID = 0;

Factura::Factura() /*: Entidad(TipoEntidad::Factura)*/ {
    contadorID++;
    idFactura = contadorID;
}

void Factura::setIdVendedor(int idVendedor) {
    this->idVendedor = idVendedor;
}

void Factura::setIdCliente(int idCliente) {
    this->idCliente = idCliente;
}

void Factura::setFechaFactura(const std::string& fecha) {
    fechaFactura = fecha;
}

void Factura::setTotalFactura(float total) {
    totalFactura = total;
}

void Factura::setFormaPago(const std::string& formaPago) {
    this->formaPago = formaPago;
}

int Factura::getIdFactura() const {
    return idFactura;
}

int Factura::getIdVendedor() const {
    return idVendedor;
}

int Factura::getIdCliente() const {
    return idCliente;
}

const std::string& Factura::getFechaFactura() const {
    return fechaFactura;
}

float Factura::getTotalFactura() const {
    return totalFactura;
}

void Factura::agregarProducto(const Producto& producto, int cantidad) {
    productos.push_back(std::make_pair(producto, cantidad));
}

std::string Factura::getFormaPago() const {
    return formaPago;
}


std::string Factura::NOMBRE_FARMACIA = "Farmacia ***";
std::string Factura::DIRECCION_FARMACIA = "Calle ***, Ciudad ***";
std::string Factura::TELEFONO_FARMACIA = "123-456-7890";
std::string Factura::CORREO_FARMACIA = "farmacia@gmail.com";
std::string Factura::HORARIO_FARMACIA = "Lunes a Viernes: 9:00 AM - 6:00 PM";

void Factura::mostrarFactura(const std::vector<Entidad*>& registros) const {
    std::cout << "\n||============================================================================================================||\n";
    std::cout << "|| Factura                                                                    ||" << " ID: " << idFactura << " || " << fechaFactura << " ||" << std::endl;
    std::cout << "||============================================================================================================||\n";
    std::cout << "|| Datos de la Farmacia:                                                                             ||" << " ID: " << ID_FARMACIA << " ||" << std::endl;
    std::cout << "||============================================================================================================||\n";
    std::cout << "|| - Nombre: " << NOMBRE_FARMACIA << std::endl;
    std::cout << "|| - Direccion: " << DIRECCION_FARMACIA << std::endl;
    std::cout << "|| - Telefono: " << TELEFONO_FARMACIA << std::endl;
    std::cout << "|| - Correo: " << CORREO_FARMACIA << std::endl;
    std::cout << "|| - Horario: " << HORARIO_FARMACIA << std::endl;
    std::cout << "||============================================================================================================||\n";
    std::cout << "|| Vendedor:                                                                                         ||" << " ID: " << idVendedor << " ||" << std::endl;
    std::cout << "||============================================================================================================||\n";
    bool vendedorEncontrado = false;
    for (Entidad* entidad : registros) {
        Vendedor* vendedor = dynamic_cast<Vendedor*>(entidad);
        if (vendedor && vendedor->getIdVendedor() == idVendedor) {
            std::cout << "|| Nombre: " << vendedor->getNombre() << " - Telefono: " << vendedor->getTelefono() << " - Direccion: " << vendedor->getDireccion() << " - Correo: " << vendedor->getCorreo() << std::endl;
            vendedorEncontrado = true;
            break;
        }
    }

    if (!vendedorEncontrado) {
        std::cout << "|| Vendedor no encontrado" << std::endl;
    }

    std::cout << "||============================================================================================================||\n";
    std::cout << "|| Cliente:                                                                                          ||"<< " ID: " << idCliente << " ||" << std::endl;
    std::cout << "||============================================================================================================||\n";
    bool clienteEncontrado = false;
    for (Entidad* entidad : registros) {
        Cliente* cliente = dynamic_cast<Cliente*>(entidad);
        if (cliente && cliente->getIdCliente() == idCliente) {
            std::cout << "|| Nombre: " << cliente->getNombre() << " - Telefono: " << cliente->getTelefono() << " - Direccion: " << cliente->getDireccion() << " - Correo: " << cliente->getCorreo() << std::endl;
            clienteEncontrado = true;
            break;
        }
    }

    if (!clienteEncontrado) {
        std::cout << "|| Cliente no encontrado" << std::endl;
    }
    std::cout << "||============================================================================================================||\n";
    std::cout << "||                                                                               Forma de pago: " << getFormaPago() << std::endl;
    std::cout << "||============================================================================================================||\n";
    std::cout << "|| Productos vendidos:" << std::endl;
    for (std::pair<const Producto&, int> pair : productos) {
        const Producto& producto = pair.first;
        int cantidad = pair.second;
        std::cout << "|| - ID del producto: " << producto.getIdProducto()
                  << " - Nombre: " << producto.getNombre()
                  << " - Marca: " << producto.getMarca()
                  << " - Clasificacion: " << producto.getClasificacion()
                  << " - Cantidad: " << cantidad
                  << " - Precio Unitario: " << producto.getPrecioVenta()
                  << std::endl;
    }
    std::cout << "||============================================================================================================||\n";
    std::cout << "|| \t\t\t\t\t\t\t\t\t\t\tTotal $: " << std::fixed << std::setprecision(3) << totalFactura << std::endl;
    std::cout << "================================================================================================================\n";
}

void Factura::guardarFacturaEnArchivotxt(const std::vector<Entidad*>& registros) const {
    std::ofstream archivo("factura_" + std::to_string(idFactura) + ".txt");
    if (archivo.is_open()) {
        archivo << "\n||============================================================================================================||\n";
        archivo << "|| Factura                                                                    ||" << " ID: " << idFactura << " || " << fechaFactura << " ||" << "\n";
        archivo << "||============================================================================================================||\n";
        archivo << "|| Datos de la Farmacia:                                                                             ||" << " ID: " << ID_FARMACIA << " ||" << "\n";
        archivo << "||============================================================================================================||\n";
        archivo << "|| - Nombre: " << NOMBRE_FARMACIA << "\n";
        archivo << "|| - Direccion: " << DIRECCION_FARMACIA << "\n";
        archivo << "|| - Telefono: " << TELEFONO_FARMACIA << "\n";
        archivo << "|| - Correo: " << CORREO_FARMACIA << "\n";
        archivo << "|| - Horario: " << HORARIO_FARMACIA << "\n";
        archivo << "||============================================================================================================||\n";
        archivo << "|| Vendedor:                                                                                         ||" << " ID: " << idVendedor << " ||" << "\n";
        archivo << "||============================================================================================================||\n";

        bool vendedorEncontrado = false;
        for (Entidad* entidad : registros) {
            Vendedor* vendedor = dynamic_cast<Vendedor*>(entidad);
            if (vendedor && vendedor->getIdVendedor() == idVendedor) {
                archivo << "|| Nombre: " << vendedor->getNombre() << " - Telefono: " << vendedor->getTelefono() << " - Direccion: " << vendedor->getDireccion() << " - Correo: " << vendedor->getCorreo() << "\n";
                vendedorEncontrado = true;
                break;
            }
        }
        if (!vendedorEncontrado) {
            archivo << "|| Vendedor no encontrado" << "\n";
        }

        archivo << "||============================================================================================================||\n";
        archivo << "|| Cliente:                                                                                          ||" << " ID: " << idCliente << " ||" << "\n";
        archivo << "||============================================================================================================||\n";

        bool clienteEncontrado = false;
        for (Entidad* entidad : registros) {
            Cliente* cliente = dynamic_cast<Cliente*>(entidad);
            if (cliente && cliente->getIdCliente() == idCliente) {
                archivo << "|| Nombre: " << cliente->getNombre() << " - Telefono: " << cliente->getTelefono() << " - Direccion: " << cliente->getDireccion() << " - Correo: " << cliente->getCorreo() << "\n";
                clienteEncontrado = true;
                break;
            }
        }
        if (!clienteEncontrado) {
            archivo << "|| Cliente no encontrado" << "\n";
        }

        archivo << "||============================================================================================================||\n";
        archivo << "||                                                                               Forma de pago: " << getFormaPago() << "\n";
        archivo << "||============================================================================================================||\n";

        archivo << "|| Productos Vendidos:\n";
        for (const auto& par : productos) {
            archivo << "|| ID del Producto: " << par.first.getIdProducto() << ", ";
            archivo << "Nombre del Producto: " << par.first.getNombre() << ", ";
            archivo << "Cantidad: " << par.second << ", ";
            archivo << "Precio Unitario: " << par.first.getPrecioVenta() << "\n";
        }
        archivo << "||============================================================================================================||\n";
        archivo << "||                                                                               Total de la Factura: $" << std::fixed << std::setprecision(3) << totalFactura << "\n";
        archivo << "||============================================================================================================||\n";
        archivo.close();
        std::cout << "|| Factura guardada correctamente en archivo TXT." << std::endl;
    } else {
        std::cout << "|| Error al abrir el archivo para guardar la factura." << std::endl;
    }
}


void Factura::guardarFacturaEnArchivocsv(const std::vector<Entidad*>& registros) const {
    std::ofstream archivouno("facturas.csv", std::ios::app);
    if (archivouno.is_open()) {
        archivouno << "ID de Factura;Fecha;ID de Vendedor;Nombre de Vendedor;Telefono de Vendedor;ID de Cliente;Nombre de Cliente;Telefono de Cliente;"
                   << "ID de Producto;Nombre de Producto;Cantidad;Precio Unitario;Total;Forma de Pago\n";

        archivouno << idFactura << ";" << fechaFactura << ";" << idVendedor << ";";

        // Buscar y escribir los detalles del vendedor
        bool vendedorEncontrado = false;
        for (Entidad* entidad : registros) {
            Vendedor* vendedor = dynamic_cast<Vendedor*>(entidad);
            if (vendedor && vendedor->getIdVendedor() == idVendedor) {
                archivouno << vendedor->getNombre() << ";" << vendedor->getTelefono() << ";";
                vendedorEncontrado = true;
                break;
            }
        }
        if (!vendedorEncontrado) {
            archivouno << "No encontrado;No encontrado;";
        }

        archivouno << idCliente << ";";

        // Buscar y escribir los detalles del cliente
        bool clienteEncontrado = false;
        for (Entidad* entidad : registros) {
            Cliente* cliente = dynamic_cast<Cliente*>(entidad);
            if (cliente && cliente->getIdCliente() == idCliente) {
                archivouno << cliente->getNombre() << ";" << cliente->getTelefono() << ";";
                clienteEncontrado = true;
                break;
            }
        }
        if (!clienteEncontrado) {
            archivouno << "No encontrado;No encontrado;";
        }

        for (const auto& par : productos) {
            const Producto& producto = par.first;
            int cantidad = par.second;
            archivouno << producto.getIdProducto() << ";" << producto.getNombre() << ";" << cantidad << ";"
                       << producto.getPrecioVenta() << ";";
        }

        archivouno << totalFactura << ";" << formaPago << "\n";
        archivouno.close();
        std::cout << "|| Factura guardada correctamente en archivo CSV." << std::endl;
    } else {
        std::cout << "|| Error al abrir el archivo para guardar la factura." << std::endl;
    }
}


void generarInformeVentas(const std::vector<Factura>& facturas) {
    int diaInicio, mesInicio, anioInicio;
    int diaFin, mesFin, anioFin;
    std::cout << "|| Ingrese la fecha de inicio en formato DD MM AAAA: ";
    std::cin >> diaInicio >> mesInicio >> anioInicio;
    std::cout << "|| Ingrese la fecha de fin en formato DD MM AAAA: ";
    std::cin >> diaFin >> mesFin >> anioFin;

    float totalVentasPeriodo = 0.0;

    std::cout << "================================================================================================================\n";
    std::cout << "||                                Informe de Ventas                                                           ||\n";
    std::cout << "================================================================================================================\n";
    std::cout << "|| Fecha                  | Cliente                | Nro Factura                | Total Factura               \n";
    std::cout << "================================================================================================================\n";

    for (const Factura& factura : facturas) {
        std::string fechaFactura = factura.getFechaFactura();
        // Descomponer la fecha de la factura
        std::istringstream iss(fechaFactura);
        int diaFactura, mesFactura, anioFactura;
        char delimiter;
        iss >> diaFactura >> delimiter >> mesFactura >> delimiter >> anioFactura;
        // Verificar si la fecha de la factura está en el rango seleccionado
        if (anioFactura == anioInicio && mesFactura == mesInicio && diaFactura >= diaInicio &&
            anioFactura == anioFin && mesFactura == mesFin && diaFactura <= diaFin) {
            // Calcular el total de la factura
            float totalFactura = factura.getTotalFactura();
            totalVentasPeriodo += totalFactura;
            // Mostrar información de la factura
            std::cout << "|| " << fechaFactura << " | " << factura.getIdCliente() << " | " << factura.getIdFactura() << " | " << totalFactura << " ||\n";
        }
    }

    std::cout << "================================================================================================================\n";
    std::cout << "|| Total de ventas del periodo: " << totalVentasPeriodo << " \n";
    std::cout << "================================================================================================================\n";

    // Preguntar al usuario si desea exportar el informe a un archivo
    char opcion;
    std::cout << "¿Desea exportar el informe a un archivo? (S/N): ";
    std::cin >> opcion;

    if (opcion == 'S' || opcion == 's') {
        std::string nombreArchivo;
        std::cout << "Ingrese el nombre del archivo (sin extensión): ";
        std::cin >> nombreArchivo;
        std::string extension;
        std::cout << "Ingrese la extension del archivo (.txt o .csv): ";
        std::cin >> extension;

        std::ofstream archivo(nombreArchivo + extension);
        if (archivo.is_open()) {
            archivo << "Fecha,Cliente,Nro Factura,Total Factura\n";
            for (const Factura& factura : facturas) {
                std::string fechaFactura = factura.getFechaFactura();
                int diaFactura, mesFactura, anioFactura;
                char delimiter;
                std::istringstream iss(fechaFactura);
                iss >> diaFactura >> delimiter >> mesFactura >> delimiter >> anioFactura;
                if (anioFactura == anioInicio && mesFactura == mesInicio && diaFactura >= diaInicio &&
                    anioFactura == anioFin && mesFactura == mesFin && diaFactura <= diaFin) {
                    archivo << fechaFactura << "," << factura.getIdCliente() << "," << factura.getIdFactura() << "," << factura.getTotalFactura() << "\n";
                }
            }
            archivo << "Total de ventas del periodo," << totalVentasPeriodo;
            std::cout << "El informe ha sido exportado correctamente a " << nombreArchivo + extension << std::endl;
        } else {
            std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        }
    }
}


enum EstadoRotacion {
    BAJA,
    NORMAL,
    ALTA,
};

void Factura::generarInformeBajaRotacion(const std::vector<Entidad*>& registro, const std::vector<Factura>& facturas) {
    std::ofstream archivo("Informe_Productos_Rotacion.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << "|| Informe de productos según rotación ||\n";
        for (Entidad* entidad : registro) {
            Producto* producto = dynamic_cast<Producto*>(entidad);
            if (producto) {
                int totalVendido = 0;
                for (const Factura& factura : facturas) {
                    for (const std::pair<Producto, int>& venta : factura.getProductos()) {
                        if (venta.first.getIdProducto() == producto->getIdProducto()) {
                            totalVendido += venta.second;
                        }
                    }
                }
                EstadoRotacion estado;
                if (totalVendido < 3) {
                    estado = BAJA;
                } else if (totalVendido < 10) {
                    estado = NORMAL;
                } else {
                    estado = ALTA;
                }
                archivo << "|| ID del producto: " << producto->getIdProducto() << std::endl;
                archivo << "|| Nombre del producto: " << producto->getNombre() << std::endl;
                archivo << "|| Cantidad total vendida: " << totalVendido << std::endl;
                archivo << "|| Estado de rotación: ";
                switch (estado) {
                    case BAJA:
                        archivo << "Baja" << std::endl;
                        break;
                    case NORMAL:
                        archivo << "Normal" << std::endl;
                        break;
                    case ALTA:
                        archivo << "Alta" << std::endl;
                        break;
                }
                archivo << "-------------------------------------------" << std::endl;
            }
        }
        archivo.close();
        std::cout << "|| Informe de productos segun la rotacion generado correctamente." << std::endl;
    } else {
        std::cout << "|| Error al abrir el archivo para generar el informe." << std::endl;
    }
}


void Factura::eliminarFactura(std::vector<Factura>& facturas) {
    std::cout << "|| Eliminar factura - ID: " << idFactura << std::endl;
    std::cout << "|| ¿Esta seguro que desea eliminar esta factura? (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "|| Factura eliminada correctamente." << std::endl;
        if (facturas.size() == 1) {
            contadorID = 0;
        }
    } else {
        std::cout << "|| Operacion de eliminacion cancelada." << std::endl;
    }
}



