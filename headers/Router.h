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

class Router {
public:
    short int IP;
    Router* next;
    Arista* arista;

    Lista<Terminal>* listaTerminales;  //Lista de todas las terminales conectadas al Router
    Cola<Pagina>* pagRecibidas;        //Paginas que llegan desde las terminales. Las cuales se deben dividir en paquetes
    Cola<Pagina>* pagListas;           //Paginas listas para mandar a la terminal correspondiente
    Lista<Paquete>* paquetes;           //Paquetes listos para enviar al siguiente Router de acuerdo a su camino
    Cola<Paquete>* paqEnDestino;       //Lista de Paquetes en el Router destino, en espera para armar la Pagina

    friend class Arista;
public:
    Router(short int IP);
    void desarmarPagina(Pagina* pagina);
    void armarPagina();
};

#endif //FINALAYEDD_ROUTER_H
