//
// Created by emanuel on 03/02/23.
//

#include "../headers/Terminal.h"

//CONSTRUCTOR de Terminal
Terminal::Terminal(std::uint8_t  ipTerminal, std::uint8_t  ipRouter){
    this->ipRouter = ipRouter;
    this->ipTerminal = ipTerminal;
    next = nullptr;
    pagRecibidas = new Cola<Pagina>();
    pagPendiendes = new Cola<Pagina>();

    IP* nvoTerminal = new IP{ipTerminal, ipRouter};
    tabla->add(nvoTerminal);
}

Pagina* Terminal::generarPagina() {

    int peso = 1 + rand() %50;                  //Genera un peso aleatorio para la pagina
    int random = 1 + rand() % tabla->size();    //Cantidad de terminales (posibltes destinos)
    struct IP* destExistente = tabla->get(random);   //Devuelve un destino aleatorio que corresponde a alguna terminal existente

    IP destino = {destExistente->ipRouter, destExistente->ipTerminal};

    Pagina* nuevaPag = new Pagina(peso, destino);

    return nuevaPag;
}
