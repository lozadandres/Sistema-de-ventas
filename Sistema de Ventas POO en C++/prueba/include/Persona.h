#ifndef PERSONA_H
#define PERSONA_H
#include "Fecha.h"
#include <string>

class Persona {
    protected:
        std::string nombre;
        Fecha fechaNacimiento;
        std::string telefono;
        std::string direccion;
        std::string correo;

    public:
        Persona();
        void setNombre(const std::string& nombre);
        void setFechaNacimiento(const Fecha& fecha);
        void setTelefono(const std::string& telefono);
        void setDireccion(const std::string& direccion);
        void setCorreo(const std::string& correo);

        const std::string& getNombre() const;
        const Fecha& getFechaNacimiento() const;
        const std::string& getTelefono() const;
        const std::string& getDireccion() const;
        const std::string& getCorreo() const;


};

#endif // PERSONA_H

