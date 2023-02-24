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



using namespace std;

class Router;

class Terminal: public Ruta{
    uint8_t ipTerminal;         //IP de 1 byte de la terminal
    //uint8_t ipRouter;
    Router* routerPadre;        //Puntero al Router al cual se esta conectado


    Cola<Pagina>* pagRecibidas = new Cola<Pagina>();                            //Cola de las paginas que la Terminal recibe del Router
    inline static Lista<IP>* tabla = new Lista<IP>(new Nodo<IP>(NULL));   //Lista de todas las terminales existentes
                                                                                //Variable creada para darle un destino existente a las paginas que se van generando
    friend class Router;

public:
    Cola<Pagina>* pagPendiendes = new Cola<Pagina>();   //Cola de las paginas que se generaron y se deben enviar al Router padre

    Terminal(uint8_t  ipTerminal, Router* router);
    void generarPagina();                                               //Genera paginas de tamaño y destino aleatorio
    uint8_t getIpTerminal() { return ipTerminal; };                     //Obtiene la ip de la terminal
    uint8_t getIpRouter();                                              //Obtiene la ip del router padre
    void addPagina(Pagina* pag) { pagRecibidas->encolar(pag); };     //Agrega una pagina que recibe del Router por parametro
    Router* getRouter() { return routerPadre; };                        //Devuelve el puntero al Router padre
    void enviarPaginas();                                               //Envia las paginas al Router padre
    void imprimirPaginas();                                             //Imprime las paginas que se pendientes de envio y las recibidas
};

#endif //FINALAYEDD2023_TERMINAL_H
