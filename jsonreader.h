#ifndef JSONREADER_H
#define JSONREADER_H

//#include "doublelist.h"
//#include "simplelist.h"
#include "dc_list.h"
#include "simplelist.h"
#include "QList"
#include "product.h"


class JsonReader
{
public:
    double CuentaTiempo;


    static double TestProducts(QByteArray json);
    static double TestProductsQt(QByteArray json);

    static void fillListFromFile(DC_List *list, QByteArray json);
    static void fillListFromFile(SimpleList *list,DC_List * ProdStock, QByteArray json);



};

#endif // JSONREADER_H
