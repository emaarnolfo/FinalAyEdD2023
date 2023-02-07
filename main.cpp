#include <iostream>
#include "headers/Administrador.h"


using namespace  std;

int main() {

    //string path = rutaActual();



    cout << "hola mundo: " << endl;


    Administrador* admin = new Administrador();
    admin->leerArchivo();


/*
    admin->insertarRouter(1);
    admin->insertarRouter(2);
    admin->insertarRouter(3);
    admin->insertarRouter(4);
    admin->insertarRouter(5);
    admin->insertarRouter(6);
    admin->insertarRouter(7);

    admin->insertarArista(1,4,8);
    admin->insertarArista(2,3,17);
    admin->insertarArista(2,4,83);
    admin->insertarArista(2,6,97);
    admin->insertarArista(2,7,60);
    admin->insertarArista(3,1,4);
    admin->insertarArista(4,2,97);
    admin->insertarArista(4,3,37);
    admin->insertarArista(4,5,41);
    admin->insertarArista(4,7,64);
    admin->insertarArista(5,2,8);
    admin->insertarArista(5,6,92);
    admin->insertarArista(6,1,12);
    admin->insertarArista(6,2,8);
    admin->insertarArista(6,5,42);
    admin->insertarArista(7,4,17);

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

                admin->insertarRouter(IP);

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

                    admin->insertarArista(IPorigen,IPdestino, ancho_de_banda);
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
                    cout << "Ingrese el nombre del vertice destino: ";
                    cin >> ipDestino;

                    admin->Dijkstra(IPorigen, ipDestino);
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
    }

     */

    return 0;
}




