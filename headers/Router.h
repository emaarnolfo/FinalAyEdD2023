//
// Created by emanuel on 24/01/23.
//

#ifndef FINALAYEDD_ROUTER_H
#define FINALAYEDD_ROUTER_H

#include <iostream>

class Arista;
class Terminal;

class Router {
public:
    short int IP;
    Router* next;
    Arista* arista;
    Terminal* terminal;

    friend class Arista;

    Router(short int IP);
};

class Terminal: public Router {

};

#endif //FINALAYEDD_ROUTER_H
