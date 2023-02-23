//
// Created by emanuel on 24/01/23.
//

#include "../headers/Router.h"
#include <vector>

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
    int pesoRestante = pagina->getPeso() * 1000;    //Peso de la pagina a desarmar en KB: el peso total de todos los paquetes juntos

    while(pesoRestante >= TAM_MAX_PAQ)
    {
        int pesoPaquete = TAM_MIN_PAQ + rand() % (TAM_MAX_PAQ - TAM_MIN_PAQ + 1);        //Paquetes entre 50 y 200 KB
        Paquete* nuevo = new Paquete(pagina->getId(),pagina->getPeso(), pagina->getDestino(), pesoPaquete);
        this->paqNuevos->add(nuevo);             //Agrega los paquetes de la pagina a la lista de paquetes del Router
        pesoRestante -= pesoPaquete;
    }

    if(pesoRestante != 0)
    {
        Paquete* nuevo = new Paquete(pagina->getId(), pagina->getPeso(), pagina->getDestino(), pesoRestante);
        this->paqNuevos->add(nuevo);             //Ultimo paquete de menor tamaño
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
                paquetes->borrar();
                borrarPaquetes(idPag, ant, paquetes);
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
        Lista<Paquete>* i = paqEnDestino;

        while(!i->esvacia())
        {
            Lista<Paquete>* j = i->resto();
            int idpag = i->cabeza()->getId();        //Peso de la pag en KB
            int pesoTotal = i->cabeza()->getPesoPaq();

            while(!j->esvacia())
            {
                if(j->cabeza()->getId() == idpag)
                    pesoTotal += j->cabeza()->getPesoPaq();
                j = j->resto();
            }

            if(pesoTotal == i->cabeza()->getPeso() * 1000)
            {
                Pagina* nueva = new Pagina(i->cabeza()->getId(), i->cabeza()->getPeso(), i->cabeza()->getDestino());
                pagListas->add(nueva);
                borrarPaq(nueva->getId(), paqEnDestino);
                i = paqEnDestino;
                continue;
            }
            if(paqEnDestino->esvacia())
                break;

            i = i->resto();
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
    map<int, Lista<Paquete>*> mapaAux;
    //mapa auxiliar, para luego intercalar y guardar en colaEnvios

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
            //Aplicar intercalado aca
            int sigRouter = tablaEnrutamiento[r_destino]->IP;
            if(mapaAux[sigRouter] == NULL)
                mapaAux[sigRouter] = new Lista<Paquete>();
            mapaAux[sigRouter]->add(nuevo);
            i =  i->resto();
            paqNuevos->borrarDato(nuevo);
        }
    }
    //Se guardan los paquetes de manera intercalada en la cola de envios
    intercalarPaquetes(mapaAux);
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
void Router::intercalarPaquetes(map<int, Lista<Paquete>*> mapaAux)
{
    for(map<int, Lista<Paquete>*>::iterator i = mapaAux.begin(); i != mapaAux.end(); i++)
    {
        //Se crea lista para el Router vecino correspondiente
        if(colaEnvios[i->first] == NULL)
            colaEnvios[i->first] = new Lista<Paquete>();

        while(!i->second->esvacia())
        {
            //Agrego el primer paquete de la cola en la cola de paquetes listos para enviar
            Paquete* primero = i->second->cabeza();
            colaEnvios[i->first]->add(primero);
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
                    colaEnvios[i->first]->add(aux);
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
    for(map<int, Lista<Paquete>*>::iterator i = colaEnvios.begin(); i != colaEnvios.end(); i++)
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
    //this->intercalarPaquetes();

    for(map<int, Lista<Paquete>*>::iterator i = colaEnvios.begin(); i != colaEnvios.end(); i++)
    {
        Lista<Paquete>* j = i->second;
        Paquete *aux;

        Arista* ari = getArista(i->first);
        int ancho = ari->ancho_de_banda * 1000;     //Ancho en KB -> medida de los paquetes

        while (!j->esvacia() && ancho > 0)
        {
            aux = j->cabeza();
            Router *r_siguiente = getVecino(i->first);
            r_siguiente->paqNuevos->add(aux);
            j->borrar();
            ancho -= aux->getPesoPaq();
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
    char nombreArchivo[100];
    snprintf(nombreArchivo, 100, "%s/salida/PagEnDestino.txt", rutaActual());
    FILE *fp = fopen(nombreArchivo, "a");

    while(!pagListas->colavacia()) {
        Pagina *aux = pagListas->tope();
        uint8_t destino = aux->getDestino().ipTerminal;

        getTerminal(destino)->addPagina(aux);

        pagListas->desencolar();

        if(fp != nullptr)
            fprintf(fp, "idPagina:%-4d Peso:%-4d Destino:%d.%d\n",
                    aux->getId(), aux->getPeso(), aux->getDestino().ipRouter, aux->getDestino().ipTerminal);
    }
    fclose(fp);
}

void Router::imprimirPaqs(int numCiclos)
{
    char nombreArchivo[100];
    snprintf(nombreArchivo, 100, "%s/salida/paquetes%d.txt", rutaActual(), numCiclos);
    FILE* fp = fopen(nombreArchivo, "a");
    fprintf(fp, "\nROUTER %d:\n", this->IP);

    map<int, int> enDestino;
    Lista<Paquete>* cola = paqEnDestino;

    while(!cola->esvacia())
    {
        if (enDestino.count(cola->cabeza()->getId()))        //Si ya se encuentra un paqute con el mismo idPag se incrementa la cantidad del mismo
            enDestino[cola->cabeza()->getId()] += 1;
        else
            enDestino[cola->cabeza()->getId()] = 1;              //Sino si crea el nuevo mapa y comienza en 1

        cola = cola->resto();
    }

    if(!enDestino.empty())
        fprintf(fp, "\tPaquetes en destino:\n");

    while(!enDestino.empty())
    {
        fprintf(fp, "\t\t- %d paquetes de la pag %d\n", enDestino.begin()->second, enDestino.begin()->first);
        enDestino.erase(enDestino.begin());
    }

    for(map<int, Lista<Paquete>*>::iterator i = colaEnvios.begin(); i != colaEnvios.end(); i++) {

        map<int, int> enColaEnvios;
        Lista<Paquete> *cola = i->second;

        while(!cola->esvacia())
        {
            if (enColaEnvios.count(cola->cabeza()->getId()))
                enColaEnvios[cola->cabeza()->getId()] += 1;
            else
                enColaEnvios[cola->cabeza()->getId()] = 1;

            cola = cola->resto();
        }

        if(!enColaEnvios.empty() && i == colaEnvios.begin())
            fprintf(fp, "\tPaquetes en cola de envios:\n");

        if(fp != nullptr){
            while (!enColaEnvios.empty()) {
                fprintf(fp, "\t\t- %d paquetes de la pag %d (siguiente Router: %d)\n"
                        , enColaEnvios.begin()->second, enColaEnvios.begin()->first, i->first);
                enColaEnvios.erase(enColaEnvios.begin());
            }
        }
    }

    if(fp != nullptr)
        fclose(fp);
}

void Router::imprimirNuevos()
{
    cout << "Paquetes recien llegados al Router" << endl;

    map<int, int> cantPaquetes;

    Lista<Paquete>* cola = paqNuevos;

    while(!cola->esvacia())
    {
        if (cantPaquetes.count(cola->cabeza()->getId()))
            cantPaquetes[cola->cabeza()->getId()] += 1;
        else
            cantPaquetes[cola->cabeza()->getId()] = 1;

        cola = cola->resto();
    }

    cola = paqNuevos;

    for(map<int, int>::iterator j = cantPaquetes.begin(); j != cantPaquetes.end(); j++)
    {
        printf("- %d paquetes de la pag %d\n", j->second, j->first);
    }

}

/*
 * Calcula el peso total, para cada Router vecino, de todos los paquetes que se deben enviar
 */
int Router::getPesoLista(Lista<Paquete>* lista)
{
    int pesoTotal = 0;

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
    for(map<int, Lista<Paquete>*>::iterator i = colaEnvios.begin(); i != colaEnvios.end(); i++)
    {
        int r_destino = i->first;
        int pesoPaquetes = getPesoLista(i->second);
        Arista* aux = this->getArista(r_destino);

        double ciclos = (double)(pesoPaquetes/1000) / aux->ancho_de_banda;

        if(ciclos > 1)
            aux->ciclos = ciclos;
    }
}
