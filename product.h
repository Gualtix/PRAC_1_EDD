#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "QString"
#include "detalle_factura.h"

class Product
{
public:

    QString Code;
    double  Price;
    int Units;
    QString Name;
    QString Description;

    bool Is_in_Use = false;

    Product() {
        Code  = "";
        Price = 0;
        Units = 0;
        Name  = "";
        Description = "";
        Is_in_Use = false;
    }

    //(^< ............ ............ ............ Constructor
    Product(QString CD,double Ps,int Unt,QString Nm,QString  Desc) {
        Code  = CD;
        Price = Ps;
        Units = Unt;
        Name  = Nm;
        Description = Desc;
        Is_in_Use = false;
        //SortValue = 0;
    }

    //(^< ............ ............ ............ Actualizar Informacion del Producto
    void UpdateProductInfo(QString CD,double Ps,int Unt,QString Nm,QString  Desc){
        Code  = CD;
        Price = Ps;
        Units = Unt;
        Name  = Nm;
        Description = Desc;
        Is_in_Use = false;
    }

     //(^< ............ ............ ............ Destructor
    ~Product(){

        Code  = "";
        Price = 0;
        Units = 0;
        Name  = "";
        Description = "";
        Is_in_Use = false;

        //SortValue = 0;
    }
};

#endif // PRODUCTS_H
