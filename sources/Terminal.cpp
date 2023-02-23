//
// Created by emanuel on 03/02/23.
//

#include "../headers/Terminal.h"

using namespace std;

//Constructor de la clase Terminal
Terminal::Terminal(std::uint8_t  ipTerminal, Router* router)
{
    //this->ipRouter = router->IP;
    this->ipTerminal = ipTerminal;
    this->routerPadre = router;

    IP* nvoTerminal = new IP{router->IP, ipTerminal};    //Direccion de la nueva terminal que se esta creando
    tabla->add(nvoTerminal);                        //Tabla que contiene todas las direcciones de las terminales existentes
}

uint8_t Terminal::getIpRouter()
{
    return this->routerPadre->getIp();
}

/*
 * Metodo encargado de generar nuevas paginas.
 * La pagina se crea con origen en la instancia de la terminal en la cual se llama al metodo.
 * La direccion de destino de la pagina es aleatoria. Este destino se encuentra en la tabla de terminales y
 * es distinto de la direccion de origen.
 */
void Terminal::generarPagina()
{
    int peso = TAM_MIN_PAG + rand() % (TAM_MAX_PAG - TAM_MIN_PAG);              //Genera un peso entre el maximo y el minimo para la pagina (definido en encabezado)
    IP* destAux;

    do{
        int indice = 1 + rand() % tabla->size();                                      //Cantidad de terminales (posibles destinos)
        destAux = tabla->get(indice);                                           //Devuelve un destino aleatorio que corresponde a alguna terminal existente
    }while(destAux->ipTerminal == ipTerminal && destAux->ipRouter == getIpRouter());  //Verifica que el destino aleatorio no sea el mismo donde se genera

    IP destino = {destAux->ipRouter, destAux->ipTerminal};                      //Se obtiene la direccion del destino aleatorio
    Pagina* nuevaPag = new Pagina(peso, destino);                               //Se crea la nueva pagina
    pagPendiendes->encolar(nuevaPag);                                        //Se agrega a la cola de paginas pendientes para enviar al Router que corresponda


    /*
     * Se agrega en el archivo PagGeneradas, la pagina que se creó.
     * Especificando su Terminal de destino y origen
     */
    char nombreArchivo[100];
    snprintf(nombreArchivo, 100, "%s/salida/PagGeneradas.txt", rutaActual());
    FILE* fp = fopen(nombreArchivo, "a");

    if(fp != nullptr)
    {
        fprintf(fp, "idPagina:%-4d Peso:%-4d Origen:%d.%-4d Destino:%d.%d\n",
                nuevaPag->getId(), nuevaPag->getPeso(), this->getIpRouter(), this->getIpTerminal(), nuevaPag->getDestino().ipRouter, nuevaPag->getDestino().ipTerminal);
        fclose(fp);
    }
}

/*
 * Método encargado de enviar las paginas a los Routers
 * y borrarlas de la terminal.
 */
void Terminal::enviarPaginas()
{
    while(!pagPendiendes->colavacia())              //Verifica que alla paginas en la cola
    {
        Pagina *aux = pagPendiendes->tope();
        getRouter()->pagRecibidas->encolar(aux);    //Se encola la pagina en la lista de paginasRecibidas del Router
        pagPendiendes->desencolar();
    }
}

/*
 * Si hay, imprime las paginas que se generaron en la terminal y se deben enviar al Router
 * y las paginas que llegan del Router padre que se originaron en otras terminales
 */
void Terminal::imprimirPaginas()
{
    Lista<Pagina>* i = (Lista<Pagina>*)pagPendiendes;

    if(!pagPendiendes->esvacia()){
        printf("Paginas listas generadas para mandar al Router %d \n", getIpRouter());

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
