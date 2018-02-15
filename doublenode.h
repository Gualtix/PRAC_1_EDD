#ifndef DOUBLENODE_H
#define DOUBLENODE_H

#include "product.h"

class DoubleNode{
public:

    Product * Prod;
    DoubleNode * Next;
    DoubleNode * Previous;

    //(^< ............ ............ ............ Constructor
    DoubleNode(){

        Prod = NULL;
        Next = NULL;
        Previous = NULL;
    }

    //(^< ............ ............ ............ Constructor
    DoubleNode(Product * TmpProd){

        Prod = TmpProd;
        Next = NULL;
        Previous = NULL;
    }

    //(^< ............ ............ ............ Destructor
    ~DoubleNode(){
        delete Prod;
        Next = NULL;
        Previous = NULL;
    }
};



#endif // DOUBLENODE_H
