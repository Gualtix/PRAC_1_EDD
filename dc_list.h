#ifndef DC_LIST_H
#define DC_LIST_H

#include "doublenode.h"
#include "product.h"
#include "QFile"
#include "QTextStream"

class DC_List{
public:

    int ListSize;
    DoubleNode * First;
    DoubleNode * Last;

    //(^< ............ ............ ............ Constructor
    void DrawList(){

        //Graficar si la lista tiene mas de un elemento
        if(ListSize > 0){

            QFile Fl("Productos.dot");
            if(Fl.open(QFile::WriteOnly | QFile::Text)){
                QTextStream DotBf(&Fl);
                DotBf<<"digraph lista_producto {\n";
                DotBf<<"rankdir = LR\n";
                DotBf<<"node [shape = record]\n";

                //Datos Temporales del Nodo
                int cnt = 0;
                int PS1 = 0;
                int PS2 = 0;
                DoubleNode * TmpNode = First;
                QString Code  = TmpNode->Prod->Code;
                QString Name  = TmpNode->Prod->Name;
                QString Price = "Q "+QString::number(TmpNode->Prod->Price);

                while (cnt < ListSize) {

                    if(ListSize == 1){

                        //Cuerpo del Nodo
                        DotBf<<"P0 [label = \""+Code+"\\n"+Name+"\\n"+Price+"\"];\n";

                        //Enlace
                        DotBf<<"P0->P0;\n";
                        DotBf<<"P0->P0;\n";
                    }

                    if(ListSize > 1){
                        //Cuerpo del Nodo
                        DotBf<<"P"+QString::number(cnt)+"[label = \""+Code+"\\n"+Name+"\\n"+Price+"\"];\n";

                        //Enlace
                        if(cnt == (ListSize-1)){
                            PS1 = 0;
                            PS2 = ListSize-1;
                            DotBf<<"P0->P"+QString::number(ListSize-1)+";\n";
                            DotBf<<"P"+QString::number(ListSize-1)+"->P0;\n";
                        }
                        else{

                            DotBf<<"P"+QString::number(cnt)+"->P"+QString::number(cnt+1)+";\n";
                            DotBf<<"P"+QString::number(cnt+1)+"->P"+QString::number(cnt)+";\n";
                        }
                    }

                    cnt++;
                    TmpNode = TmpNode->Next;
                    Code = TmpNode->Prod->Code;
                    Name = TmpNode->Prod->Name;
                    Price = "Q "+QString::number(TmpNode->Prod->Price);
                }


                DotBf<<"}";
                Fl.close();
            }
            else{

            }

            system("dot -Tpng Productos.dot -o Prods.png");
            system("xdg-open /home/wrm/build-POS_PRAC_1-Desktop_Qt_5_10_0_GCC_64bit-Debug/Prods.png");

        }
        else{

        }
    }
    //(^< ............ ............ ............ Constructor
    DC_List(){
        ListSize = 0;
        First = NULL;
        Last  = NULL;
    }

    //(^< ............ ............ ............ Destructor
    ~DC_List(){

    }

    //(^< ............ ............ ............ Retrorno de Rango: Int
    int IntRangeReturn(){

    }

    //(^< ............ ............ ............ Retrorno de Rango: String
    int StringRangeReturn(QString TmpStr){
        int cnt = 0;
        DoubleNode * TmpNode = First;

        int Eval = TmpStr.compare(TmpNode->Prod->Code);
        while (cnt < ListSize && Eval >= 0) {
            //Filtro para verificar Codigo Unico
            if(Eval == 0){
                return -100;
            }
            TmpNode = TmpNode->Next;
            Eval = TmpStr.compare(TmpNode->Prod->Code);
            cnt++;
        }

        return cnt;
    }

    //(^< ............ ............ ............ Retrorno de Rango: Double
    int DoubleRangeReturn(){

    }

    //(^< ............ ............ ............ Insertar ordenado por: Codigo
    int InsertSortedByCode(Product * TmpProd){
        if(!InsertWhenEmpty(TmpProd)){
            int Rank = StringRangeReturn(TmpProd->Code);
            TmpProd->SortValue = Rank;

            InsertAt(Rank,TmpProd);
            return Rank;
        }
        else{
            return 0;
        }

    }

    //(^< ............ ............ ............ Ordenar por Codigo
    bool SortByCode(){

        return true;
    }

    //(^< ............ ............ ............ Validar Codigo Unico
    bool ValidateUnique(QString Code){

        int Rk = StringRangeReturn(Code);
        if(Rk == -100){
            return false;
        }
        return true;
    }

    //(^< ............ ............ ............ Adelantar un Nodo
    void AdvanceNode(){

    }

    //(^< ............ ............ ............ Atrazar   un Nodo
    void DelayNode(){

    }


    //(^< ............ ............ ............ Ordenar por Precio
    bool SortByPrice(){
        return true;
    }



    //(^< ............ ............ ............ Ordenar por Nombre
    bool SortByName(){
        return true;
    }

    //(^< ............ ............ ............ Insertar cuando la Lista este Vacia
    bool InsertWhenEmpty(Product * TmpProd){
        if(ListSize == 0){
            First = Last = new DoubleNode(TmpProd);

            First->Next = Last;
            First->Previous = Last;

            ListSize ++;
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ Insertar al Frente
    bool FrontInsert(Product * TmpProd){
        if(!InsertWhenEmpty(TmpProd)){
             DoubleNode * TmpNode = new DoubleNode(TmpProd);
             First->Previous = TmpNode;
             TmpNode->Next = First;

             TmpNode->Previous = Last;
             Last->Next = TmpNode;

             First = TmpNode;

             ListSize++;
             return true;
        }
        return false;
    }

    //(^< ............ ............ ............ Insertar al Fondo
    bool EndInsert(Product * TmpProd){
        if(!InsertWhenEmpty(TmpProd)){
            DoubleNode * TmpNode = new DoubleNode(TmpProd);
            Last->Next = TmpNode;
            TmpNode->Previous = Last;

            TmpNode->Next = First;
            First->Previous = TmpNode;
            Last = TmpNode;

            ListSize ++;
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ Obtener Nodo Espesifico
    DoubleNode * GetNode(int index){
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

            DoubleNode * TmpNode = First->Next;
            int cnt = 1;

            while (cnt < index) {
                TmpNode = TmpNode->Next;
                cnt++;
            }
            return TmpNode;
        }

        return NULL;
    }

    //(^< ............ ............ ............ Eliminar Nodo segun Indice
    bool DeleteNode(int index){
        DoubleNode * TmpNode = GetNode(index);
        //Lista vacia
        if(ListSize == 0){
            return false;
        }

        //Lista con solo un elemento
        if(ListSize == 1){
            delete(First);
            First = Last = NULL;
            ListSize = 0;

            return true;
        }

        //Elimina el primer nodo de la lista
        if(index == 0){

            First->Next->Previous = Last;
            Last->Next = First->Next;
            First = First->Next;

            delete(TmpNode);
            TmpNode = NULL;

            ListSize--;
            return true;
        }

        //Elimina el ultimo nodo de la lista
        if(index == (ListSize-1)){


            Last->Previous->Next = First;
            First->Previous = Last->Previous;
            Last = Last->Previous;

            delete(TmpNode);
            TmpNode = NULL;

            ListSize--;
            return true;
        }

        //Elimina un nodo intermedio
        if(index >= 1 && index<ListSize){

            TmpNode->Previous->Next = TmpNode->Next;
            TmpNode->Next->Previous = TmpNode->Previous;

            delete(TmpNode);
            TmpNode = NULL;

            ListSize--;
            return true;
        }


        return false;
    }
    //(^< ............ ............ ............ Obtener nodo por codigo
    DoubleNode * GetNodeByCode(QString Code){
        DoubleNode * TmpNode = First;
        int cnt = 0;
        while(cnt < ListSize){
            if(TmpNode->Prod->Code.compare(Code) == 0){
                return TmpNode;
            }
            else{
                TmpNode = TmpNode->Next;
                cnt++;
            }
        }
        return NULL;
    }
    //(^< ............ ............ ............ Insertar en Indice Especifico
    bool InsertAt(int index,Product * TmpProd){

        //Inserta estando vacia la lista
        if(index == 0 && ListSize == 0){
            InsertWhenEmpty(TmpProd);
            return true;
        }

        //Inserta al frente de la lista
        if(index == 0 && ListSize > 0){
            FrontInsert(TmpProd);
            return true;
        }

        //Agrega un nuevo elemento al final de la lista
        if(index == (ListSize)){
            EndInsert(TmpProd);
            return true;
        }


        //Inserta en un punto intermedio
        if(index >= 1 && index < ListSize){

            //Linkeo
            DoubleNode * TmpNode = GetNode(index-1);
            DoubleNode * NewNode = new DoubleNode(TmpProd);

            NewNode->Next = TmpNode->Next;
            NewNode->Previous = TmpNode;

            TmpNode->Next->Previous = NewNode;
            TmpNode->Next = NewNode;

            ListSize++;

            return true;

        }

        return NULL;

    }
};

#endif // DC_LIST_H
