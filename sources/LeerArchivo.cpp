//
// Created by emanuel on 06/02/23.
//

#include "../headers/LeerArchivo.h"

char* rutaActual()
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

void leerArchivo()
{
    int routers;
    int matriz[10][10];
    FILE* fp;
    fp = fopen((char*)rutaActual(), "r");

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
    for (int i = 0; i < routers; i++) {
        for (int j = 0; j < routers; j++) {
            fscanf(fp, "%d", &matriz[i][j]);
        }
        fgets(buffer, 100, fp);
    }

    // Imprimir la matriz
    printf("Matriz de adyacencia:\n");
    for (int i = 0; i < routers; i++) {
        for (int j = 0; j < routers; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }

    fclose(fp);
}
