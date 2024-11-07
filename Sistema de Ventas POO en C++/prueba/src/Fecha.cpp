#include "Fecha.h"
#include <iostream>

Fecha::Fecha(){}

Fecha::~Fecha(){}

bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int diasEnMes(int mes, int anio) {
    switch (mes) {
        case 2:
            return esBisiesto(anio) ? 29 : 28;
        case 4: case 6: case 9: case 11:
            return 30;
        default:
            return 31;
    }
}

void Fecha::setFecha(int d, int m, int a) {
    // Validar que el año sea positivo (si lo deseas)
    if (a < 0) {
        std::cerr << "Error: El año no puede ser negativo." << std::endl;
        return;
    }

    // Validar el mes
    if (m < 1 || m > 12) {
        std::cerr << "Error: El mes debe estar entre 1 y 12." << std::endl;
        return;
    }

    // Validar el día
    int diasEnEsteMes = diasEnMes(m, a);
    if (d < 1 || d > diasEnEsteMes) {
        std::cerr << "Error: El día debe estar entre 1 y " << diasEnEsteMes << " para el mes y año proporcionados." << std::endl;
        return;
    }

    dia = d;
    mes = m;
    anio = a;

    switch(m) {
        case 1:  month = "Enero";      break;
        case 2:  month = "Febrero";    break;
        case 3:  month = "Marzo";      break;
        case 4:  month = "Abril";      break;
        case 5:  month = "Mayo";       break;
        case 6:  month = "Junio";      break;
        case 7:  month = "Julio";      break;
        case 8:  month = "Agosto";     break;
        case 9:  month = "Septiembre"; break;
        case 10: month = "Octubre";    break;
        case 11: month = "Noviembre";  break;
        case 12: month = "Diciembre";  break;
    }
}

std::string Fecha::getFecha() const {
    return std::to_string(dia) + " / " + month + " / " + std::to_string(anio);
}

int Fecha::getAnio() const {
    return anio;
}

int Fecha::getMes() const {
    return mes;
}

int Fecha::getDia() const {
    return dia;
}


