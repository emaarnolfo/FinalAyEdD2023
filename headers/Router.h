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



using namespace std;

class Arista;
class Terminal;

class Router: public Ruta{
private:
    int getPesoLista(Lista<Paquete>* lista);
    void imprimirNuevos();
    void borrarPaquetes(int idPag, Nodo<Paquete>* ant, Lista<Paquete>* lista);
    void crearPaquetes(Pagina* pagina);
    Router* getRoutVec(uint8_t ipRouter, Lista<Router>* r_vecinos);
    Router* getVecino(uint8_t ipRouter) { return getRoutVec(ipRouter, routersVecinos); };
    void intercalarPaquetes(map<int, Lista<Paquete>*> mapaAux);
    void borrarPaq(int idPag, Lista<Paquete>* lista){
        this->borrarPaquetes(idPag, nullptr, lista);
    };

public:
    uint8_t IP;
    Arista* arista;
    Router* next;

    Lista<Paquete>* paqNuevos = new Lista<Paquete>();           //Paquetes que llegan de los Routers vecinos
    map<int, Lista<Paquete>*> colaEnvios;                       //Cola de envios para cada Router vecino (con sus paquetes ya intercalados)
    Lista<Paquete>* paqEnDestino = new Lista<Paquete>();        //Lista de Paquetes en el Router destino, en espera de todos los paquetes necesarios para armar la Pagina

    Lista<Router>* routersVecinos = new Lista<Router>();        //Lista de todos los Routers vecinos
    Lista<Terminal>* listaTerminales = new Lista<Terminal>();   //Lista de todas las terminales conectadas al Router

    Cola<Pagina>* pagRecibidas = new Cola<Pagina>();            //Paginas que llegan desde las terminales. Las cuales se deben dividir en paquetes
    Cola<Pagina>* pagListas = new Cola<Pagina>();               //Paginas listas para mandar a la terminal correspondiente

    map<int, Router*> tablaEnrutamiento;                        //Indica a que Router enviar los paquetes segun su destino



    friend class Arista;

    //Constructor
    Router(uint8_t IP);

    //Getters
    uint8_t getIp() { return this->IP; };
    Arista* getArista(uint8_t ipDestino);
    Terminal* getTerminal(uint8_t ipTerminal);

    //Funcionalidades
    void agregarTerminal(Terminal* terminal);       //Agrega una termianl al Router
    void desarmarPaginas();                         //Desarma las paginas recibidas
    void ordenarPaquetes();                         //Ordena los nuevos paquetes recibidos
    void armarPaginas();                            //Arma la pagina si se encuentran todos los paquetes de la misma
    void enviarPaquetes();                          //Envia paquetes al siguiente Router
    void enviarPaginas();                           //Envia las paginas armadas a la terminal que corresponda
    void imprimirPaqs();               //Imprime los paquetes que se encuentran en el Router
    void calcularCiclos();                          //Calcula los ciclos de demora segun la cantidad de trafico
};

#endif //FINALAYEDD_ROUTER_H
