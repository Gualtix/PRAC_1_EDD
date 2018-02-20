#ifndef CLIENTE_H
#define CLIENTE_H

#include "QString"
#include "simplelist.h"

class Cliente{

public:
    QString Nit;
    QString Name;
    //SimpleList * LST_Compras;

    //(^< ............ ............ ............ Constructor
    Cliente(){
        Nit = "";
        Name = "";
        //LST_Compras = NULL;
    }

    //(^< ............ ............ ............ Constructor
    Cliente(QString Nt,QString Nm){
        Nit = Nt;
        Name = Nm;
    }

    //(^< ............ ............ ............ Obtener Numero de Factras
    int GetFactNum(){
        return 5;
    }

    ~Cliente(){

    }
};

#endif // CLIENTE_H
