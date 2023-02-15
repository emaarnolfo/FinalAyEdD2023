

#ifndef FINALAYEDD2023_LISTAS_H
#define FINALAYEDD2023_LISTAS_H

#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

template <class T> class Nodo {
private:
    T* dato;
    Nodo* next;
public:
    Nodo() { next = NULL; };
    Nodo(T* a) { dato = a; next = NULL; };
    //~Nodo();
    void set_next(Nodo* n) { next = n; };
    T* get_dato() { return dato; };
    void set_dato(T* d) { dato = d; };
    Nodo* get_next() { return next; };
    bool es_vacio() { return next == NULL; }
};

template <class T> class Lista {
private: Nodo<T>* czo;
    void addO(T d, Nodo<T>* ant);

public:
    Lista() { czo = new Nodo<T>(); };
    explicit Lista(Nodo<T>* n) { czo = n; };
    //~Lista(void);
    Nodo<T>* getCzo() { return czo; };
    void add(T* d);                      //sumar nodos a la lista
    bool esvacia();                     //Retorna true si la lista esta vacia
    T* cabeza();                         //retorna el dato del primer nodo
    Lista* resto();                     //retorna el puntero al "resto" de la lista
    //resto= lo que queda de la lista sin la cabeza
    T* get(int index);
    int size();                         //Devuele el tamaño de la lista
    bool esta(T d);                     // detecta si d esta en la lista
    void borrarD(T* d, Nodo<T>* ant);
    void borrarDato(T* d){               //borra el nodo que contiene d
        borrarD(d, NULL);
    }
    void borrar();                      //borra la cabeza de la lista
    void borrar_last(Nodo<T>* ant);     //borra el ultimo nodo de la lista
    void concat(Lista<T>* l1);          //Le transfiere los datos de l1 a this
    void tomar(int n);                  //deja "vivos" los n primeros nodos y borra el resto
    void addOrdenado(T d){              //sumar nodos a la lista Ordenados de menor a MAYOR
        addO(d, NULL);
    };
    T* last();                           //retorna el ultimo nodo de la lista
};


template <class T> class Pila:public Lista<T>{
public:
    Pila(){Lista<T>();};
    void apilar(T d)    {this->add(d);};
    T tope()            {return this->cabeza();};
    void desapilar()    {this->borrar();};
    bool pilavacia()    {return this->esvacia();};
};

template <class T> class Cola:public Lista<T>{
public:
    Cola(){Lista<T>();};
    T* tope()                 { return this->last(); };
    bool colavacia()         { return this->esvacia(); };
    void encolar(T* a)        { this->add(a); };
    void desencolar()        { this->borrar_last(nullptr); };
    T* ultimo()               { return this->cabeza(); };
    //string imprimir(string s){ return this->toPrint(s); };
};

template<class T>
T* Lista<T>::get(int index){
    if(index == 1)
        return cabeza();
    else
        return this->resto()->get(index-1);
}

template <class T>
T* Lista<T>::last()
{
    if (!this->esvacia()) {
        if (this->resto()->esvacia())
            return this->cabeza();
        return this->resto()->last();
    }
    return 0;
}


template <class T>
void Lista<T>::add(T* d) //100
{
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}
template <class T>
bool Lista<T>::esvacia()
{
    return czo->es_vacio();
}
template <class T>
T* Lista<T>::cabeza()
{
    if (this->esvacia()) {
        //cout << " ERROR, Cabeza de lista vacia ";
    }
    return czo->get_dato();
}

template <class T>
Lista<T>* Lista<T>::resto()
{
    auto* l = new Lista(czo->get_next());
    return (l);
}


template <class T> int Lista<T>::size()
{
    if (this->esvacia()) return 0;
    return 1 + this->resto()->size();
}

template <class T> void Lista<T>::borrar()
{ //borra el nodo cabeza
    if (!this->esvacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}

template <class T> void Lista<T>::borrar_last(Nodo<T>* ant)
{ // borra el ultimo nodo
    if (!this->esvacia()) {
        if ((czo->get_next())->get_next() == NULL) {
            if(ant == nullptr){
                this->borrar();
            }else{
                ant->set_next(czo->get_next());
                delete czo;
            }
        }
        else this->resto()->borrar_last(czo);
    }
}

template <class T> void Lista<T>::concat(Lista<T>* l1)
{// le transfiere los datos de l1 a this
    if (!(l1->esvacia())) {
        this->concat(l1->resto());
        this->add(l1->cabeza());
    }
}

template <class T> void Lista<T>::tomar(int n)
{ //deja "vivos" los n primeros nodos y borra el resto
    if (this->size() > n) {
        this->borrar_last();
        this->tomar(n);
    }
}

template <class T> bool Lista<T>::esta(T d)
{// busca d en la lista
    if (this->esvacia()) return false;
    if (this->cabeza() == d) return true;

    return this->resto()->esta(d);
}

template <class T>
void Lista<T>::borrarD(T* d, Nodo<T>* ant)
{
    if (!this->esvacia()) {
        if (d == this->cabeza()) {
            if (ant == NULL) {//al principio
                this->borrar();
            }
            else {//entre medio
                ant->set_next(czo->get_next());
                delete czo;
            }
        }
        else  this->resto()->borrarD(d, czo);
    }
}
#endif //FINALAYEDD2023_LISTAS_H
