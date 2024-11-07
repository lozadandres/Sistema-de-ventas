#include <iostream>
#include "Entidad.h"
#include "Cliente.h"
#include "Vendedor.h"
#include "Producto.h"
#include "Factura.h"
#include <algorithm>
#include <ctime>
#include <sstream>
#include <fstream>

// corregir para que no se sobrescriba en archivos txt
//archivos: agregar, listar, buscar, modificar y eliminar

int main() {
    system("color F0");
    std::vector<Entidad*> registro;
    std::vector<Vendedor> vendedores;
    std::vector<Cliente> clientes;
    std::vector<Producto> productos;
    std::vector<Factura> facturas;

    int opcion;
    do {
        std::cout << "=====================================================\n";
        std::cout << "||---------------- Menu Principal -----------------||" << std::endl;
        std::cout << "=====================================================\n";
        std::cout << "|| 1. Gestionar Vendedores                         ||" << std::endl;
        std::cout << "|| 2. Gestionar Clientes                           ||" << std::endl;
        std::cout << "|| 3. Gestionar Productos                          ||" << std::endl;
        std::cout << "|| 4. Gestionar Ventas                             ||" << std::endl;
        std::cout << "|| 5. Salir del programa                           ||" << std::endl;
        std::cout << "=====================================================\n";
        std::cout << "|| Ingrese su opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                system("cls");
                int opcionVendedor;
                do {
                    std::cout << "====================================================================================\n";
                    std::cout << "||----------------------------- GESTIONAR VENDEDORES -----------------------------||" << std::endl;
                    std::cout << "====================================================================================\n";
                    std::cout << "|| 1. Crear Vendedor                                                              ||" << std::endl;
                    std::cout << "|| 2. Historial de Vendedor                                                       ||" << std::endl;
                    std::cout << "|| 3. Modificar Vendedor                                                          ||" << std::endl;
                    std::cout << "|| 4. Buscar por ID o Nombre                                                      ||" << std::endl;
                    std::cout << "|| 5. Eliminar Vendedor                                                           ||" << std::endl;
                    std::cout << "|| 6. Regresar al Menu Principal                                                  ||" << std::endl;
                    std::cout << "====================================================================================\n";
                    std::cout << "|| Ingrese su opcion: ";
                    std::cin >> opcionVendedor;

                    switch (opcionVendedor) {
                        case 1: {
                            system("cls");
                            std::cout << "====================================================================================\n";
                            std::cout << "||------------------------- INGRESO DE DATOS DEL VENDEDOR ------------------------||" << std::endl;
                            std::cout << "====================================================================================\n";
                            Vendedor* vendedor = new Vendedor();
                            vendedor -> ingresarRegistro();
                            registro.push_back(vendedor);
                            break;
                        }
                        case 2: {
                            system("cls");
                            std::cout << "====================================================================================\n";
                            std::cout << "||--------------------------- HISTORIAL DE LOS VENDEDORES ------------------------||" << std::endl;
                            std::cout << "====================================================================================\n";
                            if (registro.empty()) {
                                std::cout << "|| No hay vendedores registrados.                                                   ||" << std::endl;
                            } else {
                                int cantVendedores = registro.size();
                                int contador = 1;

                                for (int i = 0; i < cantVendedores; i++) {
                                    std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                    std::cout << "|| Registro #" << contador++ << " vendedores:                                                        ||" << std::endl;
                                    std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                    Vendedor* vendedorAuxiliar = dynamic_cast<Vendedor*>(registro[i]);
                                    if (vendedorAuxiliar) {
                                        std::cout << "|| Mostrando Informacion                                                          ||" << std::endl;
                                        std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                        vendedorAuxiliar->mostrarVendedor();
                                    } else {
                                        std::cout << "|| No se pudo obtener información del vendedor.                                    ||" << std::endl;
                                    }
                                    std::cout << "====================================================================================" << std::endl;
                                }
                            }
                            break;
                        }
                        case 3: {
                            system("cls");
                            std::cout << "====================================================================================\n";
                            std::cout << "||-------------------------- MODIFICAR DATOS DEL VENDEDOR -------------------------||" << std::endl;
                            std::cout << "====================================================================================\n";
                            int idVendedorModificar;
                            std::cout << "|| Ingrese el ID del vendedor a modificar: ";
                            std::cin >> idVendedorModificar;

                            bool encontradoVendedor = false;
                            for (Entidad* entidad : registro) {
                                Vendedor* vendedor = dynamic_cast<Vendedor*>(entidad);
                                if (vendedor && vendedor->getIdVendedor() == idVendedorModificar) {
                                    vendedor->actualizarRegistro();
                                    encontradoVendedor = true;
                                    break;
                                }
                            }

                            if (!encontradoVendedor) {
                                std::cout << "|| Vendedor no encontrado." << std::endl;
                            }
                            break;
                        }
                        case 4: {
                            system("cls");
                            std::cout << "====================================================================================\n";
                            std::cout << "||----------------------------- BUSQUEDA DEL VENDEDOR ----------------------------||" << std::endl;
                            std::cout << "====================================================================================\n";
                            std::string input;
                            std::cout << "|| Ingrese el ID del vendedor o su nombre: ";
                            std::cin >> input;

                            Vendedor vendedorEncontrado;
                            bool vendedorEncontradoFlag = false;

                            if (std::isdigit(input[0])) {
                                int idVendedor = std::stoi(input);
                                for (Entidad* entidad : registro) {
                                    Vendedor* vendedor = dynamic_cast<Vendedor*>(entidad);
                                    if (vendedor && vendedor->getIdVendedor() == idVendedor) {
                                        vendedorEncontrado = *vendedor;
                                        vendedorEncontradoFlag = true;
                                        break;
                                    }
                                }
                            } else {
                                std::vector<Vendedor> vendedoresEncontrados;
                                for (Entidad* entidad : registro) {
                                    Vendedor* vendedor = dynamic_cast<Vendedor*>(entidad);
                                    if (vendedor && vendedor->getNombre() == input) {
                                        vendedoresEncontrados.push_back(*vendedor);
                                    }
                                }
                                if (!vendedoresEncontrados.empty()) {
                                    std::cout << "|| Se encontraron vendedores con el nombre especificado." << std::endl;
                                    int contador = 1;
                                    for (const Vendedor& vendedor : vendedoresEncontrados) {
                                        std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                        std::cout << "|| Registro #" << contador++ << " vendedores:" << std::endl;
                                        std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                        vendedor.mostrarVendedor();
                                        std::cout << "====================================================================================" << std::endl;
                                    }
                                } else {
                                    std::cout << "|| No se encontraron vendedores con el nombre especificado." << std::endl;
                                }
                            }

                            if (vendedorEncontradoFlag) {
                                std::cout << "|| Vendedor encontrado:" << std::endl;
                                int contador = 1;
                                std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                std::cout << "|| Registro #" << contador++ << " vendedores:" << std::endl;
                                std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                vendedorEncontrado.mostrarVendedor();
                                std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                // Mostrar historial de ventas relacionado con este vendedor
                                std::cout << "|| Historial de ventas del vendedor:" << std::endl;
                                for (const auto& factura : facturas) {
                                    if (factura.getIdVendedor() == vendedorEncontrado.getIdVendedor()) {
                                        std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                        std::cout << "|| Factura #" << factura.getIdFactura() << ":" << std::endl;
                                        std::cout << "|| ID Factura: " << factura.getIdFactura() << std::endl;
                                        std::cout << "|| Fecha y Hora: " << factura.getFechaFactura() << std::endl;
                                        std::cout << "|| Forma de pago: " << factura.getFormaPago() << std::endl;
                                        std::cout << "||   Detalles de los Productos:" << std::endl;
                                        for (const auto& par : factura.getProductos()) {
                                            const Producto& producto = par.first;
                                            int cantidad = par.second;
                                            std::cout << "||     ID del Producto: " << producto.getIdProducto()
                                                      << ", Nombre: " << producto.getNombre()
                                                      << ", Precio Unitario: " << producto.getPrecioVenta()
                                                      << ", Cantidad: " << cantidad << std::endl;
                                        }
                                    }
                                }
                                std::cout << "====================================================================================\n";
                            } else {
                                std::cout << "|| Vendedor no encontrado." << std::endl;
                            }

                            float totalTodasLasVentas = 0.0;
                            for (const auto& factura : facturas) {
                                totalTodasLasVentas += factura.getTotalFactura();
                            }

                            std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                            std::cout << "|| Total de todas las ventas realizadas: $" << totalTodasLasVentas << std::endl;
                            std::cout << "====================================================================================" << std::endl;

                            std::string respuesta;
                            std::cout << "¿Desea guardar la información en un archivo de texto? (Si/No): ";
                            std::cin >> respuesta;

                            if (respuesta == "Sí" || respuesta == "sí" || respuesta == "SI" || respuesta == "si") {
                                std::string nombreArchivo = "informacion_vendedor_" + input + ".txt"; // Construir el nombre del archivo
                                std::ofstream archivo(nombreArchivo);
                                if (archivo.is_open()) {
                                    if (vendedorEncontradoFlag) {
                                        archivo << "|| Vendedor encontrado:" << std::endl;
                                        int contador = 1;
                                        archivo << "||----------------------------------------------------------------------------------" << std::endl;
                                        archivo << "|| Registro #" << contador++ << " vendedores:" << std::endl;
                                        archivo << "||----------------------------------------------------------------------------------" << std::endl;
                                        vendedorEncontrado.mostrarVendedor(archivo);
                                        archivo << "||----------------------------------------------------------------------------------" << std::endl;
                                        // Mostrar historial de ventas relacionado con este vendedor
                                        archivo << "|| Historial de ventas del vendedor:" << std::endl;
                                        for (const auto& factura : facturas) {
                                            if (factura.getIdVendedor() == vendedorEncontrado.getIdVendedor()) {
                                                archivo << "||----------------------------------------------------------------------------------" << std::endl;
                                                archivo << "|| Factura #" << factura.getIdFactura() << ":" << std::endl;
                                                archivo << "|| ID Factura: " << factura.getIdFactura() << std::endl;
                                                archivo << "|| Fecha y Hora: " << factura.getFechaFactura() << std::endl;
                                                archivo << "|| Forma de pago: " << factura.getFormaPago() << std::endl;
                                                archivo << "||   Detalles de los Productos:" << std::endl;
                                                for (const auto& par : factura.getProductos()) {
                                                    const Producto& producto = par.first;
                                                    int cantidad = par.second;
                                                    archivo << "||     ID del Producto: " << producto.getIdProducto()
                                                            << ", Nombre: " << producto.getNombre()
                                                            << ", Precio Unitario: " << producto.getPrecioVenta()
                                                            << ", Cantidad: " << cantidad << std::endl;
                                                }
                                            }
                                        }
                                        archivo << "====================================================================================\n";
                                        float totalVentas = 0.0;
                                        for (const auto& factura : facturas) {
                                            if (factura.getIdVendedor() == vendedorEncontrado.getIdVendedor()) {
                                                totalVentas += factura.getTotalFactura();
                                            }
                                        }
                                        archivo << "|| Total de ventas realizadas por este vendedor: $" << totalVentas << std::endl;
                                    } else {
                                        archivo << "|| Vendedor no encontrado." << std::endl;
                                    }
                                    archivo.close();
                                    std::cout << "|| La información se ha guardado correctamente en '" << nombreArchivo << "'." << std::endl;
                                } else {
                                    std::cerr << "Error al abrir el archivo." << std::endl;
                                }
                            }

                            break;
                        }
                        case 5: {
                            system("cls");
                            std::cout << "====================================================================================\n";
                            std::cout << "||--------------------------------- ELIMINAR VENDEDOR -----------------------------||" << std::endl;
                            std::cout << "====================================================================================\n";
                            bool vendedorEncontrado = false;
                            int idVendedorEliminar;
                            std::cout << "|| Ingrese el ID del vendedor a eliminar: ";
                            std::cin >> idVendedorEliminar;

                            int n = registro.size();
                            for (int i = 0; i < n; i++) {
                                Vendedor* vendedor = dynamic_cast<Vendedor*>(registro[i]);
                                if (vendedor && vendedor->getIdVendedor() == idVendedorEliminar) {
                                    vendedorEncontrado = true;
                                    std::cout << "|| Datos del Vendedor:" << std::endl;
                                    vendedor->mostrarVendedor(); // Mostrar información del vendedor antes de eliminar

                                    // Eliminar vendedor del vector
                                    delete registro[i];
                                    registro.erase(registro.begin() + i);
                                    break;
                                }
                            }
                            if (!vendedorEncontrado) {
                                std::cout << "|| Vendedor no encontrado." << std::endl;
                            }
                            break;
                        }
                        case 6:
                            system("cls");
                            std::cout << "|| Volviendo al Menu Principal.\n";
                            break;
                        default:
                            std::cout << "|| Opcion invalida. Por favor, intente de nuevo." << std::endl;
                            break;
                    }

                } while (opcionVendedor != 6);
                break;
            }
            case 2: {
                system("cls");
                int opcionCliente;
                do {
                    std::cout << "====================================================================================\n";
                    std::cout << "||------------------------------ GESTIONAR CLIENTES ------------------------------||" << std::endl;
                    std::cout << "====================================================================================\n";
                    std::cout << "|| 1. Crear Cliente                                                               ||" << std::endl;
                    std::cout << "|| 2. Historial de Clientes                                                       ||" << std::endl;
                    std::cout << "|| 3. Modificar Cliente                                                           ||" << std::endl;
                    std::cout << "|| 4. Buscar por ID o Nombre                                                      ||" << std::endl;
                    std::cout << "|| 5. Eliminar Cliente                                                            ||" << std::endl;
                    std::cout << "|| 6. Regresar al Menu Principal                                                  ||" << std::endl;
                    std::cout << "====================================================================================\n";
                    std::cout << "|| Ingrese su opcion: ";
                    std::cin >> opcionCliente;

                    switch (opcionCliente) {
                        case 1: {
                            system("cls");
                            std::cout << "====================================================================================\n";
                            std::cout << "||------------------------- INGRESO DE DATOS DEL CLIENTE -------------------------||" << std::endl;
                            std::cout << "====================================================================================\n";
                            std::vector<Entidad*> registros;
                            Cliente* cliente = new Cliente();
                            cliente->ingresarRegistro();
                            registro.push_back(cliente);
                            break;
                        }
                        case 2: {
                            system("cls");
                            std::cout << "====================================================================================\n";
                            std::cout << "||----------------------------- HISTORIAL DE LOS CLIENTE -------------------------||" << std::endl;
                            std::cout << "====================================================================================\n";
                            if (registro.empty()) {
                                std::cout << "|| No hay clientes registrados.                                                   ||" << std::endl;
                            } else {
                                int cantClientes = registro.size();
                                int contador = 1;

                                for(int i = 0; i < cantClientes; i++) {
                                    std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                    std::cout << "|| Registro #" << contador++ << " clientes:                                                          ||" << std::endl;
                                    std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                    Cliente* clienteAuxiliar = dynamic_cast<Cliente*>(registro[i]);
                                    if (clienteAuxiliar) {
                                        std::cout << "|| Mostrando Informacion                                                          ||" << std::endl;
                                        std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                        clienteAuxiliar->mostrarCliente();
                                    } else {
                                        std::cout << "|| No se pudo obtener información del cliente.                                      ||" << std::endl;
                                    }
                                    std::cout << "====================================================================================" << std::endl;
                                }

                            }

                            break;
                        }
                        case 3: {
                            system("cls");
                            std::cout << "====================================================================================\n";
                            std::cout << "||-------------------------- MODIFICAR DATOS DEL CLIENTE -------------------------||" << std::endl;
                            std::cout << "====================================================================================\n";
                            int idClienteModificar;
                            std::cout << "|| Ingrese el ID del cliente a modificar: ";
                            std::cin >> idClienteModificar;

                            bool encontrado = false;
                            for (Entidad* entidad : registro) {
                                Cliente* cliente = dynamic_cast<Cliente*>(entidad);
                                if (cliente && cliente->getIdCliente() == idClienteModificar) {
                                    cliente->modificarCliente();
                                    encontrado = true;
                                    break;
                                }
                            }

                            if (!encontrado) {
                                std::cout << "|| Cliente no encontrado." << std::endl;
                            }
                            break;
                        }
                        case 4: {
                            system("cls");
                            std::cout << "====================================================================================\n";
                            std::cout << "||----------------------------- BUSQUEDA DEL CLIENTE -----------------------------||" << std::endl;
                            std::cout << "====================================================================================\n";
                            std::string input;
                            std::cout << "|| Ingrese el ID del cliente o su nombre: ";
                            std::cin >> input;

                            Cliente clienteEncontrado;
                            bool clienteEncontradoFlag = false;

                            if (std::isdigit(input[0])) {
                                int idCliente = std::stoi(input);
                                for (Entidad* entidad : registro) {
                                    Cliente* cliente = dynamic_cast<Cliente*>(entidad);
                                    if (cliente && cliente->getIdCliente() == idCliente) {
                                        clienteEncontrado = *cliente;
                                        clienteEncontradoFlag = true;
                                        break;
                                    }
                                }
                            } else {
                                std::vector<Cliente> clientesEncontrados;
                                for (Entidad* entidad : registro) {
                                    Cliente* cliente = dynamic_cast<Cliente*>(entidad);
                                    if (cliente && cliente->getNombre() == input) {
                                        clientesEncontrados.push_back(*cliente);
                                    }
                                }
                                if (!clientesEncontrados.empty()) {
                                    std::cout << "|| Se encontraron clientes con el nombre especificado." << std::endl;
                                    int contador = 1;
                                    for (const Cliente& cliente : clientesEncontrados) {
                                        std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                        std::cout << "|| Registro #" << contador++ << " clientes:" << std::endl;
                                        std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                        cliente.mostrarCliente();
                                        std::cout << "====================================================================================" << std::endl;
                                    }
                                } else {
                                    std::cout << "|| No se encontraron clientes con el nombre especificado." << std::endl;
                                }
                            }

                            if (clienteEncontradoFlag) {
                                std::cout << "|| Cliente encontrado:" << std::endl;
                                int contador = 1;
                                std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                std::cout << "|| Registro #" << contador++ << " clientes:" << std::endl;
                                std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                clienteEncontrado.mostrarCliente();
                                std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                // Mostrar historial de compras relacionado con este cliente
                                std::cout << "|| Historial de compras del cliente:" << std::endl;
                                for (const auto& factura : facturas) {
                                    if (factura.getIdCliente() == clienteEncontrado.getIdCliente()) {
                                        std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                        std::cout << "|| Factura #" << factura.getIdFactura() << ":" << std::endl;
                                        std::cout << "|| ID Factura: " << factura.getIdFactura() << std::endl;
                                        std::cout << "|| Fecha y Hora: " << factura.getFechaFactura() << std::endl;
                                        std::cout << "|| Forma de pago: " << factura.getFormaPago() << std::endl;
                                        std::cout << "||   Detalles de los Productos:" << std::endl;
                                        for (const auto& par : factura.getProductos()) {
                                            const Producto& producto = par.first;
                                            int cantidad = par.second;
                                            std::cout << "||     ID del Producto: " << producto.getIdProducto()
                                                      << ", Nombre: " << producto.getNombre()
                                                      << ", Precio Unitario: " << producto.getPrecioVenta()
                                                      << ", Cantidad: " << cantidad << std::endl;
                                        }
                                        float totalCompras = 0.0;
                                        for (const auto& factura : facturas) {
                                            if (factura.getIdCliente() == clienteEncontrado.getIdCliente()) {
                                                totalCompras += factura.getTotalFactura();
                                            }
                                        }

                                        std::cout << "||----------------------------------------------------------------------------------" << std::endl;
                                        std::cout << "|| Total de compras realizadas por este cliente: $" << totalCompras << std::endl;
                                        std::cout << "====================================================================================" << std::endl;
                                    }
                                }
                                std::cout << "====================================================================================\n";
                                std::string respuesta;
                                std::cout << "¿Desea guardar la informacion en un archivo de texto? (Si/No): ";
                                std::cin >> respuesta;

                                if (respuesta == "Sí" || respuesta == "sí" || respuesta == "SI" || respuesta == "si") {
                                    std::string nombreArchivo = "informacion_cliente_" + input + ".txt"; // Construir el nombre del archivo
                                    std::ofstream archivo(nombreArchivo);
                                    if (archivo.is_open()) {
                                        if (clienteEncontradoFlag) {
                                            archivo << "|| Cliente encontrado:" << std::endl;
                                            int contador = 1;
                                            archivo << "||----------------------------------------------------------------------------------" << std::endl;
                                            archivo << "|| Registro #" << contador++ << " clientes:" << std::endl;
                                            archivo << "||----------------------------------------------------------------------------------" << std::endl;
                                            clienteEncontrado.mostrarCliente(archivo);
                                            archivo << "||----------------------------------------------------------------------------------" << std::endl;
                                            // Mostrar historial de compras relacionado con este cliente
                                            archivo << "|| Historial de compras del cliente:" << std::endl;
                                            for (const auto& factura : facturas) {
                                                if (factura.getIdCliente() == clienteEncontrado.getIdCliente()) {
                                                    archivo << "||----------------------------------------------------------------------------------" << std::endl;
                                                    archivo << "|| Factura #" << factura.getIdFactura() << ":" << std::endl;
                                                    archivo << "|| ID Factura: " << factura.getIdFactura() << std::endl;
                                                    archivo << "|| Fecha y Hora: " << factura.getFechaFactura() << std::endl;
                                                    archivo << "|| Forma de pago: " << factura.getFormaPago() << std::endl;
                                                    archivo << "||   Detalles de los Productos:" << std::endl;
                                                    for (const auto& par : factura.getProductos()) {
                                                        const Producto& producto = par.first;
                                                        int cantidad = par.second;
                                                        archivo << "||     ID del Producto: " << producto.getIdProducto()
                                                                << ", Nombre: " << producto.getNombre()
                                                                << ", Precio Unitario: " << producto.getPrecioVenta()
                                                                << ", Cantidad: " << cantidad << std::endl;
                                                    }
                                                }
                                            }
                                            archivo << "====================================================================================\n";
                                            float totalCompras = 0.0;
                                            archivo << "|| Total de compras realizadas por este cliente: $" << totalCompras << std::endl;
                                        } else {
                                            archivo << "|| Cliente no encontrado." << std::endl;
                                        }
                                        archivo.close();
                                        std::cout << "|| La informacion se ha guardado correctamente en '" << nombreArchivo << "'." << std::endl;
                                    } else {
                                        std::cerr << "Error al abrir el archivo." << std::endl;
                                    }
                                }

                            } else {
                                std::cout << "|| Cliente no encontrado." << std::endl;
                            }
                            break;
                        }
                        case 5: {
                            system("cls");
                            std::cout << "====================================================================================\n";
                            std::cout << "||--------------------------------- ELIMINAR CLIENTE -----------------------------||" << std::endl;
                            std::cout << "====================================================================================\n";
                            bool clienteEncontrado = false;
                            int idClienteEliminar;
                            std::cout << "|| Ingrese el ID del cliente a eliminar: ";
                            std::cin >> idClienteEliminar;

                            int n = registro.size();
                            for (int i = 0; i < n; i++) {
                                Cliente* cliente = dynamic_cast<Cliente*>(registro[i]);
                                if (cliente && cliente->getIdCliente() == idClienteEliminar) {
                                    clienteEncontrado = true;
                                    std::cout << "|| Datos del Cliente:" << std::endl;
                                    std::cout << "|| ID: " << cliente->getIdCliente() << std::endl;
                                    std::cout << "|| Nombre: " << cliente->getNombre() << std::endl;

                                    cliente->eliminarCliente(clientes);
                                    registro.erase(registro.begin() + i); // Eliminar cliente del vector
                                    break;
                                }
                            }
                            if (!clienteEncontrado) {
                                std::cout << "|| Cliente no encontrado." << std::endl;
                            }
                            break;
                        }
                        case 6:
                            system("cls");
                            std::cout << "|| Volviendo al Menu Principal.\n";
                            break;
                        default:
                            std::cout << "|| Opcion invalida. Por favor, intente de nuevo." << std::endl;
                            break;
                    }
                } while (opcionCliente != 6);

                break;
            }
            case 3: {
                system("cls");
                int opcionProducto;
                do {
                    std::cout << "======================================================================================\n";
                    std::cout << "||------------------------------- GESTIONAR PRODUCTOS ------------------------------||" << std::endl;
                    std::cout << "======================================================================================\n";
                    std::cout << "|| 1. Crear Producto                                                                ||" << std::endl;
                    std::cout << "|| 2. Historial de Productos                                                        ||" << std::endl;
                    std::cout << "|| 3. Modificar Producto                                                            ||" << std::endl;
                    std::cout << "|| 4. Buscar por ID, Nombre, Marca o Clasificacion                                  ||" << std::endl;
                    std::cout << "|| 5. Eliminar Producto                                                             ||" << std::endl;
                    std::cout << "|| 6. Regresar al Menu Principal                                                    ||" << std::endl;
                    std::cout << "======================================================================================\n";
                    std::cout << "|| Ingrese su opcion: ";
                    std::cin >> opcionProducto;

                    switch (opcionProducto) {
                        case 1: {
                            system("cls");
                            std::cout << "======================================================================================\n";
                            std::cout << "||------------------------- INGRESO DE DATOS DEL PORODUCTO -------------------------||" << std::endl;
                            std::cout << "======================================================================================\n";
                            Producto* producto = new Producto();
                            producto->ingresarRegistro();
                            registro.push_back(producto);
                            break;
                        }
                        case 2: {
                            system("cls");
                            std::cout << "======================================================================================\n";
                            std::cout << "||----------------------------- HISTORIAL DE LOS PRODUCTOS -------------------------||" << std::endl;
                            std::cout << "======================================================================================\n";
                            if (registro.empty()) {
                                std::cout << "|| No hay productos registrados.                                                    ||" << std::endl;
                            } else {
                                int contador = 1;
                                for(const Entidad* entidad : registro) {
                                    const Producto* producto = dynamic_cast<const Producto*>(entidad);
                                    if (producto) {
                                        std::cout << "||------------------------------------------------------------------------------------" << std::endl;
                                        std::cout << "|| Registro #" << contador++ << " productos:" << std::endl;
                                        std::cout << "||------------------------------------------------------------------------------------" << std::endl;
                                        std::cout << "|| Mostrando Informacion" << std::endl;
                                        std::cout << "||------------------------------------------------------------------------------------" << std::endl;
                                        producto->mostrarProducto();
                                        std::cout << "======================================================================================" << std::endl;
                                    } else {
                                        std::cout << "|| No se pudo obtener información del producto.                                    ||" << std::endl;
                                    }
                                }
                            }
                            break;
                        }
                        case 3: {
                            system("cls");
                            std::cout << "======================================================================================\n";
                            std::cout << "||--------------------------- MODIFICAR DATOS DEL PRODUCTO -------------------------||" << std::endl;
                            std::cout << "======================================================================================\n";
                            int idProductoModificar;
                            std::cout << "|| Ingrese el ID del producto a modificar: ";
                            std::cin >> idProductoModificar;
                            bool encontrado = false;
                            for (Entidad* entidad : registro) {
                                Producto* producto = dynamic_cast<Producto*>(entidad);
                                if (producto && producto->getIdProducto() == idProductoModificar) {
                                    producto->modificarProducto();
                                    encontrado = true;
                                    break;
                                }
                            }

                            if (!encontrado) {
                                std::cout << "|| Producto no encontrado." << std::endl;
                            }
                            break;
                        }
                        case 4: {
                            system("cls");
                            std::cout << "======================================================================================\n";
                            std::cout << "||------------------------------ BUSQUEDA DEL PRODUCTO -----------------------------||" << std::endl;
                            std::cout << "======================================================================================\n";
                            int contador = 1;
                            std::string input;
                            std::cout << "|| Elija cómo buscar el producto (i: ID, n: Nombre, m: Marca, c: Clasificación): ";
                            std::cin >> input;

                            Producto productoEncontrado;
                            bool productoEncontradoFlag = false;

                            if (input == "i") {
                                std::cout << "|| Ingrese el ID del producto: ";
                                std::cin >> input;
                                for (Entidad* entidad : registro) {
                                    Producto* producto = dynamic_cast<Producto*>(entidad);
                                    if (producto && producto->getIdProducto() == std::stoi(input)) {
                                        productoEncontrado = *producto;
                                        productoEncontradoFlag = true;
                                        break;
                                    }
                                }
                            } else if (input == "n" || input == "m" || input == "c") {
                                std::string campo;
                                if (input == "n") {
                                    campo = "nombre";
                                } else if (input == "m") {
                                    campo = "marca";
                                } else if (input == "c") {
                                    campo = "clasificación";
                                }
                                std::cout << "|| Ingrese el " << campo << " del producto: ";
                                std::cin >> input;
                                for (Entidad* entidad : registro) {
                                    Producto* producto = dynamic_cast<Producto*>(entidad);
                                    if (producto && producto->campoCoincide(input, campo)) {
                                        if (!productoEncontradoFlag) {
                                            productoEncontrado = *producto;
                                            productoEncontradoFlag = true;
                                        }
                                        std::cout << "||------------------------------------------------------------------------------------" << std::endl;
                                        std::cout << "|| Registro #" << contador++ << " productos:" << std::endl;
                                        std::cout << "||------------------------------------------------------------------------------------" << std::endl;
                                        producto->mostrarProducto();
                                        std::cout << "======================================================================================" << std::endl;
                                    }
                                }
                            } else {
                                std::cout << "|| Opción inválida." << std::endl;
                            }

                            if (productoEncontradoFlag) {
                                std::cout << "|| Producto encontrado:" << std::endl;
                                std::cout << "||------------------------------------------------------------------------------------" << std::endl;
                                productoEncontrado.mostrarProducto();
                                std::cout << "======================================================================================\n";
                            } else {
                                std::cout << "|| Producto no encontrado." << std::endl;
                            }

                            break;
                        }

                        case 5: {
                            system("cls");
                            std::cout << "======================================================================================\n";
                            std::cout << "||--------------------------------- ELIMINAR PRODUCTO ------------------------------||" << std::endl;
                            std::cout << "======================================================================================\n";
                            bool productoEncontrado = false;
                            int idProductoEliminar;
                            std::cout << "|| Ingrese el ID del producto a eliminar: ";
                            std::cin >> idProductoEliminar;

                            int n = registro.size();
                            for(int i = 0; i < n; i++){
                                Producto* producto = dynamic_cast<Producto*>(registro[i]);
                                if(producto && producto->getIdProducto() == idProductoEliminar){
                                    productoEncontrado = true;
                                    std::cout << "|| Datos del Producto:" << std::endl;
                                    std::cout << "|| ID: " << producto->getIdProducto() << std::endl;
                                    std::cout << "|| Nombre: " << producto->getNombre() << std::endl;

                                    producto->eliminarProducto(productos);
                                    registro.erase(registro.begin() + i); // Eliminar producto del vector
                                    break;
                                }
                            }

                            if(!productoEncontrado){
                                std::cout << "|| Producto no encontrado." << std::endl;
                            }
                            break;
                        }
                        case 6:
                            system("cls");
                            std::cout << "|| Volviendo al Menu Principal.\n";
                            for (const auto& entidad : registro) {
                                const Producto* producto = dynamic_cast<const Producto*>(entidad);
                                if (producto) {
                                    producto->generarInformeEstado(registro);
                                }
                            }

                            break;
                        default:
                            std::cout << "|| Opcion invalida. Por favor, intente de nuevo." << std::endl;
                            break;
                    }
                } while (opcionProducto != 6);

                break;
            }
            case 4: {
                system("cls");
                int opcionFactura;
                do {
                    std::cout << "================================================================================================================\n";
                    std::cout << "||--------------------------------------------- GESTIONAR VENTAS ---------------------------------------------||" << std::endl;
                    std::cout << "================================================================================================================\n";
                    std::cout << "|| 1. Realizar una venta                                                                                      ||" << std::endl;
                    std::cout << "|| 2. Historial de venta                                                                                      ||" << std::endl;
                    std::cout << "|| 3. Eliminar una venta                                                                                      ||" << std::endl;
                    std::cout << "|| 4. Buscar por ID fact, fechayhora, ID cliente, ID vendedor o estadofact                                    ||" << std::endl;
                    std::cout << "|| 5. Informe general de ventas                                                                               ||" << std::endl;
                    std::cout << "|| 6. Regresar al Menu Principal                                                                              ||" << std::endl;
                    std::cout << "================================================================================================================\n";
                    std::cout << "|| Ingrese su opcion: ";
                    std::cin >> opcionFactura;

                    switch (opcionFactura) {
                        case 1: {
                            system("cls");
                            Factura factura;
                            int idCliente, idVendedor;
                            std::string fechaFactura;
                            float totalFactura = 0.0;
                            std::vector<std::pair<Producto, int>> productosVendidos;
                            std::cout << "================================================================================================================\n";
                            std::cout << "||---------------------------------------------- REALIZAR VENTA ----------------------------------------------||" << std::endl;
                            std::cout << "================================================================================================================\n";
                            time_t now = time(0);
                            struct tm tstruct;
                            char buf[80];
                            tstruct = *localtime(&now);
                            strftime(buf, sizeof(buf), "%d/%m/%Y %X", &tstruct);
                            fechaFactura = buf; // Establecer la fecha actual en el formato deseado

                            // Mostrar la fecha al usuario
                            std::cout << "|| Fecha de la venta: " << fechaFactura << std::endl;

                            // Mostrar lista de vendedores disponibles
                            std::cout << "\n|| Vendedores disponibles:" << std::endl;
                            for (Entidad* entidad : registro) {
                                Vendedor* vendedor = dynamic_cast<Vendedor*>(entidad);
                                if (vendedor) {
                                    std::cout << "|| ID: " << vendedor->getIdVendedor() << ", Nombre: " << vendedor->getNombre()
                                              << ", Telefono: " << vendedor->getTelefono() << ", Direccion: " << vendedor->getDireccion()
                                              << ", Correo: " << vendedor->getCorreo() << std::endl;
                                }
                            }

                            // Solicitar información del vendedor
                            std::cout << "\n|| Ingrese el ID del vendedor: ";
                            std::cin >> idVendedor;
                            factura.setIdVendedor(idVendedor);

                            // Verificar si el ID del vendedor existe
                            bool vendedorEncontrado = false;
                            for (Entidad* entidad : registro) {
                                Vendedor* vendedor = dynamic_cast<Vendedor*>(entidad);
                                if (vendedor && vendedor->getIdVendedor() == idVendedor) {
                                    std::cout << "\n|| Vendedor seleccionado:" << std::endl;
                                    std::cout << "|| ID: " << vendedor->getIdVendedor() << ", Nombre: " << vendedor->getNombre() << std::endl;
                                    vendedorEncontrado = true;
                                    break;
                                }
                            }
                            if (!vendedorEncontrado) {
                                std::cout << "|| Error: Vendedor no encontrado. Por favor, ingrese un ID valido." << std::endl;
                                // Salir del caso 1 y volver al menú de gestión de facturas
                                break;
                            }

                            // Mostrar lista de clientes disponibles
                            std::cout << "\n|| Clientes disponibles:" << std::endl;
                            for (const Entidad* entidad : registro) {
                                const Cliente* cliente = dynamic_cast<const Cliente*>(entidad);
                                if (cliente) {
                                    std::cout << "|| ID: " << cliente->getIdCliente() << ", Nombre: " << cliente->getNombre()
                                              << ", Telefono: " << cliente->getTelefono() << ", Direccion: " << cliente->getDireccion()
                                              << ", Correo: " << cliente->getCorreo() << std::endl;
                                }
                            }

                            // Solicitar información del cliente
                            std::cout << "\n|| Ingrese el ID del cliente: ";
                            std::cin >> idCliente;
                            factura.setIdCliente(idCliente);

                            // Verificar si el ID del cliente existe
                            bool clienteEncontrado = false;
                            for (const Entidad* entidad : registro) {
                                const Cliente* cliente = dynamic_cast<const Cliente*>(entidad);
                                if (cliente && cliente->getIdCliente() == idCliente) {
                                    std::cout << "\n|| Cliente seleccionado:" << std::endl;
                                    std::cout << "|| ID: " << cliente->getIdCliente() << ", Nombre: " << cliente->getNombre() << std::endl;
                                    clienteEncontrado = true;
                                    break;
                                }
                            }
                            if (!clienteEncontrado) {
                                std::cout << "|| Error: Cliente no encontrado. Por favor, ingrese un ID valido." << std::endl;
                                // Salir del caso 1 y volver al menú de gestión de facturas
                                break;
                            }

                            // Agregar productos a la venta
                            char continuar;
                            do {
                                std::cout << "\n|| Productos disponibles:" << std::endl;
                                for (int i = 0; i < registro.size(); ++i) {
                                    Producto* producto = dynamic_cast<Producto*>(registro[i]);
                                    if (producto) {
                                        std::string estadoProducto;
                                        switch (producto->getEstado()) {
                                            case DISPONIBLE:
                                                estadoProducto = "Disponible";
                                                break;
                                            case AGOTADO:
                                                estadoProducto = "Agotado";
                                                break;
                                            case POR_VENCER:
                                                estadoProducto = "Por vencer";
                                                break;
                                            case VENCIDO:
                                                estadoProducto = "Vencido";
                                                break;
                                            default:
                                                estadoProducto = "Desconocido";
                                        }
                                        std::cout << "|| ID: " << producto->getIdProducto()
                                                  << ", Nombre: " << producto->getNombre()
                                                  << ", Marca: " << producto->getMarca()
                                                  << ", Clasificacion: " << producto->getClasificacion()
                                                  << ", Cantidad: " << producto->getCantidad()
                                                  << ", Precio Unitario: " << producto->getPrecioVenta()
                                                  << ", Estado: " << estadoProducto << std::endl;
                                    }
                                }

                                std::cout << "\n|| Ingrese los IDs de los productos separados por espacios (Ejemplo: 1 2 3): ";
                                std::string productosIdsInput;
                                std::getline(std::cin >> std::ws, productosIdsInput); // Leer la línea completa, ignorando los espacios en blanco al inicio

                                std::istringstream iss(productosIdsInput);
                                int idProducto;
                                while (iss >> idProducto) {
                                    // Verificar si el ID del producto existe
                                    auto productoEncontrado = std::find_if(registro.begin(), registro.end(), [idProducto](Entidad* entidad) {
                                        Producto* producto = dynamic_cast<Producto*>(entidad);
                                        return producto && producto->getIdProducto() == idProducto;
                                    });
                                    if (productoEncontrado == registro.end()) {
                                        std::cout << "|| Error: Producto con ID " << idProducto << " no encontrado. Por favor, ingrese un ID válido." << std::endl;
                                        continue; // Continuar con el siguiente ID de producto
                                    }

                                    Producto* producto = dynamic_cast<Producto*>(*productoEncontrado);

                                    std::cout << "\n|| Producto seleccionado:" << std::endl;
                                    std::cout << "|| ID: " << producto->getIdProducto() << ", Nombre: " << producto->getNombre() << std::endl;

                                    int cantidad;
                                    std::cout << "|| Ingrese la cantidad vendida del producto con ID " << idProducto << ": ";
                                    std::cin >> cantidad;

                                    // Verificar si hay suficiente cantidad en el inventario
                                    if (cantidad > producto->getCantidad()) {
                                        std::cout << "|| Error: No hay suficiente cantidad en el inventario para esta venta." << std::endl;
                                        continue; // Continuar con el siguiente ID de producto
                                    }

                                    // Producto encontrado
                                    totalFactura += producto->getPrecioVenta() * cantidad;
                                    productosVendidos.push_back(std::make_pair(*producto, cantidad));

                                    // Descontar la cantidad vendida del inventario del producto
                                    producto->setCantidad(producto->getCantidad() - cantidad);

                                    if (producto->getCantidad() > 0) {
                                        producto->setEstado(DISPONIBLE);
                                    } else {
                                        producto->setEstado(AGOTADO);
                                        producto->setDisponible(false);
                                    }
                                }

                                std::cout << "|| ¿Desea agregar otro producto a la venta? (s/n): ";
                                std::cin >> continuar;
                            } while (continuar == 's' || continuar == 'S');


                            std::string formaPago;
                            std::cout << "\n|| Ingrese la forma de pago (Efectivo, Tarjeta, Transferencia, etc.): ";
                            std::cin >> formaPago;
                            factura.setFormaPago(formaPago);
                            // Crear factura
                            factura.setIdCliente(idCliente);
                            factura.setFechaFactura(fechaFactura);
                            factura.setTotalFactura(totalFactura);
                            for (int i = 0; i < productosVendidos.size(); ++i) {
                                factura.agregarProducto(productosVendidos[i].first, productosVendidos[i].second);
                            }
                            factura.setFormaPago(formaPago);
                            facturas.push_back(factura);
                            system("cls");
                            std::cout << "|| Venta realizada con exito." << std::endl;
                            factura.mostrarFactura(registro);

                            std::cout << "\n||============================================================================================================||\n";
                            std::cout << "||--------------------- Factura generada exitosamente con el ID N." << factura.getIdFactura() << " Gracias por su compra --------------------||" << std::endl;
                            std::cout << "||============================================================================================================||\n";
                            if (!facturas.empty()) {
                                facturas.back().guardarFacturaEnArchivotxt(registro); // Guardar la última factura agregada
                                facturas.back().guardarFacturaEnArchivocsv(registro);
                            } else {
                                std::cout << "No hay facturas para guardar." << std::endl;
                            }
                            for (auto& entidad : registro) {
                                Producto* producto = dynamic_cast<Producto*>(entidad);
                                if (producto && producto->getEstado() == AGOTADO) {
                                    producto->generarInformeAgotado(registro);
                                }
                            }
                            facturas.back().generarInformeBajaRotacion(registro,facturas);
                            break;
                        }
                        case 2: {
                            system("cls");
                            std::cout << "================================================================================================================\n";
                            std::cout << "||----------------------------------------- HISTORIAL DE LAS VENTAS ------------------------------------------||" << std::endl;
                            std::cout << "================================================================================================================\n";
                            if (facturas.empty()) {
                                std::cout << "|| No hay facturas registradas.                                                                               ||" << std::endl;
                            } else {
                                int contador = 1;
                                for (const auto& factura : facturas) {
                                    std::cout << "|| Factura #" << contador++ << ":" << std::endl;
                                    std::cout << "|| ID: " << factura.getIdFactura() << std::endl;
                                    std::cout << "|| Fecha y Hora: " << factura.getFechaFactura() << std::endl;

                                    bool vendedorEncontrado = false;
                                    std::string nombreVendedor;
                                    for (Entidad* entidad : registro) {
                                        Vendedor* vendedor = dynamic_cast<Vendedor*>(entidad);
                                        if (vendedor && vendedor->getIdVendedor() == factura.getIdVendedor()) {
                                            nombreVendedor = vendedor->getNombre();
                                            vendedorEncontrado = true;
                                            break;
                                        }
                                    }

                                    if (vendedorEncontrado) {
                                        std::cout << "|| Nombre del Vendedor: " << nombreVendedor << std::endl;
                                    } else {
                                        std::cout << "|| Vendedor no encontrado" << std::endl;
                                    }

                                    bool clienteEncontrado = false;
                                    std::string nombreCliente;
                                    for (Entidad* entidad : registro) {
                                        Cliente* cliente = dynamic_cast<Cliente*>(entidad);
                                        if (cliente && cliente->getIdCliente() == factura.getIdCliente()) {
                                            nombreCliente = cliente->getNombre();
                                            clienteEncontrado = true;
                                            break;
                                        }
                                    }

                                    if (clienteEncontrado) {
                                        std::cout << "|| Nombre del Cliente: " << nombreCliente << std::endl;
                                    } else {
                                        std::cout << "|| Cliente no encontrado" << std::endl;
                                    }

                                    std::cout << "|| Forma de pago: " << factura.getFormaPago() << std::endl;
                                    std::cout << "||   Cantidad de Productos comprados: " << factura.getProductos().size() << std::endl;
                                    std::cout << "||   Detalles de los Productos:" << std::endl;
                                    for (const auto& par : factura.getProductos()) {
                                        const Producto& producto = par.first;
                                        int cantidad = par.second;
                                        std::cout << "||     ID del Producto: " << producto.getIdProducto()
                                                  << ", Nombre: " << producto.getNombre()
                                                  << ", Precio Unitario: " << producto.getPrecioVenta()
                                                  << ", Cantidad: " << cantidad << std::endl;
                                    }

                                    std::cout << "|| Total de la Venta: " << factura.getTotalFactura() << std::endl;
                                    std::cout << "\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

                                    std::cout << std::endl;
                                }
                            }
                            break;
                        }
                        case 3: {
                            system("cls");
                            std::cout << "================================================================================================================\n";
                            std::cout << "||---------------------------------------------- ELIMINAR VENTA ----------------------------------------------||" << std::endl;
                            std::cout << "================================================================================================================\n";
                            bool facturaEncontrada = false;
                            int idFacturaEliminar;
                            std::cout << "|| Ingrese el ID de la factura a eliminar: ";
                            std::cin >> idFacturaEliminar;

                            int n = facturas.size();
                            for(int i = 0; i < n; i++){
                                if(facturas[i].getIdFactura() == idFacturaEliminar){
                                    facturaEncontrada = true;
                                    std::cout << "|| Datos de la Factura:" << std::endl;
                                    std::cout << "|| ID factura: " << facturas[i].getIdFactura() << std::endl;
                                    std::cout << "|| Fecha de registro: " << facturas[i].getFechaFactura() << std::endl;

                                    // Buscar y mostrar el nombre del vendedor
                                    bool vendedorEncontrado = false;
                                    std::string nombreVendedor;
                                    for (Entidad* entidad : registro) {
                                        Vendedor* vendedor = dynamic_cast<Vendedor*>(entidad);
                                        if (vendedor && vendedor->getIdVendedor() == facturas[i].getIdVendedor()) {
                                            nombreVendedor = vendedor->getNombre();
                                            vendedorEncontrado = true;
                                            break;
                                        }
                                    }

                                    if (vendedorEncontrado) {
                                        std::cout << "|| Nombre del Vendedor: " << nombreVendedor << std::endl;
                                    } else {
                                        std::cout << "|| Vendedor no encontrado" << std::endl;
                                    }

                                    // Buscar y mostrar el nombre del cliente
                                    bool clienteEncontrado = false;
                                    std::string nombreCliente;
                                    for (Entidad* entidad : registro) {
                                        Cliente* cliente = dynamic_cast<Cliente*>(entidad);
                                        if (cliente && cliente->getIdCliente() == facturas[i].getIdCliente()) {
                                            nombreCliente = cliente->getNombre();
                                            clienteEncontrado = true;
                                            break;
                                        }
                                    }

                                    if (clienteEncontrado) {
                                        std::cout << "|| Nombre del Cliente: " << nombreCliente << std::endl;
                                    } else {
                                        std::cout << "|| Cliente no encontrado" << std::endl;
                                    }

                                    // Eliminar la factura del vector
                                    facturas[i].eliminarFactura(facturas);
                                    facturas.erase(facturas.begin() + i);
                                    break;
                                }
                            }

                            if (!facturaEncontrada) {
                                std::cout << "|| Factura no encontrada." << std::endl;
                            }
                            break;
                        }

                        case 4: {
                            system("cls");
                            std::cout << "================================================================================================================\n";
                            std::cout << "||---------------------------------------------- BUSCAR FACTURA ----------------------------------------------||" << std::endl;
                            std::cout << "================================================================================================================\n";
                            std::string opcionBusqueda;
                            std::cout << "|| Elija como buscar la factura (if: ID Factura, fhf: fecha y hora Fctura,iv: ID Vendedor,ic: ID Cliente): ";
                            std::cin >> opcionBusqueda;

                            if (opcionBusqueda == "if") {
                                int idFacturaBusqueda;
                                std::cout << "|| Ingrese el ID de la factura a buscar: ";
                                std::cin >> idFacturaBusqueda;
                                bool facturaEncontrada = false;
                                for (Factura& factura : facturas) {
                                    if (factura.getIdFactura() == idFacturaBusqueda) {
                                        factura.mostrarFactura(registro);
                                        facturaEncontrada = true;
                                        break;
                                    }
                                }

                                if (!facturaEncontrada) {
                                    std::cout << "|| Factura no encontrada." << std::endl;
                                }
                            } else if (opcionBusqueda == "fhf") {
                                std::string fechaHoraBusqueda;
                                std::cout << "|| Ingrese la fecha y hora (en formato dd/mm/yyyy hh:mm:ss): ";
                                std::cin.ignore();
                                std::getline(std::cin, fechaHoraBusqueda);
                                bool facturaEncontrada = false;
                                for (Factura& factura : facturas) {
                                    if (factura.getFechaFactura() == fechaHoraBusqueda) {
                                        factura.mostrarFactura(registro);
                                        facturaEncontrada = true;
                                    }
                                }

                                if (!facturaEncontrada) {
                                    std::cout << "|| No se encontraron facturas en la fecha y hora especificadas." << std::endl;
                                }
                            } else if (opcionBusqueda == "iv") {
                                int idVendedorBusqueda;
                                std::cout << "|| Ingrese el ID del vendedor: ";
                                std::cin >> idVendedorBusqueda;
                                bool facturaEncontrada = false;
                                for (Factura& factura : facturas) {
                                    if (factura.getIdVendedor() == idVendedorBusqueda) {
                                        factura.mostrarFactura(registro);
                                        facturaEncontrada = true;
                                    }
                                }
                                if (!facturaEncontrada) {
                                    std::cout << "|| No se encontraron facturas asociadas al vendedor con ID: " << idVendedorBusqueda << std::endl;
                                }
                            } else if (opcionBusqueda == "ic") {
                                int idClienteBusqueda;
                                std::cout << "|| Ingrese el ID del cliente: ";
                                std::cin >> idClienteBusqueda;
                                bool facturaEncontrada = false;
                                for (Factura& factura : facturas) {
                                    if (factura.getIdCliente() == idClienteBusqueda) {
                                        factura.mostrarFactura(registro);
                                        facturaEncontrada = true;
                                    }
                                }

                                if (!facturaEncontrada) {
                                    std::cout << "|| No se encontraron facturas para el cliente especificado." << std::endl;
                                }
                            } else {
                                std::cout << "|| Opcion invalida. Por favor, intente de nuevo." << std::endl;
                            }
                            break;
                        }
                        case 5:{
                            void generarInformeVentas(const std::vector<Factura>& facturas);
                            generarInformeVentas(facturas);
                            break;
                        }
                        case 6:
                            system("cls");
                            std::cout << "|| Volviendo al Menu Principal.\n";
                            break;
                        default:
                            std::cout << "|| Opcion invalida. Por favor, intente de nuevo." << std::endl;
                            break;
                    }
                } while (opcionFactura != 6);

                break;
            }
            case 5:
                std::cout << "|| Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "|| Opcion invalida. Por favor, intente de nuevo." << std::endl;
                break;
        }
    } while (opcion != 5);

    return 0;
}


