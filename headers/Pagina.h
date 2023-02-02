//
// Created by emanuel on 31/01/23.
//

#ifndef FINALAYEDD2023_PAGINA_H
#define FINALAYEDD2023_PAGINA_H

using namespace std;

class Pagina {
    int ID;
    int peso;
    short int destino;

    public:
    Pagina(int ID, int peso, short int destino);
    int getId() const { return ID; }
    int getPeso() const { return peso; }
    short getDestino() const { return destino; }

};

class Paquete: public Pagina {
    int ID_paq;
    int peso_paq;
    short int destino_paq;

public:
    Paquete(int id, int peso, short destino, int idPaq, int pesoPaq, short destinoPaq) :
    Pagina(id, peso, destino),
    ID_paq(idPaq), peso_paq(pesoPaq), destino_paq(destinoPaq) {}
    int getIdPaq() const { return ID_paq; }
    int getPesoPaq() const { return peso_paq; }
    short getDestinoPaq() const { return destino_paq; }

};

#endif //FINALAYEDD2023_PAGINA_H
