#include <iostream>
#include "headers/Administrador.h"

using namespace  std;


int main() {

    cout << " ----------------------------------------------------------------" << endl;
    cout << "|                SIMULACION DE TRAFICO DE INTERNET               |"<< endl;
    cout << "| Este programa en C++ consiste en simular una red de Internet   |"<< endl;
    cout << "| Armando Routers y terminales que estan conectados entre si,    |"<< endl;
    cout << "| y simulando el envio de paginas y paquetes que se produce      |"<< endl;
    cout << "| a traves de los mismos. Para ello, se utilizan esctructuras    |"<< endl;
    cout << "| de datos como listas y colas enlazadas y grafos direccionales. |"<< endl;
    cout << "| Asi como también algoritmos como el de Dijkstra.               |"<< endl;
    cout << " ----------------------------------------------------------------" << endl;
    cout << endl << endl;

    int numArchivo;

    cout << "Elija el tipo de archivo que quiere abrir. Los siguientes se encuentran por defecto:" << endl <<endl;

    cout << "   - OPCION 1: Archivo 'config1.txt' el cual contiene una red compleja " << endl
         << "que genera paquetes aleatorios con destinos aleatorios y muestra los resultados." << endl
         << "de cada ciclo en los archivos que va generando" << endl << endl;

    cout << "   - OPCION 2: Archivo 'config2.txt' el cual contiene una red sencilla que demuestra " << endl
         << "como cambian la ruta los paquetes cuando hay mucho trafico." << endl <<endl;

    cout << "Para armar uno propio cree un archivo txt llamado configX.txt, siendo X un numero mayor a 3" << endl
         << "El archivo debe incluir la cantidad de Routers, la matriz de adyacencia y las terminales de c/router" << endl << endl;

    cin >> numArchivo;

    Administrador *admin = new Administrador();
    admin->limpiarArchivos();
    admin->leerArchivo(numArchivo);

    cout << endl << endl;
/*
    int opc;

    while(opc!= 0)
    {
        cout << "1: Generar Paginas aleatorias" << endl;
        cout << "2: Imprimir Terminales" << endl;
        cout << "3: Imprimir Routers" << endl;
        cout << "3: Ciclo completo" << endl;
        cout << "4: Recalcular rutas" << endl;
        cout << "5: Ejecutar n ciclos:" << endl;
        cout << "0: Salir" << endl <<endl;

        cout << "Inserte la opcion que desee: ";
        cin >> opc;
        switch (opc) {
            case 1:
                cout << "Generar paginas" << endl;
                break;

            case 2:

                break;

            case 3:

                break;

            case 4:

                break;

            case 5:
                int num_ciclos;
                cout << "Inserte la cantidad de ciclos a ejecutar: ";
                cin >> num_ciclos;

                for(int i=0; i <= num_ciclos; i++)
                {
                    admin->ciclo();
                    if(i % 2 == 0 && i != 0)
                        admin->recalcular();
                }

                break;

            case 6:
                return 0;
        }

        cin.get();
    }


/*
 */
    //Se generan paginas en las terminales
    Terminal *terminal = admin->terminales->get(2);
    terminal->generarPagina();
    terminal->generarPagina();
    admin->imprimirTermianles();

    //Se mandan las paginas de los terminales a los Routers correspondientes
    admin->enviarPaginas();

    for (int i = 0; i < admin->nroRouters; i++)
        admin->Dijkstra(i + 1, 1);

    admin->ciclo();
    admin->ciclo();
    admin->recalcular();
    admin->ciclo();
    admin->ciclo();
    admin->recalcular();
    admin->ciclo();
    admin->ciclo();
    admin->recalcular();
    admin->ciclo();
    admin->ciclo();



    //admin->generarPaginas(admin->nroTerminales);

    cout << endl;
    cout << endl;




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