//
// Created by emanuel on 24/01/23.
//

#include "../headers/Administrador.h"

Administrador::Administrador() {
    this->primero = NULL;
    this->tamanio = 0;
}

bool Administrador::esVacio() {
    if(primero == NULL)
        return true;
    return false;
}

Router* Administrador::getRouter(short IP) {
    Router* aux = primero;

    while(aux != NULL)
    {
        if(aux->IP == IP)
            return aux;

        aux = aux->next;
    }

    return NULL;
}

void Administrador::insertarRouter(short int IP)
{
    Router* nuevo = new Router(IP);


    if(esVacio())
    {
        primero = nuevo;
    }
    else
    {
        Router* aux = primero;

        while(aux->next != NULL)
            aux = aux->next;

        aux->next = nuevo;
        tamanio++;
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
    Router* i = primero;

    while(i != NULL)
    {
        Arista* j = i->arista;
        cout << "\x1b[31m" << i->IP << " = ";

        while(j != NULL)
        {
            cout << "\x1b[31m" << i->IP <<"\x1b[32m" <<"->" <<j->ancho_de_banda << "\x1b[31m" << "->" <<j->destino->IP;
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

void Administrador::Dijkstra(short IPorigen)
{
    Router* r_origen = getRouter(IPorigen);

    if(r_origen == NULL)
        cout << "El vertice origen no existe" <<endl;
    else
    {
        map<Router*, map<Router*, int>> matriz;
        map<Router*, bool> visitados;
        map<Router*, Router*> rutas;
        map<Router*, int> cola;         //Se debe reemplazar por una cola simple
        map<Router*, int> distancias;

        Router* ri = primero;

        while(ri != NULL)
        {
            visitados[ri] = false;
            rutas[ri] = NULL;
            distancias[ri] = numeric_limits<int>::max();

            Router* rj = primero;

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
        cola[r_origen] = distancias[r_origen];

        //Recorremos los nodos para sacar los recorridos
        while(!cola.empty())
        {
            map<Router*, int>::iterator iter = min_element(cola.begin(), cola.end(), costoMinimo);
            visitados[iter->first] = true;

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
                    }
                }
                ai = ai->next;
            }

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

        if(cola.empty())
            cout << "Cola vacia" <<endl;

    }
}