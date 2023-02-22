//
// Created by emanuel on 21/02/23.
//

#ifndef FINALAYEDD2023_RUTA_H
#define FINALAYEDD2023_RUTA_H

#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;

class Ruta
{
public:
    virtual char* rutaActual()
    {
        // Obtiene la ruta actual
        char* buf = get_current_dir_name();

        // Convierte la ruta actual a una cadena de C++
        string pathAlt(buf);

        // Encuentra la última aparición de la barra diagonal
        size_t pos = pathAlt.find_last_of("/");

        if (pos != string::npos)        // Si se encontró la barra diagonal
            pathAlt.erase(pos);         // Elimina todo despues de la ultima barra diagonal

        string path2 = pathAlt;
        char* path = strcpy(new char[path2.length() + 1], path2.c_str());

        return path;
    }
};

#endif //FINALAYEDD2023_RUTA_H
