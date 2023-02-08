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


using namespace std;

class Administrador {
private:
    char* rutaActual();
    int routers;
    int matriz[10][10];

public:
    Router* routerCzo;
    Lista<Terminal>* terminales = new Lista<Terminal>();
    int nroRouters;
    int nroTerminales;

    Administrador();
    bool esVacio();
    void addRouter(uint8_t ipRouter);      //Inserta un Router en la red
    Router* getRouter(uint8_t ipRouter);        //Obtiene el Router del IP especificado
    void addTerminal(uint8_t ipRouter, uint8_t ipTerminal);
    void generarPaginas(int nroPaginas);
    int getTamanio(){ return nroRouters; };
    void insertarArista(short int IPorigen, short int IPdestino, int ancho_de_banda);   //Inserta una Arista(conexion entre Routers) con el ancho de banda especificado
    void mostrarListaAdyacencia();          //Muestra lista de adyacencia de toda la red construida
    void Dijkstra(short int IPorigen, short int IPdestino);     //Despliega las rutas mas cortas entre los vertices
    void leerArchivo();


};

#endif //FINALAYEDD_ADMINISTRADOR_H
