#ifndef VENDEDOR_H
#define VENDEDOR_H
#include "Entidad.h"
#include "Persona.h"
#include <string>
#include <vector>

class Vendedor : public Entidad, public Persona {
private:
    static int contadorID;
    int idVendedor;
    std::string area;

public:
    Vendedor();
    int getIdVendedor() const;

    void ingresarRegistro() override;
    void listarRegistros(const std::vector<Entidad*>& registros) const override;
    void actualizarRegistro() override;
    //void eliminarRegistro(const std::vector<Entidad*>& registros) const;

    void crearVendedor();
    void mostrarVendedor() const;
    void mostrarVendedor(std::ofstream& archivo) const;
    void modificarVendedor();
    void eliminarVendedor(std::vector<Vendedor>& vendedores);
};

bool buscarVendedor(const std::vector<Vendedor>& vendedores, const std::string& criterio, bool buscarPorID, Vendedor& vendedorEncontrado);

#endif // VENDEDOR_H

