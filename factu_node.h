#ifndef FACTU_NODE_H
#define FACTU_NODE_H

#include "factura.h"

class Factu_Node{
  public:

    Factura * Fct;
    Factu_Node * Next;

    //(^< ............ ............ ............ Constructor
    Factu_Node(){
        Fct  = NULL;
        Next = NULL;
    }
    //(^< ............ ............ ............ Constructor
    Factu_Node(Factura * TmpFact){
        Fct = TmpFact;
        Next = NULL;
    }


    //(^< ............ ............ ............ Destructor
    ~Factu_Node(){
        Next = NULL;
        delete Fct;
    }

};

#endif // FACTU_NODE_H
