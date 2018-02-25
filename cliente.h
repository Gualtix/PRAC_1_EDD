#ifndef CLIENTE_H
#define CLIENTE_H

#include "QString"
#include "factu_list.h"

class Cliente{

public:
    QString Nit;
    QString Name;
    Factu_List * Lista_de_Facturas;


    //(^< ............ ............ ............ Constructor
    Cliente(){
        Nit = "";
        Name = "";
        Lista_de_Facturas = new Factu_List();
    }

    //(^< ............ ............ ............ Constructor
    Cliente(QString Nt,QString Nm){
        Nit = Nt;
        Name = Nm;
        Lista_de_Facturas = new Factu_List();
    }

    //(^< ............ ............ ............ Constructor
    Cliente(QString Nt,QString Nm,Factu_List * Factlist){
        Nit = Nt;
        Name = Nm;
        Lista_de_Facturas = Factlist;
    }

    //(^< ............ ............ ............ Obtener Numero de Factras
    /*int GetFactNum(){
        if(Lista_de_Facturas != NULL){
            return Lista_de_Facturas->ListSize;
        }
        else{
            return 0;
        }
    }
    */

    ~Cliente(){

    }
};

#endif // CLIENTE_H
