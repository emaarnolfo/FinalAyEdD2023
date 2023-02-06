//
// Created by emanuel on 24/01/23.
//

#include "../headers/Router.h"

Router::Router(uint8_t IP) {
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

    delete pagina;

    Paquete* nuevo = new Paquete(pagina->getId(), pagina->getPeso(), pagina->getDestino(), pesoRestante);
    this->paquetes->add(nuevo);
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