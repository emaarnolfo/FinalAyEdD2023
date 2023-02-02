//
// Created by emanuel on 31/01/23.
//

#ifndef FINALAYEDD2023_PAGINA_H
#define FINALAYEDD2023_PAGINA_H

#include "IP_Struct.h"
#include <map>

using namespace std;

class Pagina {
    int id;
    int peso;
    struct IP destino;
    inline static int contPaginas = 1;
public:

    //Constructor
    Pagina(int peso, IP destino)
        : peso(peso), destino(destino) {
        id = contPaginas++;
    }

    //Getters
    int getId() const { return id; }
    int getPeso() const { return peso; }
    IP getDestino() const { return destino; }

};

class Paquete: public Pagina {
    int ID_paq;
    int peso_paq;
    inline static int contPaquetes = 1;

public:
    //Constructor
    Paquete(int peso, const IP &destino, int idPaq, int pesoPaq) : Pagina(peso, destino),  peso_paq(pesoPaq){
        ID_paq = contPaquetes ++;
    }

    //Getters
    int getIdPaq() const { return ID_paq; }
    int getPesoPaq() const { return peso_paq; }

};

#endif //FINALAYEDD2023_PAGINA_H
