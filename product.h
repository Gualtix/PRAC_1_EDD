#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "QString"

class Product
{
public:

    QString Code;
    double  Price;
    int Units;
    QString Name;
    QString Description;

    int SortValue;

    Product() {
        Code  = "";
        Price = 0;
        Units = 0;
        Name  = "";
        Description = "";
    }

    //(^< ............ ............ ............ Constructor
    Product(QString CD,double Ps,int Unt,QString Nm,QString  Desc) {
        Code  = CD;
        Price = Ps;
        Units = Unt;
        Name  = Nm;
        Description = Desc;

        SortValue = 0;
    }

    //(^< ............ ............ ............ Actualizar Informacion del Producto
    void UpdateProductInfo(QString CD,double Ps,int Unt,QString Nm,QString  Desc){
        Code  = CD;
        Price = Ps;
        Units = Unt;
        Name  = Nm;
        Description = Desc;
    }

     //(^< ............ ............ ............ Destructor
    ~Product(){

        Code  = "";
        Price = 0;
        Units = 0;
        Name  = "";
        Description = "";

        SortValue = 0;
    }
};

#endif // PRODUCTS_H
