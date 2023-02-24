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
    cout << "Realizado por Arnolfo Emanuel" << endl;
    cout << endl << endl;

    int numArchivo;

    cout << "Elija el tipo de archivo que quiere abrir."
         << "Los siguientes se encuentran por defecto:" << endl <<endl;

    cout << "   - OPCION 1: Archivo 'config1.txt' el cual contiene " << endl
         << "   una red de varios Routers y Terminales" << endl <<endl;

    cout << "   - OPCION 2: Archivo 'config2.txt' el cual contiene" << endl
         << "   una red sencilla ideal para visualizar con " << endl
         << "   facilidad el cambio en los caminos de los paquetes "<< endl
         << "   según el trafico" << endl <<endl;

    cout << "Para armar uno propio cree un archivo txt llamado configX.txt," << endl
         << "siendo X un numero mayor a 3. El archivo debe incluir " << endl
         << "la cantidad de Routers, la matriz de adyacencia" << endl
         << " y las terminales de c/router" << endl << endl;

    cin >> numArchivo;

    Administrador *admin = new Administrador();
    admin->limpiarArchivos();
    admin->leerArchivo(numArchivo);

    for (int i = 0; i < admin->nroRouters; i++)
        admin->Dijkstra(i + 1, 1);

    cout << endl << endl;

    int opc = 1;

    cout << "Lectura correcta del archivo, presione enter para continuar" << endl;
    cin.get();
    cin.get();

    system("clear");

    while(opc!= 0)
    {
        system("clear");
        printf("Archivo de configuración en ejecucion: 'config%d.txt'\n\n", numArchivo);
        cout << "1: Generar Paginas aleatorias" << endl;
        cout << "2: Generar Paginas en terminal específica" << endl;
        cout << "3: Ciclo completo " << endl;
        cout << "4: Ejecutar n ciclos sin recomputar:" << endl;
        cout << "5: Ejecutar n ciclos contemplando el tráfico:" << endl;

        cout << "0: Salir" << endl <<endl;

        cout << "Ingrese la opcion que desee: ";
        cin >> opc;
        cout << endl;

        int num_ciclos, pagsAleatorias;

        system("clear");

        switch (opc) {

            case 1:
                cout << "Se generarán paginas con origenes y destinos aleatorios y se enviaran a los Routers." << endl
                     << "Indique el numero de paginas que desea crear: ";
                cin >> pagsAleatorias;

                admin->generarPaginas(pagsAleatorias);
                admin->enviarPaginas();

                break;

            case 2:
                int numPags, ipTerminal, ipRouter;
                Terminal* aux;

                cout << "Indique el numero de paginas que desea crear: ";
                cin >> numPags;

                cout << "Indique la IP del Router: ";
                cin >> ipRouter;

                cout << "Indique la IP de la Terminal: ";
                cin >> ipTerminal;

                cout << endl;

                aux = admin->getRouter(ipRouter)->getTerminal(ipTerminal);

                for(int i=0; i<numPags; i++)
                    aux->generarPagina();

                admin->enviarPaginas();
                break;

            case 3:
                admin->ciclo(0);
                break;

            case 4:
                cout << "Inserte la cantidad de ciclos a ejecutar: ";
                cin >> num_ciclos;

                for(int i=0; i < num_ciclos; i++)
                    admin->ciclo(0);
                break;

            case 5:
                cout << "Inserte la cantidad de ciclos a ejecutar: ";
                cin >> num_ciclos;

                for(int i=0; i < num_ciclos; i++)
                    admin->ciclo(1);
                break;

            case 0:
                return 0;
        }
        cout << endl;

        cout << "Presione enter para continuar ";
        cin.get();
        cin.get();
    }


/*

    Administrador *admin = new Administrador();
    admin->limpiarArchivos();
    admin->leerArchivo(2);

    for (int i = 0; i < admin->nroRouters; i++)
        admin->Dijkstra(i + 1, 1);

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
*/
    return 0;
}