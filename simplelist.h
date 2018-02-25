#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#include "simplenode.h"
#include "product.h"
#include "QFile"
#include "QTextStream"

class SimpleList{
public:

    int ListSize;
    SimpleNode * First;
    SimpleNode * Last;
    int ID_Rank;

    //(^< ............ ............ ............ Constructor
    SimpleList(){
        ListSize = 0;
        First = NULL;
        Last  = NULL;
        ID_Rank = 0;
    }

    //(^< ............ ............ ............ Destructor
    ~SimpleList(){

    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ C L I E N T
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    //(^< ............ ............ ............ ............ ............ Graficar Lista
    void DrawList(){

        //Graficar si la lista tiene mas de un elemento
        if(ListSize > 0){

            QFile Fl("Clientes.dot");
            if(Fl.open(QFile::WriteOnly | QFile::Text)){
                QTextStream DotBf(&Fl);
                DotBf<<"digraph lista_cliente {\n";
                DotBf<<"rankdir = LR\n";
                DotBf<<"node [shape = record]\n";

                //Datos Temporales del Nodo
                int cnt = 0;
                SimpleNode * TmpNode = First;
                QString Nit  = TmpNode->Clt->Nit;
                QString Name  = TmpNode->Clt->Name;
                QString Fact = "Q "+QString::number(TmpNode->Clt->Lista_de_Facturas->ListSize);

                while (cnt < ListSize) {

                    if(ListSize == 1){

                        //Cuerpo del Nodo
                        DotBf<<"P0 [label = \""+Nit+"\\n"+Name+"\\n"+Fact+"\"];\n";
                        break;
                    }

                    if(ListSize > 1){
                        //Cuerpo del Nodo
                        DotBf<<"P"+QString::number(cnt)+"[label = \""+Nit+"\\n"+Name+"\\n"+Fact+"\"];\n";

                        //Enlace
                        if(cnt != (ListSize-1)){
                            DotBf<<"P"+QString::number(cnt)+"->P"+QString::number(cnt+1)+";\n";
                        }
                    }

                        TmpNode = TmpNode->Next;

                    if(TmpNode != NULL){
                        cnt++;
                        Nit = TmpNode->Clt->Nit;
                        Name = TmpNode->Clt->Name;
                        Fact = "Facturas "+QString::number(TmpNode->Clt->Lista_de_Facturas->ListSize);
                    }
                    else{
                        break;
                    }
                }

                DotBf<<"}";
                Fl.close();
            }
            else{

            }

            //system("dot -Tpng Clientes.dot -o Clients.png");
            //system("xdg-open /home/wrm/build-POS_PRAC_1-Desktop_Qt_5_10_0_GCC_64bit-Debug/Clients.png");

            //system("dot -Tpng Clientes.dot -o Clients.png");
            system("xdg-open ./Clientes.dot");

        }
        else{

        }
    }

    //(^< ............ ............ ............ ............ ............ Retrorno de Rango: String
    int StringRangeReturn(QString TmpStr){
        SimpleNode * TmpNode = First;
        int Eval = TmpStr.compare(TmpNode->Clt->Nit);
        int cnt = 0;

        while(TmpNode != NULL){

            Eval = TmpStr.compare(TmpNode->Clt->Nit);
            if(Eval <= 0){
                break;
            }
            TmpNode = TmpNode->Next;
            cnt++;
        }

        if(Eval == 0){
            return -100;
        }

        return cnt;
    }

    //(^< ............ ............ ............ ............ ............ Insertar ordenado por: Nit
    int InsertSortedByNit(Cliente * TmpClient){
        //Verificamos que la lista no este vacia
        if(!InsertWhenEmpty(TmpClient)){
            //Verificamos que el Nit a ingresar sea unico
            if(ValidateUnique(TmpClient->Nit)){
                InsertAt(ID_Rank,TmpClient);
                return ID_Rank;
            }
            else{
                return -100;
            }
        }
        else{
            return 0;
        }
    }

    //(^< ............ ............ ............ ............ ............ Validar Codigo Unico
    bool ValidateUnique(QString Code){

        ID_Rank = StringRangeReturn(Code);
        if(ID_Rank == -100){
            return false;
        }
        return true;
    }

    //(^< ............ ............ ............ ............ ............ Insertar cuando la Lista este Vacia
    bool InsertWhenEmpty(Cliente * TmpClient){
        if(ListSize == 0){
            First = Last = new SimpleNode(TmpClient);

            ListSize ++;
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Insertar al Frente
    bool FrontInsert(Cliente * TmpClient){
        if(!InsertWhenEmpty(TmpClient)){
             SimpleNode * TmpNode = new SimpleNode(TmpClient);


             TmpNode->Next = First;
             First = TmpNode;
             ListSize++;
             return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Insertar al Fondo
    bool EndInsert(Cliente * TmpClient){
        if(!InsertWhenEmpty(TmpClient)){
            SimpleNode * TmpNode = new SimpleNode(TmpClient);

            Last->Next = TmpNode;
            Last = TmpNode;
            ListSize ++;
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Obtener Nodo Espesifico
    SimpleNode * GetNode(int index){
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

            SimpleNode * TmpNode = First->Next;
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
        if(ListSize > 0){
            SimpleNode * TmpNode;

            //Eliminar al Inicio
            if(index == 0){
                 TmpNode = First;
                 First = First->Next;
                 delete(TmpNode);
                 return;

            }

            //Eliminar al Final
            if(index == (ListSize-1)){
                TmpNode = Last;
                Last = GetNode(index-1);
                delete(TmpNode);
                return;
            }

            //Eliminar valor Intermedio
            if(index != 0 && index < (ListSize-1))
            {

                TmpNode = GetNode(index);
                GetNode(index-1)->Next = TmpNode->Next;
                delete(TmpNode);
                return;
            }
        }
    }

    //(^< ............ ............ ............ ............ ............ Busqueda Binaria
    SimpleNode * BinarySearch(QString k){

        int Sup = ListSize;
        int Cnt = 0;
        int Inf = 0;
        int PM = (Sup + Inf)/2;

        if(PM == ListSize){
            PM--;
        }
        SimpleNode * TmpNode = GetNode(PM);

        while((Sup - Inf) > 0 && Cnt == 0 && TmpNode != NULL){

            if((Sup - Inf) == 1){
                Cnt = 1;
            }


            //if(A[PM] == k){
            if(TmpNode->Clt->Nit.compare(k) == 0){
                //return PM;
                return TmpNode;

            }
            else{
                //if(A[PM] > k){
                int Rs = TmpNode->Clt->Nit.compare(k);
                if(Rs < 0){


                    //Sup = PM;
                    //PM  = (Sup + Inf)/2;
                    //TmpNode = GetNode(PM);



                    Inf = PM;
                    PM  = (Sup + Inf)/2;
                    TmpNode = GetNode(PM);
                }
                else{




                    //Inf = PM;
                    //PM  = (Sup + Inf)/2;
                    //TmpNode = GetNode(PM);






                    Sup = PM;
                    PM  = (Sup + Inf)/2;
                    TmpNode = GetNode(PM);
                }
            }
        }
        //Dato i no encontrado
        return NULL;

        /*
        int Sup =  (ListSize-0);
        int Inf =  0;
        int Pm = (Sup + Inf) / 2;
        int cnt = 0;
        SimpleNode TmpNode = First;
        int Eval = Nit.compare(TmpNode.Clt->Nit);

        while(Sup >= Inf){
            if(Eval == 0){
                break;
            }

            TmpNode = TmpNode.Next;
        }

        return TmpNode;
        */
    }

    //(^< ............ ............ ............ ............ ............ Obtener nodo por Nit
    SimpleNode * GetNodeByNit(QString Nit){

        return BinarySearch(Nit);
        /*int cnt = 0;
        SimpleNode TmpNode = First;

        while(TmpNode != NULL){

            if(TmpNode.Clt->Nit == Nit){
                return TmpNode;
            }
            TmpNode = TmpNode.Next;
        }
        */
    }

    //(^< ............ ............ ............ ............ ............ Insertar en Indice Especifico
    bool InsertAt(int index,Cliente * TmpClient){

        //Inserta estando vacia la lista
        if(index == 0 && ListSize == 0){
            InsertWhenEmpty(TmpClient);
            return true;
        }

        //Inserta al frente de la lista
        if(index == 0 && ListSize > 0){
            FrontInsert(TmpClient);
            return true;
        }

        //Agrega un nuevo elemento al final de la lista
        if(index == (ListSize)){
            EndInsert(TmpClient);
            return true;
        }


        //Inserta en un punto intermedio
        if(index >= 1 && index < ListSize){

            //Linkeo
            SimpleNode * TmpNode = GetNode(index-1);
            SimpleNode * NewNode = new SimpleNode(TmpClient);


            NewNode->Next = TmpNode->Next;
            TmpNode->Next = NewNode;

            ListSize++;

            return true;

        }

        return NULL;

    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ P R O D U C T
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    /*
    //(^< ............ ............ ............ ............ ............ P U S H
    void Push_Product(Product * Prod){
        if(ListSize != 0){
            InsertAt(0,Prod);
        }
    }

    //(^< ............ ............ ............ ............ ............ P O P
    SimpleNode * Pop_Product(){
        if(ListSize != 0){
            SimpleNode * TmpNode = GetNode(0);
            DeleteNode(0);
            return TmpNode;
        }
        return NULL;

    }

    //(^< ............ ............ ............ ............ ............ Clear Stack
    void ClearStack(){
        if(ListSize > 0){
            while(ListSize > 0){
                DeleteNode(0);
            }
        }
    }

    //(^< ............ ............ ............ ............ ............ Insertar cuando la Lista este Vacia
    bool InsertWhenEmpty(Product * TmpProd){
        if(ListSize == 0){
            First = Last = new SimpleNode(TmpProd);

            ListSize ++;
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Insertar al Frente
    bool FrontInsert(Product * TmpProd){
        if(!InsertWhenEmpty(TmpProd)){
             SimpleNode * TmpNode = new SimpleNode(TmpProd);


             TmpNode->Next = First;
             First = TmpNode;
             ListSize++;
             return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Insertar al Fondo
    bool EndInsert(Product * TmpProd){
        if(!InsertWhenEmpty(TmpProd)){
            SimpleNode * TmpNode = new SimpleNode(TmpProd);

            Last->Next = TmpNode;
            Last = TmpNode;
            ListSize ++;
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ ............ ............ Insertar en Indice Especifico
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
            SimpleNode * TmpNode = GetNode(index-1);
            SimpleNode * NewNode = new SimpleNode(TmpProd);


            NewNode->Next = TmpNode->Next;
            TmpNode->Next = NewNode;

            ListSize++;

            return true;

        }

        return NULL;

    }
    */
};

#endif // SIMPLELIST_H
