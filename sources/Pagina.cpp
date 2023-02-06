//
// Created by emanuel on 03/02/23.
//

#include "../headers/Pagina.h"
#include "../headers/Paquete.h"

Pagina::Pagina(int peso, IP destino) : peso(peso), destino(destino) {
    id = contPaginas++;
}

Pagina::Pagina(int idPag, int peso, IP destino) : id(idPag), peso(peso), destino(destino) {}


