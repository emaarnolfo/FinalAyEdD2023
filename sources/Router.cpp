//
// Created by emanuel on 24/01/23.
//

#include "../headers/Router.h"

using namespace std;

Router::Router(uint8_t IP) {
    this->IP = IP;
    this->next = NULL;
    this->arista = NULL;
}

void Router::agregarTerminal(Terminal* terminal)
{
    this->listaTerminales->add(terminal);
}

/*
 * Crea paquetes a partir de una pagina. El peso de la pagina
 * se divide en paquetes de peso aleatorio entre 1 y 10.
 * Los paquetes generados se agregan a la lista de paquetes
 */

void Router::crearPaquetes(Pagina *pagina)
{
    int pesoRestante = pagina->getPeso();           //Peso de la pagina a desarmar: el peso total de todos los paquetes juntos

    while(pesoRestante >= 10)
    {
        int pesoPaquete = 1 + rand() % 10;
        Paquete* nuevo = new Paquete(pagina->getId(),pagina->getPeso(), pagina->getDestino(), pesoPaquete);
        this->paquetes->add(nuevo);             //Agrega los paquetes de la pagina a la lista de paquetes del Router
        pesoRestante -= pesoPaquete;
    }

    if(pesoRestante != 0)
    {
        Paquete* nuevo = new Paquete(pagina->getId(), pagina->getPeso(), pagina->getDestino(), pesoRestante);
        this->paquetes->add(nuevo);             //Ultimo paquete de menor tamaño para
    }
}

void Router::desarmarPaginas()
{
    while(!pagRecibidas->colavacia())
    {
        Pagina* pagina = pagRecibidas->tope();
        crearPaquetes(pagina);
        pagRecibidas->desencolar();
    }
}

void Router::borrarPaquetes(int idPag, Nodo<Paquete>* ant, Lista<Paquete>* paquetes)
{
    if(!paquetes->esvacia())
    {
        if(paquetes->cabeza()->getId() == idPag)
        {
            if(ant == nullptr) {
                paquetes->borrar();
                borrarPaquetes(idPag, nullptr, paquetes);
            }
            else {
                ant->set_next(paquetes->getCzo()->get_next());
                delete paquetes->cabeza();
                borrarPaquetes(idPag, paquetes->getCzo(), paquetes->resto());
            }
        }
        if(!paquetes->esvacia())
            borrarPaquetes(idPag, paquetes->getCzo(), paquetes->resto());
    }
}

void Router::armarPaginas()
{
    if(!paqEnDestino->esvacia()){           //Verifico que haya paquetes en el destino
        Lista<Paquete>* i = paqEnDestino;

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
            if(paqEnDestino->esvacia())
                break;

            i = i->resto();
        }
    }
}

/*
 * Verifica si los paquetes que llegan al Router y se encuentran en la lista 'paquetes'
 * se encuentran en el router destino. Si es asi se quitan de la lista 'paquetes'
 * y se pasan a la lista de 'paqEnDestino' la cual se utiliza luego para armar la
 * pagina una vez que se encuentran todos los paquetes de la misma
 */
void Router::ordenarPaquetes()
{
    Lista<Paquete>* i = paquetes;

    while(!i->esvacia())
    {
        if(paquetes->cabeza()->getDestino().ipRouter == this->IP){
            Paquete* nuevo = paquetes->cabeza();
            paqEnDestino->add(nuevo);
            paquetes->borrar();
        } else {
            i = i->resto();
        }
    }
}

Router* Router::getRoutVec(uint8_t ipRouter, Lista<Router>* r_vecinos)
{
    if(!r_vecinos->esvacia()){
        if (r_vecinos->cabeza()->IP == ipRouter)
            return r_vecinos->cabeza();
        else
            return getRoutVec(ipRouter, r_vecinos->resto());
    }

    cout << "No se encontro el Router Vecino especificado " << endl;
    return nullptr;
}

/*
 * Cada paquete pregunta en sigRouter cual es el proximo Router al que tiene que ir
 * para llegar al destino del paquete.
 * Una vez encontrado el paquete lo agrega a la cola de paquetes
 * del Router que corresponde segun el destino del dato
 */
void Router::enviarPaquetes()
{
    Lista<Paquete>* i = paquetes;

    while(!i->esvacia())
    {
        Paquete* aux = i->cabeza();
        uint8_t r_destino = aux->getDestino().ipRouter;
        Router* r_siguiente = sigRouter[r_destino];

        r_siguiente->paquetes->add(aux);

        i->borrar();

        //i = i->resto();
    }
}

Terminal* Router::getTerminal(uint8_t ipTerminal)
{
    Lista<Terminal>* i = listaTerminales;

    while(!i->esvacia())
    {
        if(i->cabeza()->getIpTerminal() == ipTerminal)
            return i->cabeza();

        i = i->resto();
    }

    cout << "No se entontro la pagina pedida " << endl;
    return nullptr;
}

/*
 *
 */
void Router::enviarPaginas()
{
    while(!pagListas->colavacia())
    {
        Pagina* aux = pagListas->tope();
        uint8_t destino = aux->getDestino().ipTerminal;

        getTerminal(destino)->addPagina(aux);

        pagListas->desencolar();
    }
}