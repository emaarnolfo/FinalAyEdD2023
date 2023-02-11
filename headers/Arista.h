//
// Created by emanuel on 24/01/23.
//

#ifndef FINALAYEDD_ARISTA_H
#define FINALAYEDD_ARISTA_H

#include <iostream>

class Router;

class Arista {
public:
    int ancho_de_banda;
    int peso;               //Para calcular el camino mas corto con dijkstra sin tener en cuenta el trafico
    int ciclos;             //Ciclos de demora debido al trafico
    Router* destino;
    Arista* next;

    friend class Router;

    Arista(int ancho_de_banda, Router* destino);
    //void calcPeso() { peso = 1/ancho_de_banda; };
};

#endif //FINALAYEDD_ARISTA_H