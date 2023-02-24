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
#include "Ruta.h"

#define MAX_ROUTERS 255

using namespace std;

class Administrador : public Ruta {
private:
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
    void addRouter();                                                           //Inserta un Router en la red
    Router* getRouter(uint8_t ipRouter);                                        //Obtiene el Router del IP especificado
    void addTerminal(uint8_t ipRouter, uint8_t ipTerminal);                     //Agrega una terminal al Router especificado
    void generarPaginas(int nroPaginas);                                        //Genera n paginas aleatorias con origen y destino aleatorios
    void addArista(uint8_t IPorigen, uint8_t IPdestino, int ancho_de_banda);    //Inserta una Arista(conexion entre Routers) con el ancho de banda especificado
    void mostrarListaAdyacencia();                                              //Muestra lista de adyacencia de toda la red construida
    void Dijkstra(short int IPorigen, int opcion);                              //Calcula las rutas mas cortas entre los vertices
    void leerArchivo(int opcion);                                               //Lee el archivo de configuracion y arma la red del mismo
    void ciclo();                                                               //Realiza un ciclo completo de la red.
    void enviarPaginas();                                                       //Envia las paginas que se encuentran en las terminales hacia sus Routers correspondientes
    void imprimirTermianles();                                                  //Imprime las paginas que contiene cada termianl
    void imprimirPaquetes();                                                    //Imprime los paquetes que contiene cada Router
    void recalcular();                                                          //Recalcula los caminos en base a las colas de trafico de cada Router
    void limpiarArchivos();                                                     //Limpia los archivos que se van a utilizar para guardar la informacion

};

#endif //FINALAYEDD_ADMINISTRADOR_H
