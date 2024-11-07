#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include "Persona.h"
#include <string>
#include <vector>

class Proveedor : /*public Entidad,*/ public Persona {
private:
    static int contadorID;
    int idProveedor;
    std::string tipoProducto;
    std::string rut;

public:
    Proveedor();
    int getIdProveedor() const;
    std::string getRut() const;

    //virtual void ingresarRegistro() override;
    //virtual void listarRegistros() const override;
    //virtual void actualizarRegistro() override;
    //virtual void eliminarRegistro(std::vector<Entidad*>& registros) override;

    void crearProveedor();
    void mostrarProveedor() const;
    void modificarProveedor();
    void eliminarProveedor(std::vector<Proveedor>& proveedores);
    void mostrarProductosProveedor() const;
};

bool buscarProveedor(const std::vector<Proveedor>& proveedores, const std::string& criterio, bool buscarPorID, Proveedor& proveedorEncontrado);

#endif // PROVEEDOR_H

