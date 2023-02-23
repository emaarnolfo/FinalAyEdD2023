//
// Created by emanuel on 24/01/23.
//

#ifndef FINALAYEDD_ROUTER_H
#define FINALAYEDD_ROUTER_H

#include <iostream>
#include "Terminal.h"
#include "Paquete.h"
#include "Arista.h"
#include "Ruta.h"
#include <map>

//Tamaño de los paquetes de las paginas en KB
#define TAM_MAX_PAQ 2500
#define TAM_MIN_PAQ 1000

using namespace std;

class Arista;
class Terminal;

class Router: public Ruta{
private:
    int getPesoLista(Lista<Paquete>* lista);
    void imprimirNuevos();
    void imprimirEnDestino();
    void borrarPaquetes(int idPag, Nodo<Paquete>* ant, Lista<Paquete>* lista);
    void crearPaquetes(Pagina* pagina);
    void imprimirIntercalado();
    Router* getRoutVec(uint8_t ipRouter, Lista<Router>* r_vecinos);
    Router* getVecino(uint8_t ipRouter) { return getRoutVec(ipRouter, routersVecinos); };
    void intercalarPaquetes(map<int, Lista<Paquete>*> mapaAux);
    void borrarPaq(int idPag, Lista<Paquete>* lista){
        this->borrarPaquetes(idPag, nullptr, lista);
    };

public:
    uint8_t IP;
    Arista* arista;

    Lista<Paquete>* paqNuevos = new Lista<Paquete>();           //Paquetes que llegan de los Routers vecinos
    map<int, Lista<Paquete>*> colaEnvios;                       //Cola de envios para cada Router vecino sin intercalar
    Lista<Paquete>* paqEnDestino = new Lista<Paquete>();        //Lista de Paquetes en el Router destino, en espera para armar la Pagina

    Lista<Router>* routersVecinos = new Lista<Router>();        //Lista de todos los Routers vecinos
    Lista<Terminal>* listaTerminales = new Lista<Terminal>();   //Lista de todas las terminales conectadas al Router

    Cola<Pagina>* pagRecibidas = new Cola<Pagina>();            //Paginas que llegan desde las terminales. Las cuales se deben dividir en paquetes
    Cola<Pagina>* pagListas = new Cola<Pagina>();               //Paginas listas para mandar a la terminal correspondiente

    map<int, Router*> tablaEnrutamiento;                        //Indica a que Router enviar los paquetes segun su destino

    Router* next;

    friend class Arista;

    Router(uint8_t IP);
    void agregarTerminal(Terminal* terminal);
    void desarmarPaginas();
    void ordenarPaquetes();
    void armarPaginas();
    void enviarPaquetes();
    void enviarPaginas();
    void imprimirPaqs(int numCiclos);
    void calcularCiclos();


    Arista* getArista(uint8_t ipDestino);
    Terminal* getTerminal(uint8_t ipTerminal);
};

#endif //FINALAYEDD_ROUTER_H
