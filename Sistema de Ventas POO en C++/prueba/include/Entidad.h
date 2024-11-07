#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <vector>

enum class TipoEntidad {
    Cliente,
    Vendedor,
    Proveedor,
    Producto
}; // <-- Missing semicolon here

class Entidad
{
    public:
        Entidad(TipoEntidad _tipo);
        virtual ~Entidad();

        virtual void ingresarRegistro() = 0;
        virtual void listarRegistros(const std::vector<Entidad*>& registros) const = 0;
        virtual void actualizarRegistro() = 0;
        //virtual void eliminarRegistro(std::vector<Entidad*>& registros) = 0;

    protected:

    private:
        TipoEntidad tipo;
};


#endif // ENTIDAD_H
