//
// Created by emanuel on 24/01/23.
//

#include "../headers/Arista.h"

Arista::Arista(int ancho_de_banda, Router *destino) {
    this->ancho_de_banda = ancho_de_banda;
    this->destino = destino;
    this->next = NULL;
    this->peso = 10000/ancho_de_banda;    //peso = 10 x 10⁶ / BW  => BW: ancho de banda en Mega bits por segundos
}