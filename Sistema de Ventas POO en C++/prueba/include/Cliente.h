#ifndef CLIENTE_H
#define CLIENTE_H
#include "Entidad.h"
#include "Persona.h"
#include <string>
#include <vector>

class Cliente : public Entidad, public Persona {
    private:
        static int contadorID;
        int idCliente;

    public:
        Cliente();
        int getIdCliente() const;

        void ingresarRegistro() override;
        void listarRegistros(const std::vector<Entidad*>& registros) const override;
        void actualizarRegistro() override;
        //void eliminarRegistro(std::vector<Entidad*>& registros) override;


        void crearCliente();
        void mostrarCliente() const;
        void mostrarCliente(std::ofstream& archivo) const;
        void modificarCliente();
        void eliminarCliente(std::vector<Cliente>& clientes);
};
bool buscarCliente(const std::vector<Cliente>& clientes, const std::string& criterio, bool buscarPorID, Cliente& clienteEncontrado);

#endif // CLIENTE_H

