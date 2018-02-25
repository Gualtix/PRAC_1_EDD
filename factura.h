#ifndef FACTURA_H
#define FACTURA_H

#include "QString"
#include "QDate"
#include "productstack.h"

class Factura{
public:

    QString Serial;
    int Correlative;
    QString Date;
    QString Nit;
    ProductStack * Prods_Stack;
    double Total;


    //(^< ............ ............ ............ ............ ............ Constructor
    Factura(){
        Serial = "";
        Correlative = 0;
        Date = QDate::currentDate().toString("dd/MM/yy");
        Nit = "C/F";
        Prods_Stack = NULL;
        Total = 0;
    }

    //(^< ............ ............ ............ ............ ............ Constructor
    Factura(QString Ser,int Correl, QString Dt, QString Nt, ProductStack * ProdStd){
        Serial = Ser;
        Correlative = Correl;
        Date = Dt;
        Nit = Nt;
        Prods_Stack = ProdStd;
        Total = 0;
    }

    //(^< ............ ............ ............ ............ ............ Destructor
    ~Factura(){
        if(Prods_Stack->ListSize > 0){
            //Prods_Stack->ClearStack();
        }
    }
};
#endif // FACTURA_H
