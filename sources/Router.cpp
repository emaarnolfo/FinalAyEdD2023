//
// Created by emanuel on 24/01/23.
//

#include "../headers/Router.h"

Router::Router(short int IP) {
    this->IP = IP;
    this->next = NULL;
    this->arista = NULL;

    //std::cout << "Constructor Router" << std::endl;

}