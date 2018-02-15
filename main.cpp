#include "mainwindow.h"
#include <QApplication>
#include "dc_list.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DC_List * P = new DC_List();
    DoubleNode * S;

    /*

    P->InsertSortedByCode(new Product("7777",10.50,"Glaseado","Aplicado a Pasteles"));
    P->InsertSortedByCode(new Product("2222",20.25,"Chocolate","Panes"));
    P->InsertSortedByCode(new Product("3333",30.25,"Refresco","Postre"));
    P->InsertSortedByCode(new Product("1111",30.25,"Refresco","Postre"));
    P->InsertSortedByCode(new Product("0000",30.25,"Refresco","Postre"));
    P->InsertSortedByCode(new Product("5555",30.25,"Refresco","Postre"));
    P->InsertSortedByCode(new Product("9999",30.25,"Refresco","Postre"));

    P->InsertAt(2,new Product("5555",10.50,"Banano","Aplicado a Pasteles"));

    P->DeleteNode(0);
    P->DeleteNode(0);
    P->DeleteNode(0);
    P->DeleteNode(0);

    P->InsertAt(0,new Product("5555",10.50,"Banano","Aplicado a Pasteles"));

    S=P->GetNode(3);
    S=P->GetNode(2);
    S=P->GetNode(1);
    S=P->GetNode(0);
    */


    //LISTO :D pero mira
    return a.exec();
}
