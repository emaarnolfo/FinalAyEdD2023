//
// Created by emanuel on 24/01/23.
//

#include "../headers/Router.h"

Router::Router(short int IP) {
    this->IP = IP;
    this->next = NULL;
    this->arista = NULL;

    //Paquetes
    //Paginas

    //std::cout << "Constructor Router" << std::endl;
}

void Router::desarmarPagina(Pagina *pagina)
{

    int numPaquetes = 1 + rand() % 30;              //Numero aleatorio de paquetes entre 1 y 30
    int pesoRestante = pagina->getPeso();           //Peso de la pagina a desarmar: el peso total de todos los paquetes juntos
    int pesoPaquete = pesoRestante / numPaquetes;   //Peso de cada paquete

    while(pesoRestante > pesoPaquete)
    {
        Paquete* nuevo = new Paquete(pagina->getId(),pagina->getPeso(), pagina->getDestino(), pesoPaquete);
        this->paquetes->add(nuevo);
        pesoRestante -= pesoPaquete;
    }

    Paquete* nuevo = new Paquete(pagina->getId(), pagina->getPeso(), pagina->getDestino(), pesoRestante);
    this->paquetes->add(nuevo);
}

void Router::armarPagina()
{
    int id = this->paquetes->cabeza()->getId();
    int peso = 0;

    //Recorrer con resto
    while(true){

    }
}