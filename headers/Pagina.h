//
// Created by emanuel on 31/01/23.
//

#ifndef FINALAYEDD2023_PAGINA_H
#define FINALAYEDD2023_PAGINA_H

#include "IP_Struct.h"
#include "Listas.h"

using namespace std;

class Paquete;

class Pagina {
    int id;
    int peso;
    IP destino;
    inline static int contPaginas = 1;          //Variable estatica para generar ID diferentes en cada instancia de la clase

public:
    Pagina(int peso, IP destino);               //Constructor con ID automatica. Se utiliza para crar nuevas paginas
    Pagina(int idPag, int peso, IP destino);    //Constructor con ID por parametro. Se utliza para rearmar paginas en el Router destinos

    //Getters
    int getId() { return id; }
    int getPeso() { return peso; }
    IP getDestino() { return destino; }
    void setID(int id) { this->id = id; };
};



#endif //FINALAYEDD2023_PAGINA_H