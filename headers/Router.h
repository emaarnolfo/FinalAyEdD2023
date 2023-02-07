//
// Created by emanuel on 24/01/23.
//

#ifndef FINALAYEDD_ROUTER_H
#define FINALAYEDD_ROUTER_H

#include <iostream>
#include "Terminal.h"
#include "Paquete.h"

using namespace std;

class Arista;
class Terminal;

class Router {
private:
    void borrarPaquetes(int idPag, Nodo<Paquete>* ant, Lista<Paquete>* lista);

public:
    uint8_t IP;
    Router* next;
    Arista* arista;

    Lista<Terminal>* listaTerminales = new Lista<Terminal>();       //Lista de todas las terminales conectadas al Router
    Cola<Pagina>* pagRecibidas = new Cola<Pagina>();                //Paginas que llegan desde las terminales. Las cuales se deben dividir en paquetes
    Cola<Pagina>* pagListas = new Cola<Pagina>();                   //Paginas listas para mandar a la terminal correspondiente
    Lista<Paquete>* paquetes = new Lista<Paquete>();                //Paquetes listos para enviar al siguiente Router de acuerdo a su camino
    Lista<Paquete>* paqEnDestino = new Lista<Paquete>();            //Lista de Paquetes en el Router destino, en espera para armar la Pagina


    friend class Arista;

    Router(uint8_t IP);
    void agregarTerminal(Terminal* terminal);
    void desarmarPagina();
    void armarPaginas();
    void borrarPaq(int idPag, Lista<Paquete>* lista) { this->borrarPaquetes(idPag, nullptr, lista); };
};

#endif //FINALAYEDD_ROUTER_H
