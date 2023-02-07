//
// Created by emanuel on 24/01/23.
//

#include "../headers/Administrador.h"

Administrador::Administrador() {
    this->routerCzo = NULL;
    this->nroRouters = 0;
    this->nroTerminales = 0;
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

void Administrador::addRouter(uint8_t IP)
{
    Router* nuevo = new Router(IP);


    if(esVacio())
    {
        routerCzo = nuevo;
    }
    else
    {
        Router* aux = routerCzo;

        while(aux->next != NULL)
            aux = aux->next;

        aux->next = nuevo;
        nroRouters++;
    }
}


void Administrador::addTerminal(uint8_t ipRouter, uint8_t ipTerminal)
{
    Router* router = this->getRouter(ipRouter);

    if(router != NULL) {
        Terminal* nuevo = new Terminal(ipTerminal, ipRouter);
        this->terminales->add(nuevo);
        router->agregarTerminal(nuevo);
        nroTerminales++;
    } else {
        cout << "No se puede agregar la terminal, no ha encontrado el Router especificado" << endl;

    }
}

void Administrador::generarPaginas(int nroPaginas)
{

    for(int i = 0; i < nroPaginas; i++) {
        int index = 1 + rand() % terminales->size();
        Terminal *terminal = terminales->get(index);
        terminal->generarPagina();
    }
}

void Administrador::insertarArista(short IPorigen, short IPdestino, int ancho_de_banda)
{
    Router* router_origen = getRouter(IPorigen);
    Router* router_destino = getRouter(IPdestino);

    if(router_destino != NULL && router_origen != NULL)
    {
        Arista* nuevo = new Arista(ancho_de_banda, router_destino);

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

void Administrador::Dijkstra(short IPorigen, short IPdestino)
{
    Router* r_origen = getRouter(IPorigen);
    Router* r_destino = getRouter(IPdestino);

    if(r_origen == NULL)
        cout << "El vertice origen no existe" <<endl;
    else
    {
        map<Router*, map<Router*, int>> matriz;
        map<Router*, bool> visitados;           //Par ordenado con los Routers de la red y su booleano que indica si fue visitado
        map<Router*, Router*> rutas;            //Ruta que va desde el origen ingresado hacia cada Router de la red
        map<Router*, int> cola;                 //Se puede implementar con Lista y agregar ordenado
        //Cola<Router*>* cola2;                 //Cola que indica los siguientes nodos a visitar
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

            while(aj != NULL)
            {
                matriz[ri][aj->destino] = aj->ancho_de_banda;
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

            /*
             * Verificar si el destino ha sido alcanzado y corta
             */
            if (iter->first->IP == r_destino->IP) {
                cout << "Se llego al destino" << endl;
                break;
            }

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
            cout << i->first->IP <<": " << i->second << endl;


        //Muestra las rutas completas
        for(map<Router*, Router*>::iterator i = rutas.begin(); i != rutas.end(); i++)
        {
            Router* rActual = i->first;

            while(rActual != NULL)
            {
                cout << rActual->IP << " <- ";
                rActual = rutas[rActual];
            }

            cout << endl;
        }

    }
}

char* Administrador::rutaActual()
{
    char* buf = get_current_dir_name();

    // Obtiene la ruta actual

    // Convierte la ruta actual a una cadena de C++
    string pathAlt(buf);

    // Encuentra la última aparición de la barra diagonal
    size_t pos = pathAlt.find_last_of("/");

    if (pos != string::npos)        // Si se encontró la barra diagonal
        pathAlt.erase(pos);         // Elimina todo despues de la ultima barra diagonal


    string path2 = pathAlt + "/config.txt";

    char* path = strcpy(new char[path2.length() + 1], path2.c_str());

    return path;
}

void Administrador::leerArchivo()
{
    FILE* fp;
    fp = fopen(rutaActual(), "r");

    if (fp == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    // Leer la cantidad de routers
    fscanf(fp, "Routers: %d\n", &routers);
    printf("Cantidad de routers: %d\n", routers);

    // Saltar la línea "MatrizDeAdyacencia:"
    char buffer[100];
    fgets(buffer, 100, fp);

    // Leer las siguientes líneas
    for (int i = 0; i <= routers; i++) {
        for (int j = 0; j <= routers; j++) {
            fscanf(fp, "%d", &matriz[i][j]);
        }
        fgets(buffer, 100, fp);
    }

    // Imprimir la matriz
    printf("Matriz de adyacencia:\n");
    for (int i = 0; i <= routers; i++) {
        for (int j = 0; j <= routers; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }

    fclose(fp);
}