#ifndef DETALLE_FACTURA_H
#define DETALLE_FACTURA_H

#include "QString"

class Detalle_Factura{

public:
    QString Codigo;
    QString Descipcion;
    double  Precio_Unitario;
    int     Cantidad;
    double  Descuento;
    double  Subtotal;

    //(^< ............ ............ ............ ............ ............ Constructor
    Detalle_Factura(){
        Codigo = "";
        Descipcion = "";
        Precio_Unitario = 0;
        Cantidad = 0;
        Descuento = 0;
        Subtotal = 0;
    }

    //(^< ............ ............ ............ ............ ............ Constructor
    Detalle_Factura(QString Code,QString Descrip,double Pres_Unit,int Cant,double Desc){
        Codigo     = Code;
        Descipcion = Descrip;
        Precio_Unitario  = Pres_Unit;
        Cantidad   = Cant;
        Descuento  = Desc;
        Subtotal = Cantidad * Precio_Unitario * (1-Descuento);
    }

    //(^< ............ ............ ............ ............ ............ Constructor
    Detalle_Factura(QString Code,int Cant,double Desc){
        Codigo     = Code;
        Descipcion = "--- No Disponible ---";
        Precio_Unitario  = 0;
        Cantidad   = Cant;
        Descuento  = Desc;
        Subtotal = Cantidad * Precio_Unitario * (1-Descuento);
    }


    //(^< ............ ............ ............ ............ ............ Destructor
    ~Detalle_Factura(){

    }

    //(^< ............ ............ ............ ............ ............ Calcular Subtotal
    //double CalcularSubtotal(){
    //    Subtotal = Cantidad * Precio_Unitario * (1-Descuento);
    //    return Subtotal;
    // }

};

#endif // DETALLE_FACTURA_H
