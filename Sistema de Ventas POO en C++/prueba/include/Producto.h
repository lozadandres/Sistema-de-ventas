#ifndef PRODUCTO_H
#define PRODUCTO_H
#include "Fecha.h"
#include "Entidad.h"
#include <string>
#include <vector>

enum EstadoProducto {
    DISPONIBLE,
    AGOTADO,
    POR_VENCER,
    VENCIDO
};
class Producto : public Entidad {
    private:
        static int contadorID;
        int idProducto;
        std::string nombre;
        std::string marca;
        std::string clasificacion;
        int cantidad;
        float precioVenta;
        Fecha fechaVencimiento;
        EstadoProducto estado;
        bool disponible;

    public:
        Producto();
        void setNombre(const std::string& nombre);
        void setMarca(const std::string& marca);
        void setClasificacion(const std::string& clasificacion);
        void setCantidad(int cantidad);
        void setPrecioVenta(float precio);
        void setFechaVencimiento(const Fecha& fecha);

        void setEstado(EstadoProducto nuevoEstado) {
            estado = nuevoEstado;
        }

        void setDisponible(bool disponible) {
            this->disponible = disponible;
        }

        int getIdProducto() const;
        const std::string& getNombre() const;
        const std::string& getMarca() const;
        const std::string& getClasificacion() const;
        int getCantidad() const;
        float getPrecioVenta() const;
        const Fecha& getFechaVencimiento() const;

        EstadoProducto getEstado() const {
            return estado;
        }
        void generarInformeAgotado(const std::vector<Entidad*>& registro) const;

        void generarInformeEstado(const std::vector<Entidad*>& registro) const;

        bool campoCoincide(const std::string& valor, const std::string& campo) const {
            if (campo == "nombre") {
                return nombre == valor;
            } else if (campo == "marca") {
                return marca == valor;
            } else if (campo == "clasificación") {
                return clasificacion == valor;
            }
            return false;
        }


        void crearProducto();
        void mostrarProducto() const;
        void modificarProducto();
        void eliminarProducto(std::vector<Producto>& productos);

        void ingresarRegistro() override;
        void listarRegistros(const std::vector<Entidad*>& registros) const override;
        void actualizarRegistro() override;
        //virtual void eliminarRegistro(std::vector<Entidad*>& registros) override;

};
bool buscarProducto(const std::vector<Producto>& productos, const std::string& criterio, bool buscarPorID, Producto& productoEncontrado);
bool buscarPorMarcaOClasificacion(const std::vector<Producto>& productos, const std::string& criterio, bool buscarPorMarca, Producto& productoEncontrado);
#endif // PRODUCTO_H

