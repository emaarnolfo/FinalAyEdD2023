//
// Created by emanuel on 24/01/23.
//

#ifndef FINALAYEDD_ADMINISTRADOR_H
#define FINALAYEDD_ADMINISTRADOR_H

#include "Arista.h"
#include "Router.h"
#include <map>
#include <algorithm>
#include "Color.h"
#include "Terminal.h"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <cstring>

#define MAX_ROUTERS 255

using namespace std;

class Administrador {
private:
    char* rutaActual();
    int routers = 255;
    int matriz[MAX_ROUTERS][MAX_ROUTERS];
    int contCiclos;


public:
    Router* routerCzo;
    Lista<Terminal>* terminales = new Lista<Terminal>();
    uint8_t nroRouters;
    int nroTerminales;

    Administrador();
    bool esVacio();
    void addRouter();      //Inserta un Router en la red
    Router* getRouter(uint8_t ipRouter);        //Obtiene el Router del IP especificado
    void addTerminal(uint8_t ipRouter, uint8_t ipTerminal);
    void generarPaginas(int nroPaginas);
    int getTamanio(){ return nroRouters; };
    void addArista(uint8_t IPorigen, uint8_t IPdestino, int ancho_de_banda);   //Inserta una Arista(conexion entre Routers) con el ancho de banda especificado
    void mostrarListaAdyacencia();          //Muestra lista de adyacencia de toda la red construida
    void Dijkstra(short int IPorigen);     //Despliega las rutas mas cortas entre los vertices
    void leerArchivo();
    void ciclo();
    void enviarPaginas();
    void imprimirTermianles();
    void imprimirPaquetes();

};

#endif //FINALAYEDD_ADMINISTRADOR_H
