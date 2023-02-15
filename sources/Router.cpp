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

    while(pesoRestante >= 20)
    {
        int pesoPaquete = 1 + rand() % 20;
        Paquete* nuevo = new Paquete(pagina->getId(),pagina->getPeso(), pagina->getDestino(), pesoPaquete);
        this->paqNuevos->add(nuevo);             //Agrega los paquetes de la pagina a la lista de paquetes del Router
        pesoRestante -= pesoPaquete;
    }

    if(pesoRestante != 0)
    {
        Paquete* nuevo = new Paquete(pagina->getId(), pagina->getPeso(), pagina->getDestino(), pesoRestante);
        this->paqNuevos->add(nuevo);             //Ultimo paquete de menor tamaño para
    }
}

/*
 * Desarma las paginas recibidas de las terminales y llama la funcion encargada de armar paquetes
 */
void Router::desarmarPaginas()
{
    while(!pagRecibidas->colavacia())
    {
        Pagina* pagina = pagRecibidas->tope();
        crearPaquetes(pagina);
        pagRecibidas->desencolar();
    }
}

/*
 * Funcion recursiva que borra paquetes de la lista que se pasa por parametro.
 * Se buscan los paquetes que corresponden al id de Pagina que se especifica por parametro y
 * dichos paquetes se borran de la lista
 */
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

/*
 * Verifica que se encuentren todos los paquetes de una misma pagina en la lista de 'paqEnDestino'
 * y arma la página con los datos correspondientes de la misma
 */
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
                i = paqEnDestino;
            }
            if(paqEnDestino->esvacia())
                break;

            i = i->resto();
        }
    }
}

/*
 * Verifica el destino de cada paquete que llega al Router en la lista paqNuevos.
 * Si el el destino del paquete es el del mismo Router, este se pasa a la lista de paqEnDestino
 * para armar la pagina (sólo si se encuentra la totalidad de paquetes de la pagina).
 * En cambio si el destino es otro Router, el paquete pasa a la cola de Envios de su respectivo destino.
 * La lista 'paqNuevos' queda vacia para recibir los nuevos paquetes en el proximo turno
 */
void Router::ordenarPaquetes()
{
    Lista<Paquete>* i = paqNuevos;

    while(!i->esvacia())
    {
        int r_destino = i->cabeza()->getDestino().ipRouter;
        Paquete* nuevo = i->cabeza();

        //El paquete se encuentra en su router destino
        if(r_destino == this->IP)
        {
            paqEnDestino->add(nuevo);
            i = i->resto();
            paqNuevos->borrarDato(nuevo);
        }

        //El paquete no llego al Router destino, pasa a la cola de envios de su siguiente Router
        else
        {
            int sigRouter = tablaEnrutamiento[r_destino]->IP;
            if(colaEnvios[sigRouter] == NULL)
                colaEnvios[sigRouter] = new Lista<Paquete>();
            colaEnvios[sigRouter]->add(nuevo);
            i =  i->resto();
            paqNuevos->borrarDato(nuevo);
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

Arista *Router::getArista(uint8_t ipDestino)
{
    Arista* aux = this->arista;

    while(aux != nullptr)
    {
        if(aux->destino->IP == ipDestino)
            return aux;

        aux = aux->next;
    }

    cout << "No se encontro la Arista pedida " << endl;

    return nullptr;
}

/*
 * Intercala los paquetes para no enviar todos los paquetes de una misma pagina juntos.
 * Los paquetes que se encuentran en la cola de envios se pasan de manera intercalada
 * a la cola de paquetes listos de cada Router vecino.
 */
void Router::intercalarPaquetes()
{
    for(map<int, Lista<Paquete>*>::iterator i = colaEnvios.begin(); i != colaEnvios.end(); i++)
    {
        //Se crea lista para el Router vecino correspondiente
        if(paqListos[i->first] == NULL)
            paqListos[i->first] = new Lista<Paquete>();

        while(!i->second->esvacia())
        {
            //Agrego el primer paquete de la cola en la cola de paquetes listos para enviar
            Paquete* primero = i->second->cabeza();
            paqListos[i->first]->add(primero);
            i->second->borrar();

            if(i->second->esvacia())   //Se borro el ultimo paquete en la linea anterior
                continue;

            Lista<Paquete>* j = i->second;
            int idPag = j->cabeza()->getId();

            while(!j->esvacia())
            {
                if(idPag != j->cabeza()->getId())
                {
                    idPag = j->cabeza()->getId();
                    Paquete* aux = j->cabeza();
                    paqListos[i->first]->add(aux);
                    j = j->resto();
                    i->second->borrarDato(aux);
                }
                else
                    j = j->resto();
            }

        }
    }
}

void Router::imprimirIntercalado()
{
    for(map<int, Lista<Paquete>*>::iterator i = paqListos.begin(); i != paqListos.end(); i++)
    {
        Lista<Paquete>* j = i->second;

        while(!j->esvacia())
        {
            cout <<"ID paquete: " << j->cabeza()->getId() << endl;
            j = j->resto();
        }
    }

}

/*
 * Cada paquete pregunta en 'sigRouter' cual es el proximo Router al que tiene que ir
 * para llegar al destino del paquete.
 * Una vez encontrado el paquete lo agrega a la cola de paquetes
 * del Router que corresponde segun el destino del dato.
 */
void Router::enviarPaquetes()
{
    this->intercalarPaquetes();

    //this->imprimirIntercalado();

    for(map<int, Lista<Paquete>*>::iterator i = paqListos.begin(); i != paqListos.end(); i++)
    {
        Lista<Paquete>* j = i->second;
        Paquete *aux = j->cabeza();


        Arista* ari = getArista(i->first);
        int ancho = ari->ancho_de_banda * 1000;     //Ancho en KB -> medida de los paquetes

        while (!j->esvacia())
        {
            uint8_t r_destino = aux->getDestino().ipRouter;
            aux = j->cabeza();
            Router *r_siguiente = tablaEnrutamiento[r_destino];
            r_siguiente->paqNuevos->add(aux);
            j->borrar();
        //    ancho -= aux->getPesoPaq();
        }
    }
}

/*
 * Devuelve la terminal pedida por parametro la cual se encuentra conectada al Router
 * Imprime un mensaje si no encuentra la terminal especificada
 */
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

void Router::imprimirPaqs()
{
    int cant, idPag;

    for(map<int, Lista<Paquete>*>::iterator i = colaEnvios.begin(); i != colaEnvios.end(); i++){
        cant = 0;
        Lista<Paquete>* cola = i->second;
        if(!cola->esvacia())
            idPag = cola->cabeza()->getId();

        while(!cola->esvacia())
        {
            if(idPag != cola->cabeza()->getId())
            {
                printf("- %d paquetes de la pag %d con destino en Router %d\n", cant, idPag, i->first);
                idPag = cola->cabeza()->getId();
                cant = 1;
            }
            else
                cant++;

            cola = cola->resto();
        }
        if(cant != 0)
            printf("- %d paquetes de la pag %d con destino en Router %d\n", cant, idPag, i->first);
    }
}

/*
 * Calcula el peso total, para cada Router vecino, de todos los paquetes que se deben enviar
 */
int Router::getAnchoBandaLista(Lista<Paquete>* lista)
{
    int pesoTotal;

    while(!lista->esvacia())
    {
        pesoTotal += lista->cabeza()->getPesoPaq();
        lista = lista->resto();
    }

    return pesoTotal;
}

/*
 * Calcula la cantidad de ciclos que hay de demora hacia
 * cada Router que vaya a recibir paquetes nuevos
 */
void Router::calcularCiclos()
{
    Arista* aux = arista;

    for(map<int, Lista<Paquete>*>::iterator i = paqListos.begin(); i != paqListos.end(); i++)
    {
        int r_destino = i->first;
        int pesoPaquetes = getAnchoBandaLista(i->second);
        Arista* aux = this->getArista(r_destino);

        double ciclos = pesoPaquetes / aux->ancho_de_banda;

        if(ciclos > 1)
            aux->ciclos = ciclos;
    }
}
