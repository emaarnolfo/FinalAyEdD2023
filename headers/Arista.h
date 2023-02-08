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
    Arista* next;
    Router* destino;

    friend class Router;

    Arista(int ancho_de_banda, Router* destino);
};

#endif //FINALAYEDD_ARISTA_H