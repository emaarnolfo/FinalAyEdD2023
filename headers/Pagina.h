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
    struct IP destino;
    inline static int contPaginas = 1;          //Variable estatica para generar ID diferentes en cada instancia de la clase
public:
    Pagina(int peso, IP destino);

    //Getters
    int getId() const { return id; }
    int getPeso() const { return peso; }
    IP getDestino() const { return destino; }
    Cola<Paquete>* desarmarPagina();
};



#endif //FINALAYEDD2023_PAGINA_H