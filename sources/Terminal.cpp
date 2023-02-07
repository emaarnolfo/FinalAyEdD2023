//
// Created by emanuel on 03/02/23.
//

#include "../headers/Terminal.h"

using namespace std;

//CONSTRUCTOR de Terminal
Terminal::Terminal(std::uint8_t  ipTerminal, std::uint8_t  ipRouter)
{
    this->ipRouter = ipRouter;
    this->ipTerminal = ipTerminal;

    this->pagRecibidas = new Cola<Pagina>();
    this->pagPendiendes = new Cola<Pagina>();

    IP* nvoTerminal = new IP{ipRouter, ipTerminal};
    tabla->add(nvoTerminal);
}

void Terminal::generarPagina()
{
    int peso = 50 + rand() %100;                         //Genera un peso entre 50 y 149
    IP* destAux;

    do{
        int indice = 1 + rand() % tabla->size();                                                //Cantidad de terminales (posibles destinos)
        destAux = tabla->get(indice);                                               //Devuelve un destino aleatorio que corresponde a alguna terminal existente
    }while(destAux->ipTerminal != ipTerminal && destAux->ipRouter != ipRouter);     //Verifica que la terminal aleatoria no se la propia terminal

    IP destino = {destAux->ipRouter, destAux->ipTerminal};

    Pagina* nuevaPag = new Pagina(peso, destino);

    delete destAux;

    pagPendiendes->encolar(nuevaPag);
}
