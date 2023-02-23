//
// Created by emanuel on 21/02/23.
//

#ifndef FINALAYEDD2023_RUTA_H
#define FINALAYEDD2023_RUTA_H

#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;

/*
 * Clase abstracta que implementan todas las clases
 * que necesiten imprimir o leer en archivos externos
 */
class Ruta
{
public:
    //Devuelve la ruta en la cual se encuentra el proyecto
    virtual char* rutaActual()
    {
        //Obtiene la ruta actual
        char* buf = get_current_dir_name();

        //Convierte la ruta actual a una cadena de C++
        string pathAlt(buf);

        //Encuentra la última aparición de la barra diagonal
        size_t pos = pathAlt.find_last_of("/");

        if (pos != string::npos)        //Si se encontró la barra diagonal
            pathAlt.erase(pos);         //Elimina todo despues de la ultima barra diagonal

        //Copia la cadena en una nueva area de memoria asiganada dinamicamente y lo devuelve
        char* path = strcpy(new char[pathAlt.length() + 1], pathAlt.c_str());

        return path;
    }
};

#endif //FINALAYEDD2023_RUTA_H
