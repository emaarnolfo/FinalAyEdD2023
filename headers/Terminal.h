//
// Created by emanuel on 02/02/23.
//

#ifndef FINALAYEDD2023_TERMINAL_H
#define FINALAYEDD2023_TERMINAL_H


#include "Pagina.h"
#include <cstdlib>


using namespace std;

class Terminal {
    uint8_t ipTerminal;
    uint8_t ipRouter;

    Cola<Pagina>* pagRecibidas = new Cola<Pagina>();    //Cola de las paginas que va recibiendo la Terminal
    Cola<Pagina>* pagPendiendes = new Cola<Pagina>();   //Cola de las paginas que generó para enviar a los Routers
    inline static Lista<IP>* tabla = new Lista<IP>(new Nodo<IP>(NULL));   //Lista de todas las terminales existentes
                                                        //Variable creada para darle un destino existente a las paginas que se van generando
public:
    Terminal(uint8_t  ipTerminal, uint8_t  ipRouter);
    void generarPagina();
};

#endif //FINALAYEDD2023_TERMINAL_H
