#ifndef FACTU_LIST_H
#define FACTU_LIST_H

#include "factu_node.h"
class Factu_List{
public:


    int ListSize;
    Factu_Node * First;
    Factu_Node * Last;

    //(^< ............ ............ ............ Constructor
    Factu_List(){
        ListSize = 0;
        First = NULL;
        Last  = NULL;
    }

    //(^< ............ ............ ............ Destructor
    ~Factu_List(){

    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ F A C T U R A S
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............



    //(^< ............ ............ ............ ............ ............ Insertar cuando la Lista este Vacia
    bool InsertWhenEmpty(Factura * TmpFact){
        if(ListSize == 0){
            First = Last = new Factu_Node(TmpFact);

            ListSize ++;
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Insertar al Frente
    bool FrontInsert(Factura * TmpFact){
        if(!InsertWhenEmpty(TmpFact)){
             Factu_Node * TmpNode = new Factu_Node(TmpFact);
             TmpNode->Next = First;
             First = TmpNode;
             ListSize++;
             return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Insertar al Fondo
    bool EndInsert(Factura * TmpFact){
        if(!InsertWhenEmpty(TmpFact)){
            Factu_Node * TmpNode = new Factu_Node(TmpFact);
            Last->Next = TmpNode;
            Last = TmpNode;
            ListSize ++;
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Obtener Nodo Espesifico
    Factu_Node * GetNode(int index){
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

            Factu_Node * TmpNode = First->Next;
            int cnt = 1;

            while (cnt < index) {
                TmpNode = TmpNode->Next;
                cnt++;
            }
            return TmpNode;
        }

        return NULL;
    }

    //(^< ............ ............ ............ ............ ............ Eliminar Nodo segun Indice
    void DeleteNode(int index){
        if(ListSize != 0){
            Factu_Node * TmpNode;

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
            TmpNode = GetNode(index);
            GetNode(index-1)->Next = TmpNode->Next;
            delete(TmpNode);
            ListSize--;
            return;

        }
    }
};
#endif // FACTU_LIST_H
