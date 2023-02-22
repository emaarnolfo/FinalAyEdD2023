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

char* Terminal::rutaActual()
{
    // Obtiene la ruta actual
    char* buf = get_current_dir_name();

    // Convierte la ruta actual a una cadena de C++
    string pathAlt(buf);

    // Encuentra la última aparición de la barra diagonal
    size_t pos = pathAlt.find_last_of("/");

    if (pos != string::npos)        // Si se encontró la barra diagonal
        pathAlt.erase(pos);         // Elimina todo despues de la ultima barra diagonal

    string path2 = pathAlt;
    char* path = strcpy(new char[path2.length() + 1], path2.c_str());

    return path;
}

void Terminal::generarPagina()
{
    int peso = 1 + rand() %5;         //Genera un peso entre 1 y 25 MB
    IP* destAux;

    do{
        int indice = 1 + rand() % tabla->size();                                 //Cantidad de terminales (posibles destinos)
        destAux = tabla->get(indice);                                      //Devuelve un destino aleatorio que corresponde a alguna terminal existente
    }while(destAux->ipTerminal == ipTerminal && destAux->ipRouter == ipRouter);  //Verifica que el destino aleatorio no sea el mismo donde se genera

    IP destino = {destAux->ipRouter, destAux->ipTerminal};

    Pagina* nuevaPag = new Pagina(peso, destino);

    pagPendiendes->encolar(nuevaPag);


    char nombreArchivo[100];
    snprintf(nombreArchivo, 100, "%s/paginas.txt", rutaActual());
    FILE* fp = fopen(nombreArchivo, "a");

    if(fp != nullptr)
    {
        fprintf(fp, "idPagina:%-4d Peso:%-4d Origen:%d.%-4d Destino:%d.%d\n", nuevaPag->getId(), nuevaPag->getPeso(), this->ipRouter, this->ipTerminal, nuevaPag->getDestino().ipRouter, nuevaPag->getDestino().ipTerminal);
        fclose(fp);
    }


/*
    agregarPag(char* cadena) {
        FILE* archivo = fopen("informacion.txt", "a"); // "a" significa "append" o "añadir"
        if (archivo != NULL) {
            fprintf(archivo, "%s", cadena);
            fclose(archivo);
        }
    }
    */
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
