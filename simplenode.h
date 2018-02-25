#ifndef SIMPLENODE_H
#define SIMPLENODE_H
#include "cliente.h"


class SimpleNode{
public:


    Cliente * Clt;
    SimpleNode * Next;

    //(^< ............ ............ ............ Constructor
    SimpleNode(){
        Clt = NULL;
        Next = NULL;
    }
    //(^< ............ ............ ............ Constructor
    SimpleNode(Cliente * TmpCliente){
        Clt = TmpCliente;
        Next = NULL;
    }



    //(^< ............ ............ ............ Destructor
    ~SimpleNode(){
        Next = NULL;
        delete Clt;
    }
};

#endif // SIMPLENODE_H
