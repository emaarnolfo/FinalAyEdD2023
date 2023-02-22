#include <iostream>
#include "headers/Administrador.h"

using namespace  std;

int main() {

    Administrador *admin = new Administrador();
    admin->leerArchivo();

    //Se generan paginas en las terminales
    Terminal *terminal = admin->terminales->get(2);
    terminal->generarPagina();
    terminal->generarPagina();
    terminal->generarPagina();


    /*
    admin->generarPaginas(admin->nroTerminales);
    admin->imprimirTermianles();
    */

    //Se mandan las paginas de los terminales a los Routers correspondientes
    admin->enviarPaginas();

    for (int i = 0; i < admin->nroRouters; i++)
        admin->Dijkstra(i + 1, 1);

    admin->ciclo();
    admin->ciclo();
    //admin->recalcular();
    admin->ciclo();
    admin->ciclo();
    //admin->recalcular();
    admin->ciclo();
    admin->ciclo();



    //admin->generarPaginas(admin->nroTerminales);

    cout << endl;
    cout << endl;


    int opc;

    /*
    while (opc != 16)
    {
        system("clear");

        cout << "1. Siguiente ciclo" << endl;
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