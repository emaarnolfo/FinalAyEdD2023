//
// Created by emanuel on 02/02/23.
//

#ifndef FINALAYEDD2023_TERMINAL_H
#define FINALAYEDD2023_TERMINAL_H

#include "Listas.h"
#include "Pagina.h"
#include <cstdlib>


using namespace std;

class Terminal {
    std::uint8_t ipTerminal;
    std::uint8_t ipRouter;
    Terminal* next;

    Cola<Pagina>* pagRecibidas;                         //Cola de las paginas que va recibiendo la Terminal
    Cola<Pagina>* pagPendiendes;                        //Cola de las paginas que generó para enviar a los Routers
    inline static Lista<IP>* tabla = new Lista<IP>();   //Lista de todas las terminales existentes
                                                        //Variable creada para darle un destino existente a las paginas que se van generando
public:
    Terminal(std::uint8_t  ipTerminal, std::uint8_t  ipRouter);
    Pagina* generarPagina();
};

#endif //FINALAYEDD2023_TERMINAL_H
