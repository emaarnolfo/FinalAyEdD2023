//
// Created by emanuel on 24/01/23.
//

#ifndef FINALAYEDD_ARISTA_H
#define FINALAYEDD_ARISTA_H

#include <iostream>

class Router;

class Arista {
public:
    int ancho_de_banda;     //Ancho de banda en MegaByte. Especificado en archivo txt entre 25 MB a 100 MB aprox
    int peso;               //Inversa del ancho de banda, para definir los caminos mas cortos inciales
    double ciclos;          //Ciclos de demora debido al trafico
    Router* destino;
    Arista* next;

    friend class Router;

    Arista(int ancho_de_banda, Router* destino);
    //void calcPeso() { peso = 1/ancho_de_banda; };
};

#endif //FINALAYEDD_ARISTA_H