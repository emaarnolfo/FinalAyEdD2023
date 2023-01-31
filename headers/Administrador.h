//
// Created by emanuel on 24/01/23.
//

#ifndef FINALAYEDD_ADMINISTRADOR_H
#define FINALAYEDD_ADMINISTRADOR_H

#include "Arista.h"
#include "Router.h"
#include <map>
#include <algorithm>
#include <iostream>
#include "Color.h"


using namespace std;

class Administrador {
    Router* primero;
    int tamanio;

public:
    Administrador();
    bool esVacio();
    Router* getRouter(short int IP);        //Obtiene el Router del IP especificado
    void insertarRouter(short int IP);      //Inserta un Router en la red
    int getTamanio(){ return tamanio; };
    void insertarArista(short int IPorigen, short int IPdestino, int ancho_de_banda);   //Inserta una Arista(conexion entre Routers) con el ancho de banda especificado
    void mostrarListaAdyacencia();          //Muestra lista de adyacencia de toda la red construida
    void Dijkstra(short int IPorigen);     //Despliega las rutas mas cortas entre los vertices


};


#endif //FINALAYEDD_ADMINISTRADOR_H
//
// Created by emanuel on 24/01/23.
//

#ifndef FINALAYEDD_ADMINISTRADOR_H
#define FINALAYEDD_ADMINISTRADOR_H

#include "Arista.h"
#include "Router.h"
#include <map>
#include <algorithm>
#include <iostream>
#include "color.h"


using namespace std;

class Administrador {
    Router* primero;
    int tamanio;

public:
    Administrador();
    bool esVacio();
    Router* getRouter(short int IP);        //Obtiene el Router del IP especificado
    void insertarRouter(short int IP);      //Inserta un Router en la red
    int getTamanio(){ return tamanio; };
    void insertarArista(short int IPorigen, short int IPdestino, int ancho_de_banda);   //Inserta una Arista(conexion entre Routers) con el ancho de banda especificado
    void mostrarListaAdyacencia();          //Muestra lista de adyacencia de toda la red construida
    void Dijkstra(short int IPorigen);     //Despliega las rutas mas cortas entre los vertices


};


#endif //FINALAYEDD_ADMINISTRADOR_H
