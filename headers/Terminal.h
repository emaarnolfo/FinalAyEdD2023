//
// Created by emanuel on 02/02/23.
//

#ifndef FINALAYEDD2023_TERMINAL_H
#define FINALAYEDD2023_TERMINAL_H

#include "Listas.h"
#include "Pagina.h"
#include <cstdlib>
#include <map>

using namespace std;

class Terminal {
    int IP_terminal;
    Terminal* next;
    Cola<Pagina>* pagRecibidas;             //Cola de las paginas que va recibiendo
    Cola<Pagina>* pagPendiendes;            //Cola de las paginas que genero para enviar
    static Lista<struct IP>* tabla;          //Lista de todas las terminales existentes

public:
    Terminal(uint8_t IP_terminal, uint8_t IP_router);
    Pagina generarPagina();
};

Terminal::Terminal(uint8_t IP_terminal, uint8_t IP_router) {
    this->IP_terminal = IP_terminal;
    next = NULL;
    struct IP nuevo = {IP_terminal, IP_router};

    if(tabla == NULL){
        tabla = new Lista<struct IP>();
    }

    tabla->add(nuevo);
}

Pagina Terminal::generarPagina() {

    int ID_pag = 1 + rand() % 1000;             //Genera un ID aleatorio entre 1 y 1000 para identificar la pagina
    int peso = 1 + rand() %50;                  //Genera un peso aleatorio para la pagina
    int random = 1 + rand() % tabla->size();    //Cantidad de terminales (posibltes destinos)

    struct IP destino = tabla->get(random);   //Devuelve un destino que corresponde a alguna terminal random

    Pagina nuevaPag = Pagina(peso, destino);

    return nuevaPag;
}

#endif //FINALAYEDD2023_TERMINAL_H
