#ifndef PRODUCTSTACK_H
#define PRODUCTSTACK_H

#include "stacknode.h"
#include "detalle_factura.h"

class ProductStack{
public:

    int ListSize;
    double Total_esta_Factura;
    StackNode * First;
    StackNode * Last;

    //(^< ............ ............ ............ Constructor
    ProductStack(){
        ListSize = 0;
        Total_esta_Factura = 0;
        First = NULL;
        Last  = NULL;

    }

    //(^< ............ ............ ............ Destructor
    ~ProductStack(){

    }

    //(^< ............ ............ ............ ............ ............ Calcular Total
    /*double CalcularTotal(){
        if(ListSize > 0){

            int cnt = 0;
            double Total = 0;
            StackNode * TmpNode = First;
            while(cnt < ListSize && TmpNode != NULL){

                Total = Total + TmpNode->Det_Fact->Subtotal;
                TmpNode = TmpNode->Next;

            }
            Monto_Total = Total;
            return Total;

        }
        else{
            Monto_Total = 0;
            return 0;
        }

    }
    */
    //(^< ............ ............ ............ ............ ............ P U S H
    void Push_Product(Detalle_Factura * TmpDet){
        Total_esta_Factura = Total_esta_Factura + TmpDet->Subtotal;
        InsertAt(0,TmpDet);
    }

    //(^< ............ ............ ............ ............ ............ P O P
    StackNode * Pop_Product(){
        if(ListSize > 0){
            StackNode * TmpNode = GetNode(0);
            Total_esta_Factura = Total_esta_Factura - TmpNode->Det_Fact->Subtotal;
            DeleteNode(0);
            return TmpNode;
        }
        return NULL;

    }

    //(^< ............ ............ ............ ............ ............ Clear Stack
    void ClearStack(){
        if(ListSize > 0){
            while(ListSize > 0){
                Pop_Product();
            }
        }
    }

    //(^< ............ ............ ............ ............ ............ Insertar cuando la Lista este Vacia
    bool InsertWhenEmpty(Detalle_Factura * TmpDet){
        if(ListSize == 0){
            First = Last = new StackNode(TmpDet);

            ListSize ++;
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Insertar al Frente
    bool FrontInsert(Detalle_Factura * TmpDet){
        if(!InsertWhenEmpty(TmpDet)){
             StackNode * TmpNode = new StackNode(TmpDet);


             TmpNode->Next = First;
             First = TmpNode;
             ListSize++;
             return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Insertar al Fondo
    bool EndInsert(Detalle_Factura * TmpDet){
        if(!InsertWhenEmpty(TmpDet)){
            StackNode * TmpNode = new StackNode(TmpDet);

            Last->Next = TmpNode;
            Last = TmpNode;
            ListSize ++;
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Eliminar Nodo segun Indice
    void DeleteNode(int index){
        if(ListSize > 0 && First != NULL){
            StackNode * TmpNode;

            //Eliminar al Inicio
            if(index == 0){
                 TmpNode = First;
                 First = First->Next;
                 delete(TmpNode);
                 ListSize--;
                 return;

            }

            //Eliminar al Final
            if(index == (ListSize-1)){
                TmpNode = Last;
                Last = GetNode(index-1);
                delete(TmpNode);
                ListSize--;
                return;
            }

            //Eliminar valor Intermedio
            if(index != 0 && index < (ListSize-1))
            {

                TmpNode = GetNode(index);
                GetNode(index-1)->Next = TmpNode->Next;
                delete(TmpNode);
                ListSize--;
                return;
            }
        }
    }

    //(^< ............ ............ ............ ............ ............ Obtener Nodo Espesifico
    StackNode * GetNode(int index){
        if(index == 0){
            return First;
        }
        if(index == (ListSize-1)){
            return Last;
        }
        if(index == 1){
            return First->Next;
        }
        if(index > 1 && index < ListSize){

            StackNode * TmpNode = First->Next;
            int cnt = 1;

            while (cnt < index) {
                TmpNode = TmpNode->Next;
                cnt++;
            }
            return TmpNode;
        }

        return NULL;
    }

    //(^< ............ ............ ............ ............ ............ Insertar en Indice Especifico
    bool InsertAt(int index,Detalle_Factura * TmpDet){

        //Inserta estando vacia la lista
        if(index == 0 && ListSize == 0){
            InsertWhenEmpty(TmpDet);
            return true;
        }

        //Inserta al frente de la lista
        if(index == 0 && ListSize > 0){
            FrontInsert(TmpDet);
            return true;
        }

        //Agrega un nuevo elemento al final de la lista
        if(index == (ListSize)){
            EndInsert(TmpDet);
            return true;
        }


        //Inserta en un punto intermedio
        if(index >= 1 && index < ListSize){

            //Linkeo
            StackNode * TmpNode = GetNode(index-1);
            StackNode * NewNode = new StackNode(TmpDet);


            NewNode->Next = TmpNode->Next;
            TmpNode->Next = NewNode;

            ListSize++;

            return true;

        }

        return NULL;

    }

};

#endif // PRODUCTSTACK_H
