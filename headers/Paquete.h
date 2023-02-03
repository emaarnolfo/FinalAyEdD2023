//
// Created by emanuel on 03/02/23.
//

#ifndef FINALAYEDD2023_PAQUETE_H
#define FINALAYEDD2023_PAQUETE_H

#include "Pagina.h"

class Paquete: public Pagina {
    int ID_paq;
    int peso_paq;
    inline static int contPaquetes = 1;

public:
    //Constructor
    Paquete(int peso, const IP destino, int pesoPaq) : Pagina(peso, destino), peso_paq(pesoPaq){
        ID_paq = contPaquetes ++;
    }

    //Getters
    int getIdPaq() const { return ID_paq; }
    int getPesoPaq() const { return peso_paq; }

};

#endif //FINALAYEDD2023_PAQUETE_H
