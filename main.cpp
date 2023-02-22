#include <iostream>
#include "headers/Administrador.h"

using namespace  std;

int main() {

    Administrador *admin = new Administrador();
    admin->leerArchivo();

    //Se generan paginas en las terminales
    admin->generarPaginas(admin->nroTerminales);
    admin->imprimirTermianles();


    //Se mandan las paginas de los terminales a los Routers correspondientes
    admin->enviarPaginas();

    for (int i = 0; i < admin->nroRouters; i++)
        admin->Dijkstra(i + 1);

    admin->ciclo();
    admin->ciclo();
    admin->ciclo();


    admin->generarPaginas(admin->nroTerminales);

    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    /*

    cout << "Ciclo 1" << endl;
    admin->ciclo();
    admin->imprimirPaginas();
    admin->imprimirPaquetes();

    cout << "Ciclo 2" << endl;
    admin->ciclo();
    admin->imprimirPaginas();
    admin->imprimirPaquetes();

    cout << "Ciclo 3" << endl;
    admin->ciclo();
    admin->imprimirPaginas();
    admin->imprimirPaquetes();

    cout << "Ciclo 4" << endl;
    admin->ciclo();
    admin->imprimirPaginas();
    admin->imprimirPaquetes();

    /*
    for(int i= 0; i < admin->nroRouters; i++){

        admin->getRouter(i+1)->desarmarPaginas();       //Las paginas generadas se transforman en paquetes que se agregan a la cola de paquetes
        admin->getRouter(i+1)->ordenarPaquetes();       //Los paquetes que se encuentran en el Router desstino pasan a la lista de paquetes en destino
        admin->getRouter(i+1)->enviarPaquetes();        //Se envian los paquetes al destino correspondiente segun la tabla de enrutamiento
        admin->getRouter(i+1)->ordenarPaquetes();       //Se ordenan los paquetes nuevos que llegan desde los routers vecinos
    }
     */

    /*
    admin->addRouter(1);
    admin->addRouter(2);
    admin->addRouter(3);

    admin->addArista(1,2,10);
    admin->addArista(1,3,50);
    admin->addArista(2,1,50);
    admin->addArista(2,3,50);
    admin->addArista(3,1,50);
    admin->addArista(3,2,50);

    admin->addTerminal(1,1);
    admin->addTerminal(2, 1);
    admin->addTerminal(3, 1);

    admin->generarPaginas(1);

    IP dest = {2, 1};
    Pagina* nueva = new Pagina(50, dest);
    admin->getRouter(1)->getTerminal(1)->pagPendiendes->encolar(nueva);

    //Se envian todas las paginas que las terminales tengan pendientes
    for(int i = 1; i <= admin->nroTerminales; i++)
        admin->terminales->get(i)->enviarPaginas();


    admin->getRouter(1)->desarmarPagina();
    //admin->getRouter(1)->ordenarPaquetes();

    //admin->generarPaginas(2);
    //admin->getRouter(1)->armarPaginas();

    admin->Dijkstra(1);
    admin->getRouter(1)->enviarPaquetes();
    admin->getRouter(2)->ordenarPaquetes();
    admin->getRouter(2)->armarPaginas();
    admin->getRouter(2)->enviarPaginas();

    cout << "hola mundo: " << endl;

/*
    admin->addRouter(1);
    admin->addRouter(2);
    admin->addRouter(3);
    admin->addRouter(4);
    admin->addRouter(5);
    admin->addRouter(6);
    admin->addRouter(7);

    admin->addArista(1,4,8);
    admin->addArista(2,3,17);
    admin->addArista(2,4,83);
    admin->addArista(2,6,97);
    admin->addArista(2,7,60);
    admin->addArista(3,1,4);
    admin->addArista(4,2,97);
    admin->addArista(4,3,37);
    admin->addArista(4,5,41);
    admin->addArista(4,7,64);
    admin->addArista(5,2,8);
    admin->addArista(5,6,92);
    admin->addArista(6,1,12);
    admin->addArista(6,2,8);
    admin->addArista(6,5,42);
    admin->addArista(7,4,17);

    //admin->mostrarListaAdyacencia();

    int opc;

    while (opc != 16)
    {
        system("clear");

        cout << "1. Insertar vertice" << endl;
        cout << "2. Insertar arista" << endl;
        cout << "3. Obtener tamano" << endl;
        cout << "4. Mostrar lista de adyacencia" << endl;
        cout << "13. Dijkstra" << endl;
        cout << "16. Salir" << endl;

        cout << "\nIngrese una opcion del menu: ";
        cin >> opc;

        system("clear");      //El comando 'cls' limpia la consola

        switch (opc)
        {
            case 1:
            {
                short int IP;
                cout << "Ingrese el IP del Router: ";
                cin >> IP;

                admin->addRouter(IP);

                break;
            }
            case 2:
            {
                if (admin->esVacio())
                    cout << "El grafo esta vacio" << endl;
                else
                {
                    short int IPorigen, IPdestino;
                    int ancho_de_banda;
                    cout << "Ingrese la IP del Router origen: ";
                    cin >> IPorigen;
                    cout << "Ingrese la IP del Router destino: ";
                    cin >> IPdestino;
                    cout << "Ingrese el precio: ";
                    cin >> ancho_de_banda;

                    admin->addArista(IPorigen,IPdestino, ancho_de_banda);
                }
                break;
            }
            case 3:
            {
                cout << "El grafo tiene " << admin->getTamanio() << " vertices" << endl;
                break;
            }
            case 4:
            {
                if (admin->esVacio())
                    cout << "El grafo esta vacio" << endl;
                else
                    admin->mostrarListaAdyacencia();
                break;
            }
            case 13:
            {
                if (admin->esVacio())
                    cout << "El grafo esta vacio" << endl;
                else
                {
                    short int IPorigen;
                    short int ipDestino;
                    cout << "Ingrese el nombre del vertice origen: ";
                    cin >> IPorigen;

                    admin->Dijkstra(IPorigen);
                }
                break;
            }
            case 16:
            {
                return 0;
            }
        }
        cin.get();
        cin.get();
    }*/
    return 0;
}