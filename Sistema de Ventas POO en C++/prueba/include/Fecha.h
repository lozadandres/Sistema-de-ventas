#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <string>

using namespace std;

class Fecha{
    private:
        int dia, mes, anio;
        string month;

    public:
        Fecha();
        virtual ~Fecha();

        std::string getFecha() const;
        void setFecha(int d, int m, int a);
        int getAnio() const;
        int getMes() const;
        int getDia() const;


};

#endif // FECHA_H
