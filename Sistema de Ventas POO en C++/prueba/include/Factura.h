#ifndef FACTURA_H
#define FACTURA_H
#include "Entidad.h"
#include <vector>
#include "Producto.h"
#include "Vendedor.h"
#include "Cliente.h"


class Factura /*: public Entidad*/ {
    private:
        static int contadorID;
        int idFactura;
        int idVendedor;
        int idCliente;
        std::string fechaFactura;
        float totalFactura;
        std::string formaPago;
        std::vector<std::pair<Producto, int>> productos;


    public:
        Factura();
        void setIdVendedor(int idVendedor);
        void setIdCliente(int idCliente);
        void setFechaFactura(const std::string& fecha);
        void setTotalFactura(float total);
        void setFormaPago(const std::string& formaPago);

        int getIdFactura() const;
        int getIdVendedor() const;
        int getIdCliente() const;
        const std::string& getFechaFactura() const;
        float getTotalFactura() const;
        std::string getFormaPago() const;

        void agregarProducto(const Producto& producto, int cantidad);
        void guardarFacturaEnArchivotxt(const std::vector<Entidad*>& registros) const;
        void guardarFacturaEnArchivocsv(const std::vector<Entidad*>& registros) const;
        void mostrarFactura(const std::vector<Entidad*>& registros) const;
        void eliminarFactura(std::vector<Factura>& facturas);

        const std::vector<std::pair<Producto, int>>& getProductos() const {
            return productos;
        }


        void generarInformeVentas(const std::vector<Factura>& facturas);
        void generarInformeBajaRotacion(const std::vector<Entidad*>& registro, const std::vector<Factura>& facturas);


         // Datos estáticos de la farmacia
        static const int ID_FARMACIA = 1;  // Ejemplo de ID de la farmacia
        static std::string NOMBRE_FARMACIA;
        static std::string DIRECCION_FARMACIA;
        static std::string TELEFONO_FARMACIA;
        static std::string CORREO_FARMACIA;
        static std::string HORARIO_FARMACIA;
};

#endif // FACTURA_H
