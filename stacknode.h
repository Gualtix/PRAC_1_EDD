#ifndef STACKNODE_H
#define STACKNODE_H

#include "detalle_factura.h"

class StackNode{
public:

    Detalle_Factura * Det_Fact;
    StackNode * Next;

    //(^< ............ ............ ............ Constructor
    StackNode(){
        Det_Fact  = NULL;
        Next = NULL;
    }
    //(^< ............ ............ ............ Constructor
    StackNode(Detalle_Factura * TmpDetFact){
        Det_Fact = TmpDetFact;
        Next = NULL;
    }

    //(^< ............ ............ ............ Destructor
    ~StackNode(){
        Next = NULL;
        delete Det_Fact;
    }

};

#endif // STACKNODE_H
