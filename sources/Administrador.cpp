//
// Created by emanuel on 24/01/23.
//

#include "../headers/Administrador.h"

Administrador::Administrador() {
    this->routerCzo = NULL;
    this->nroRouters = 0;
    this->nroTerminales = 0;
    this->contCiclos = 0;
}

bool Administrador::esVacio() {
    if(routerCzo == NULL)
        return true;
    return false;
}

Router* Administrador::getRouter(uint8_t IP) {
    Router* aux = routerCzo;

    while(aux != NULL)
    {
        if(aux->IP == IP)
            return aux;

        aux = aux->next;
    }
    return NULL;
}

void Administrador::addRouter()
{
    if(nroRouters != numeric_limits<uint8_t>::max())
    {
        Router *nuevo = new Router(++nroRouters);

        if (esVacio()) {
            routerCzo = nuevo;
        } else {
            Router *aux = routerCzo;

            while (aux->next != NULL)
                aux = aux->next;

            aux->next = nuevo;
        }
    }
}


void Administrador::addTerminal(uint8_t ipRouter, uint8_t ipTerminal)
{
    Router* router = this->getRouter(ipRouter);

    if(router != NULL) {
        Terminal* nuevo = new Terminal(ipTerminal, router);
        this->terminales->add(nuevo);
        router->agregarTerminal(nuevo);
        nroTerminales++;
    } else {
        cout << "No se puede agregar la terminal, no se ha encontrado el Router especificado" << endl;
    }
}


/*
 * Genera la cantidad de paginas que se le pasan por parametro.
 * Las paginas se generan en terminales aleatorias que se
 * obtienen de la lista de terminales
 */

void Administrador::generarPaginas(int nroPaginas)
{
    for(int i = 0; i < nroPaginas; i++) {
        int index = 1 + rand() % terminales->size();
        Terminal *terminal = terminales->get(index);
        terminal->generarPagina();
    }

    char nombreArchivo[100];
    snprintf(nombreArchivo, 100, "%s/salida/PagGeneradas.txt", rutaActual());
    FILE* fp = fopen(nombreArchivo, "a");

    if(fp != nullptr)
    {
        fprintf(fp, "\n");
        fclose(fp);
    }
}


void Administrador::addArista(uint8_t IPorigen, uint8_t IPdestino, int ancho_de_banda)
{
    Router* router_origen = getRouter(IPorigen);
    Router* router_destino = getRouter(IPdestino);

    if(router_destino != NULL && router_origen != NULL)
    {
        Arista* nuevo = new Arista(ancho_de_banda, router_destino);
        router_origen->routersVecinos->add(router_destino);

        if(router_origen->arista == NULL)
            router_origen->arista = nuevo;
        else
        {
            Arista* aux = router_origen->arista;

            while(aux->next != NULL)
                aux = aux->next;

            aux->next = nuevo;
        }
    } else {
        cout<<"No se encontraron los Routers especificados" <<endl;
    }
}

void Administrador::mostrarListaAdyacencia()
{
    cout << "Lista de Adyacencia: " << RED <<"Routers " << GREEN << "Ancho de banda" <<endl;
    Router* i = routerCzo;

    while(i != NULL)
    {
        Arista* j = i->arista;
        //printf(RED "%d = ", i->IP);

        while(j != NULL)
        {
            //cout << "\x1b[31m" << i->IP <<"\x1b[32m" <<"->" <<j->ancho_de_banda << "\x1b[31m" << "->" <<j->destino->IP;
            printf(RED "%d" GREEN "->%d" RED "->%d", i->IP, j->ancho_de_banda, j->destino->IP);
            if(j->next != NULL)
                cout << " - ";
            j = j->next;
        }
        cout << endl;
        i = i->next;
    }
    cout << RESET;
}

bool costoMinimo(const pair<Router*, int>& a, const pair<Router*, int>& b)
{
    return a.second < b.second;
}
/*
 * Algoritmo de dijkstra para calcular el camino mas corto
 * desde el router origen que se pasa por parametro
 * Opcion 1: el algoritmo resuleve el camino segun los anchos de banda de las aristas
 * Opcion 2: el algoritmo resuleve el camino segun los ciclos de las aristas
 */
void Administrador::Dijkstra(short IPorigen, int opcion)
{
    Router* r_origen = getRouter(IPorigen);

    if(r_origen == NULL)
        cout << "El vertice origen no existe" <<endl;
    else
    {
        map<Router*, map<Router*, double>> matriz;
        map<Router*, bool> visitados;           //Par ordenado con los Routers de la red y su booleano que indica si fue visitado
        map<Router*, Router*> rutas;            //Ruta que va desde el origen ingresado hacia cada Router de la red
        map<Router*, int> cola;                 //Cola de prioridad
        map<Router*, int> distancias;           //Distancia desde el router origen ingresado hacia cada Router


        //cola2 = new Cola<Router*>();
        Router* ri = routerCzo;

        while(ri != NULL)
        {
            visitados[ri] = false;
            rutas[ri] = NULL;
            distancias[ri] = numeric_limits<int>::max();

            Router* rj = routerCzo;

            while(rj != NULL)
            {
                matriz[ri][rj] = numeric_limits<int>::max();
                rj = rj->next;
            }

            Arista* aj = ri ->arista;

            //Se carga la matriz con los pesos de los ancho de banda
            while(aj != NULL)
            {
                if(opcion == 1)
                    matriz[ri][aj->destino] = aj->peso;
                else if(opcion == 2)
                    matriz[ri][aj->destino] = aj->ciclos;
                else{
                    cout << "Opcion incorrecta en Dijkstra" << endl;
                    exit(1);
                }

                aj = aj->next;
            }
            ri = ri->next;
        }

        distancias[r_origen] = 0;
        visitados[r_origen] = true;
        //cola2->encolar(r_origen);
        cola[r_origen] = distancias[r_origen];


        //Recorremos los nodos para sacar los recorridos
        while(!cola.empty())
        {
            map<Router*, int>::iterator iter = min_element(cola.begin(), cola.end(), costoMinimo);


            //Router* r_iter = cola2->tope();

            Arista* ai = iter->first->arista;

            while(ai != NULL)
            {
                if(!visitados[ai->destino])
                {
                    if(distancias[ai->destino] > distancias[iter->first] + matriz[iter->first][ai->destino])
                    {
                        distancias[ai->destino] = distancias[iter->first] + matriz[iter->first][ai->destino];
                        rutas[ai->destino] = iter->first;
                        cola[ai->destino] = distancias[ai->destino];
                        //cola2->encolar(ai->destino);
                    }
                }
                ai = ai->next;
            }

            visitados[iter->first] = true;
            //cola2->desencolar();
            cola.erase(iter->first);
        }

        //Muestra los vertices destino con su respectivo peso total
        for(map<Router*, int>::iterator i = distancias.begin(); i != distancias.end(); i++)
            //printf("%d: %d\n",i->first->IP, i->second);

        //Muestra las rutas completas
        for(map<Router*, Router*>::iterator i = rutas.begin(); i != rutas.end(); i++)
        {
            Router* rActual = i->first;

            while(rActual != NULL)
            {
                if(rutas[rActual] == r_origen){
                    //cout<<"(primero) ";
                    r_origen->tablaEnrutamiento[i->first->IP] = rActual;
                }

                //printf("%d <- ", rActual->IP);
                rActual = rutas[rActual];
            }
            //cout << endl;
        }
    }
}

void Administrador::leerArchivo()
{
    cout << "Leyendo archivo con informacion de la red" <<endl;

    char nombre[100];
    snprintf(nombre, 100, "%s/config2.txt", rutaActual());

    FILE* fp;
    fp = fopen(nombre, "r");

    if (fp == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    // Leer la cantidad de routers
    fscanf(fp, "Routers: %d\n", &routers);
    printf("Cantidad de routers: %d\n", routers);
    for (int i = 0; i < routers; ++i) {
        addRouter();
        cout << "Se agrega router " << i+1 << endl;
    }


    // Saltar la línea "MatrizDeAdyacencia:"
    char buffer[100];
    fgets(buffer, 100, fp);

    //int matriz[routers+1][routers+1];
    // Leer las siguientes líneas
    for (int i = 0; i <= routers; i++) {
        for (int j = 0; j <= routers; j++) {
            fscanf(fp, "%d", &matriz[i][j]);
        }
        fgets(buffer, 100, fp);
    }

    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL) {
        int ipRouter = atoi(&line[0]);
        int numTerminals = atoi(&line[2]);
        for (int i = 1; i <= numTerminals; i++) {
            printf("Se crea terminal %d en Router %d\n", i, ipRouter);
            addTerminal(ipRouter, i);
        }
    }

    // Insertar las aristas
    printf("Aristas y anchos de banda:\n");
    for (int i = 1; i <= routers; i++) {
        for (int j = 1; j <= routers; j++) {
            if(matriz[i][j] != 0) {
                this->addArista(i, j, matriz[i][j]);
                printf("%d -> %d -> %d  -  ", i, matriz[i][j], j);
            }
        }
        printf("\n");
    }

    fclose(fp);
}

void Administrador::enviarPaginas()
{
    Lista<Terminal>* i = terminales;

    while (!i->esvacia())
    {
        i->cabeza()->enviarPaginas();
        i = i->resto();
    }
}

void Administrador::recalcular()
{
    for(int i=0; i<nroRouters; i++)
        getRouter(i+1)->calcularCiclos();

    for(int i=0; i<nroRouters; i++)
        Dijkstra(i+1, 2);
}

void Administrador::ciclo()
{
    cout << BLACK << BG_YELLOW << " CICLO " << ++contCiclos <<" " << RESET << endl;

    //Desarma las paginas que se encuentran en los Routers
    for(int i=0; i<nroRouters; i++)
        getRouter(i+1)->desarmarPaginas();

    for(int i=0; i<nroRouters; i++)
        getRouter(i+1)->ordenarPaquetes();

    for(int i=0; i<nroRouters; i++)
        getRouter(i+1)->enviarPaquetes();

    for(int i=0; i<nroRouters; i++)
        getRouter(i+1)->ordenarPaquetes();

    for(int i=0; i<nroRouters; i++)
        getRouter(i+1)->armarPaginas();

    for(int i=0; i<nroRouters; i++)
        getRouter(i+1)->enviarPaginas();

    imprimirTermianles();
    imprimirPaquetes();
}

void Administrador::imprimirTermianles()
{
    cout << endl << "Impresion de " << RED << " Paginas" << RESET << endl;
    Lista<Terminal>* i = terminales;

    while(!i->esvacia())
    {
        Terminal* aux = i->cabeza();
        cout <<endl << REVERSED;
        printf("Terminal %d.%d", aux->getIpRouter(), aux->getIpTerminal());
        cout << RESET << endl;

        aux->imprimirPaginas();
        i = i->resto();
    }

    cout << endl << " ------------------------------------------------------------------ " << endl;
}

void Administrador::imprimirPaquetes()
{
    //cout << endl << endl << "Impresion de " << RED << " Paquetes" << RESET << endl;
    Router* aux = routerCzo;

    while(aux != nullptr){
        //cout << endl << REVERSED;
        //printf("Router %d:", aux->IP);
        //cout << RESET <<endl;
        aux->imprimirPaqs(this->contCiclos);
        aux = aux->next;
    }

    //cout << endl << " ------------------------------------------------------------------ " << endl;
}
