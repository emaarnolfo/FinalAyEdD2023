//
// Created by emanuel on 31/01/23.
//

#ifndef FINALAYEDD2023_PAGINA_H
#define FINALAYEDD2023_PAGINA_H

#include "IP_Struct.h"
#include "Listas.h"

//Tamaño Maximo y Minimo de las paginas en MB
#define TAM_MAX_PAG 20
#define TAM_MIN_PAG 15

using namespace std;

class Paquete;

class Pagina {
    int id;
    int peso;
    IP destino;
    inline static int contPaginas = 1;          //Variable estatica para generar IDs diferentes en cada instancia de la clase

public:
    Pagina(int peso, IP destino);               //Constructor con ID automatica. Se utiliza para crar nuevas paginas
    Pagina(int idPag, int peso, IP destino);    //Constructor con ID por parametro. Se utliza para rearmar paginas en el Router destinos

    //Getters
    int getId() { return id; }
    int getPeso() { return peso; }
    IP getDestino() { return destino; }
    int getCont() { return contPaginas; };

    //Setters
    void setID(int id) { this->id = id; };
    void setContador(int cont) { contPaginas = cont; };
};

#endif //FINALAYEDD2023_PAGINA_H