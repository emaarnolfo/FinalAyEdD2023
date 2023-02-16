//
// Created by emanuel on 03/02/23.
//

#include "../headers/Terminal.h"

using namespace std;

Terminal::Terminal(std::uint8_t  ipTerminal, Router* router)
{
    this->ipRouter = router->IP;
    this->ipTerminal = ipTerminal;
    this->routerPadre = router;

    IP* nvoTerminal = new IP{ipRouter, ipTerminal};
    tabla->add(nvoTerminal);
}

void Terminal::generarPagina()
{
    int peso = 1 + rand() %10;         //Genera un peso entre 1 y 10 MB
    IP* destAux;

    do{
        int indice = 1 + rand() % tabla->size();                                 //Cantidad de terminales (posibles destinos)
        destAux = tabla->get(indice);                                      //Devuelve un destino aleatorio que corresponde a alguna terminal existente
    }while(destAux->ipTerminal == ipTerminal && destAux->ipRouter == ipRouter);  //Verifica que el destino aleatorio no sea el mismo donde se genera

    IP destino = {destAux->ipRouter, destAux->ipTerminal};

    Pagina* nuevaPag = new Pagina(peso, destino);

    //delete destAux;

    pagPendiendes->encolar(nuevaPag);
}

void Terminal::enviarPaginas()
{
    while(!pagPendiendes->colavacia())
    {
        Pagina *aux = pagPendiendes->tope();
        getRouter()->pagRecibidas->encolar(aux);
        pagPendiendes->desencolar();
    }
}

void Terminal::imprimirPaginas()
{
    Lista<Pagina>* i = (Lista<Pagina>*)pagPendiendes;

    if(!pagPendiendes->esvacia()){
        printf("Paginas listas generadas para mandar al Router %d \n", ipRouter);

        while (!i->esvacia()) {
            Pagina *aux = i->cabeza();
            cout << "Pagina:" << aux->getId() << " peso:" << aux->getPeso() << " destino:";
            printf("%d.%d\n", aux->getDestino().ipTerminal, aux->getDestino().ipRouter);

            i = i->resto();
        }
    }

    if(!pagRecibidas->esvacia()){
        i = (Lista<Pagina> *) pagRecibidas;

        cout << "Paginas recibidas de otras terminales: " << endl;
        while (!i->esvacia()) {
            Pagina *aux = i->cabeza();
            cout << "Pagina: " << aux->getId() << " peso: " << aux->getPeso() << endl;
            i = i->resto();
        }
    }
}
