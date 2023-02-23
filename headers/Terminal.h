//
// Created by emanuel on 02/02/23.
//

#ifndef FINALAYEDD2023_TERMINAL_H
#define FINALAYEDD2023_TERMINAL_H


#include "Pagina.h"
#include <cstdlib>
#include "Router.h"
#include <string.h>
#include <iostream>
#include <unistd.h>
#include "Ruta.h"

//Tamaño de las paginas en MB
#define TAM_MAX_PAG 20
#define TAM_MIN_PAG 15

using namespace std;

class Router;

class Terminal: public Ruta{
    uint8_t ipTerminal;
    uint8_t ipRouter;
    Router* routerPadre;


    Cola<Pagina>* pagRecibidas = new Cola<Pagina>();    //Cola de las paginas que la Terminal recibe del Router
    inline static Lista<IP>* tabla = new Lista<IP>(new Nodo<IP>(NULL));   //Lista de todas las terminales existentes
                                                        //Variable creada para darle un destino existente a las paginas que se van generando
    friend class Router;

public:
    Cola<Pagina>* pagPendiendes = new Cola<Pagina>();   //Cola de las paginas que se generaron para enviar a los Routers


    Terminal(uint8_t  ipTerminal, Router* router);
    void generarPagina();
    uint8_t getIpTerminal() { return ipTerminal; };
    uint8_t getIpRouter() { return ipRouter; };
    void addPagina(Pagina* pag) { pagRecibidas->encolar(pag); };
    Router* getRouter() { return routerPadre; };
    void enviarPaginas();
    void imprimirPaginas();

};

#endif //FINALAYEDD2023_TERMINAL_H
