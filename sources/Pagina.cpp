//
// Created by emanuel on 03/02/23.
//

#include "../headers/Pagina.h"
#include "../headers/Paquete.h"

Pagina::Pagina(int peso, IP destino) : peso(peso), destino(destino) {
    id = contPaginas++;
}

/*
Cola<Paquete> *Pagina::desarmarPagina() {

    int numPaquetes = 1 + rand() % 30;              //10
    int pesoRestante = this->peso;                  //83
    int pesoPaquete = this->peso / numPaquetes;     //8
    Cola<Paquete>* colaPaquetes = new Cola<Paquete>();

    while(pesoRestante > pesoPaquete*2)             //11 > 16
    {
        Paquete* nuevo = new Paquete(this->peso, this->destino, pesoPaquete);   //PesoPag - DestinoPag - 8
        colaPaquetes->add(nuevo);                //19 paquete
        pesoRestante -= pesoPaquete;                //11
    }

    Paquete* ultimo = new Paquete(this->peso, this->destino, pesoRestante);
    colaPaquetes->add(ultimo);

    return colaPaquetes;

}

*/