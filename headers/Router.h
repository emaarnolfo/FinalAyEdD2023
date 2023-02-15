//
// Created by emanuel on 24/01/23.
//

#ifndef FINALAYEDD_ROUTER_H
#define FINALAYEDD_ROUTER_H

#include <iostream>
#include "Terminal.h"
#include "Paquete.h"
#include "Arista.h"
#include <map>

using namespace std;

class Arista;
class Terminal;

class Router {
private:
    map<int, int> pesoColas;
    void getAnchoBandaColas();
    void borrarPaquetes(int idPag, Nodo<Paquete>* ant, Lista<Paquete>* lista);
    void crearPaquetes(Pagina* pagina);
    void imprimirIntercalado();
    Router* getRoutVec(uint8_t ipRouter, Lista<Router>* r_vecinos);
    Router* getVecino(uint8_t ipRouter) { return getRoutVec(ipRouter, routersVecinos); };

    void borrarPaq(int idPag, Lista<Paquete>* lista){
        this->borrarPaquetes(idPag, nullptr, lista);
    };

public:
    uint8_t IP;
    Arista* arista;

    Lista<Paquete>* paqNuevos = new Lista<Paquete>();           //Paquetes que llegan de los Routers vecinos
    map<int, Lista<Paquete>*> colaEnvios;                       //Cola de envios para cada Router vecino sin intercalar
    Lista<Paquete>* paqEnDestino = new Lista<Paquete>();        //Lista de Paquetes en el Router destino, en espera para armar la Pagina
    map<int, Lista<Paquete>*> paqListos;                        //Paquetes listos e intercalados para enviar

    Lista<Router>* routersVecinos = new Lista<Router>();        //Lista de todos los Routers vecinos
    Lista<Terminal>* listaTerminales = new Lista<Terminal>();   //Lista de todas las terminales conectadas al Router

    Cola<Pagina>* pagRecibidas = new Cola<Pagina>();            //Paginas que llegan desde las terminales. Las cuales se deben dividir en paquetes
    Cola<Pagina>* pagListas = new Cola<Pagina>();               //Paginas listas para mandar a la terminal correspondiente

    map<int, Router*> tablaEnrutamiento;                        //Indica a que Router enviar los paquetes segun su destino

    Router* next;

    friend class Arista;

    Router(uint8_t IP);
    void agregarTerminal(Terminal* terminal);
    void desarmarPaginas();                   //Se puede implementar con paquetes aleatorios
    void ordenarPaquetes();                   //Los paquetes que se encuentran en el router destino pasan a la lista de paqEnDestino
    void armarPaginas();
    void enviarPaquetes();
    void enviarPaginas();
    void imprimirPaqs();
    void intercalarPaquetes();
    Arista* getArista(uint8_t ipDestino);



    //Pasar a privado
    Terminal* getTerminal(uint8_t ipTerminal);
};

#endif //FINALAYEDD_ROUTER_H
