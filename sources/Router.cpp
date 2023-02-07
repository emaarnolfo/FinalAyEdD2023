//
// Created by emanuel on 24/01/23.
//

#include "../headers/Router.h"

Router::Router(uint8_t IP) {
    this->IP = IP;
    this->next = NULL;
    this->arista = NULL;
}

void Router::agregarTerminal(Terminal* terminal)
{
    this->listaTerminales->add(terminal);
}

void Router::desarmarPagina()
{
    while(!pagRecibidas->colavacia())
    {
        Pagina* pagina = pagRecibidas->tope();

        int numPaquetes = 1 + rand() % 10;              //Numero aleatorio de paquetes entre 1 y 30
        int pesoRestante = pagina->getPeso();           //Peso de la pagina a desarmar: el peso total de todos los paquetes juntos
        int pesoPaquete = pesoRestante / numPaquetes;   //Peso de cada paquete

        while(pesoRestante > pesoPaquete)
        {
            Paquete* nuevo = new Paquete(pagina->getId(),pagina->getPeso(), pagina->getDestino(), pesoPaquete);
            this->paquetes->add(nuevo);             //Agrega los paquetes de la pagina a la lista de paquetes del Router
            pesoRestante -= pesoPaquete;
        }

        pagRecibidas->desencolar();

        if(pesoRestante != 0)
        {
            Paquete* nuevo = new Paquete(pagina->getId(), pagina->getPeso(), pagina->getDestino(), pesoRestante);
            this->paquetes->add(nuevo);             //Ultimo paquete de menor tamaño para
        }
    }
}



void Router::borrarPaquetes(int idPag, Nodo<Paquete>* ant, Lista<Paquete>* paquetes)
{
    if(!paquetes->esvacia())
    {
        if(paquetes->cabeza()->getId() == idPag)
        {
            if(ant == nullptr)
                paquetes->borrar();
            else {
                ant->set_next(paquetes->getCzo()->get_next());
                delete paquetes->cabeza();
                borrarPaquetes(idPag, paqEnDestino->getCzo(), paquetes->resto());
            }
        }
        else borrarPaquetes(idPag, paqEnDestino->getCzo(), paquetes->resto());
    }
}

void Router::armarPaginas()
{
   Lista<Paquete>* i = paquetes;

    while(!i->esvacia())
    {
        Lista<Paquete>* j = i->resto();
        int idpag = i->cabeza()->getId();
        int pesoTotal = i->cabeza()->getPesoPaq();

        while(!j->esvacia())
        {
            if(j->cabeza()->getId() == idpag)
                pesoTotal += j->cabeza()->getPesoPaq();
            j = j->resto();
        }

        if(pesoTotal == i->cabeza()->getPeso())
        {
            Pagina* nueva = new Pagina(i->cabeza()->getId(), pesoTotal, i->cabeza()->getDestino());
            pagListas->add(nueva);
            borrarPaq(nueva->getId(), paqEnDestino);
        }
        i = i->resto();
    }
}