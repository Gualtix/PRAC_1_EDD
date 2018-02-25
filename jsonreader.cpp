#include "jsonreader.h"
#include "time.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>


//static double TestProductsQt(DC_List *list, QByteArray json);
//static double TestProducts(QList *list, QByteArray json);

//(^< ............ ............ ............ T E S T: Productos Estudiante
double JsonReader::TestProducts(QByteArray json){

    DC_List *list = new DC_List();
    QJsonDocument doc = QJsonDocument::fromJson(json);
    if(! doc.isArray()){
        QMessageBox::warning(nullptr, "JSON Productos", "Error en el archivo, el elemento raíz debe ser un arreglo");
        return 0;
    }
    QJsonArray array = doc.array();
    int max = array.size();

    clock_t t;
    t = clock();
    for(int i = 0; i < max; i++) {
        QJsonValueRef ref = array[i];
        if(! ref.isObject())
            continue;


        QJsonObject obj = ref.toObject();

        //Codigo
        QJsonValue codeValue = obj["codigo"];
        if(codeValue.isUndefined() || codeValue.isNull())
            continue;

        //Precio
        QJsonValue priceValue = obj["precio"];
        if(priceValue.isUndefined() || priceValue.isNull())
            continue;

        //Nombre
        QJsonValue  nameValue = obj["nombre"];
        if(nameValue.isUndefined() || nameValue.isNull())
            continue;

        //Descripcion
        QJsonValue descriptionValue = obj["descripcion"];
        if(descriptionValue.isUndefined() || descriptionValue.isNull())
            continue;

        list->InsertSortedByCode(new Product(codeValue.toString(),priceValue.toString().toDouble(),0,nameValue.toString(),descriptionValue.toString()));
    }
    t = clock() - t;

    return ((double)t / CLOCKS_PER_SEC) * 1000;

    //QString resume = QString::asprintf("Se cargaron correctamente %d de %d registros en %ld ciclos de reloj.", list->size(), max, t);
    //QString resume = QString::asprintf("Se cargaron correctamente %d de %d registros en %f milisegundos.", list->ListSize, max, ((double)t / CLOCKS_PER_SEC) * 1000);
    //QMessageBox::information(NULL, "Rendimiento lista doble", resume);



}

//(^< ............ ............ ............ T E S T: Productos QT
double JsonReader::TestProductsQt(QByteArray json){

    QList<Product> *list = new QList<Product>;

    QJsonDocument doc = QJsonDocument::fromJson(json);
    if(! doc.isArray()){
        QMessageBox::warning(nullptr, "JSON Productos", "Error en el archivo, el elemento raíz debe ser un arreglo");
        return 0;
    }
    QJsonArray array = doc.array();
    int max = array.size();

    clock_t t;
    t = clock();
    for(int i = 0; i < max; i++) {
        QJsonValueRef ref = array[i];
        if(! ref.isObject())
            continue;


        QJsonObject obj = ref.toObject();

        //Codigo
        QJsonValue codeValue = obj["codigo"];
        if(codeValue.isUndefined() || codeValue.isNull())
            continue;

        //Precio
        QJsonValue priceValue = obj["precio"];
        if(priceValue.isUndefined() || priceValue.isNull())
            continue;

        //Nombre
        QJsonValue  nameValue = obj["nombre"];
        if(nameValue.isUndefined() || nameValue.isNull())
            continue;

        //Descripcion
        QJsonValue descriptionValue = obj["descripcion"];
        if(descriptionValue.isUndefined() || descriptionValue.isNull())
            continue;

        //list->InsertSortedByCode(new Product(codeValue.toString(),priceValue.toString().toDouble(),0,nameValue.toString(),descriptionValue.toString()));
        //list->append(new Product("LS",3.2,3,"Wata","EES"));
        Product * Prod = new Product(codeValue.toString(),priceValue.toString().toDouble(),0,nameValue.toString(),descriptionValue.toString());
        list->append(*Prod);
    }
    t = clock() - t;

    return  ((double)t / CLOCKS_PER_SEC) * 1000;

    //QString resume = QString::asprintf("Se cargaron correctamente %d de %d registros en %ld ciclos de reloj.", list->size(), max, t);
    //QString resume = QString::asprintf("Se cargaron correctamente %d de %d registros en %f milisegundos.", list->ListSize, max, ((double)t / CLOCKS_PER_SEC) * 1000);
    //QMessageBox::information(NULL, "Rendimiento lista doble", resume);
}






void JsonReader::fillListFromFile(DC_List *list, QByteArray json) {

    QJsonDocument doc = QJsonDocument::fromJson(json);
    if(! doc.isArray()){
        QMessageBox::warning(nullptr, "JSON Productos", "Error en el archivo, el elemento raíz debe ser un arreglo");
        return;
    }
    QJsonArray array = doc.array();
    int max = array.size();

    clock_t t;
    t = clock();
    for(int i = 0; i < max; i++) {
        QJsonValueRef ref = array[i];
        if(! ref.isObject())
            continue;


        QJsonObject obj = ref.toObject();

        //Codigo
        QJsonValue codeValue = obj["codigo"];
        if(codeValue.isUndefined() || codeValue.isNull())
            continue;

        //Precio
        QJsonValue priceValue = obj["precio"];
        if(priceValue.isUndefined() || priceValue.isNull())
            continue;

        //Nombre
        QJsonValue  nameValue = obj["nombre"];
        if(nameValue.isUndefined() || nameValue.isNull())
            continue;

        //Descripcion
        QJsonValue descriptionValue = obj["descripcion"];
        if(descriptionValue.isUndefined() || descriptionValue.isNull())
            continue;

        list->InsertSortedByCode(new Product(codeValue.toString(),priceValue.toString().toDouble(),0,nameValue.toString(),descriptionValue.toString()));
    }

    t = clock() - t;

    //QString resume = QString::asprintf("Se cargaron correctamente %d de %d registros en %ld ciclos de reloj.", list->size(), max, t);
    QString resume = QString::asprintf("Se cargaron correctamente %d de %d registros en %f milisegundos.", list->ListSize, max, ((double)t / CLOCKS_PER_SEC) * 1000);
    QMessageBox::information(NULL, "Rendimiento lista doble", resume);
}



void JsonReader::fillListFromFile(SimpleList *list,DC_List * ProdStock, QByteArray json) {

    //Contenedores Temporales
    Factu_List * FAACT = new Factu_List();
    ProductStack * PROOD = new ProductStack();

    QJsonDocument doc = QJsonDocument::fromJson(json);
    if(! doc.isArray()){
        QMessageBox::warning(nullptr, "JSON Clientes", "Error en el archivo, el elemento raíz debe ser un arreglo");
        return;
    }
    QJsonArray array = doc.array();
    int max = array.size();

    clock_t t;
    t = clock();


    for(int i = 0; i < max; i++) {

        QJsonValueRef ref = array[i];
        if(! ref.isObject())
            continue;

        QJsonObject obj = ref.toObject();

        //Nit
        QJsonValue nitValue = obj["NIT"];
        if(nitValue.isUndefined() || nitValue.isNull())
            continue;

        //Nombre
        QJsonValue nameValue = obj["nombre"];
        if(nameValue.isUndefined() || nameValue.isNull())
            continue;

        QJsonArray Facturas = obj["facturas"].toArray();
        int maxFact = Facturas.size();

        for(int j = 0; j < maxFact; j++){



            QJsonValueRef reFact = Facturas[j];
            if(! reFact.isObject())
                continue;

            QJsonObject objFact = reFact.toObject();

            //serie
            QJsonValue serieValue = objFact["serie"];
            if(serieValue.isUndefined() || serieValue.isNull())
                continue;

            //correlativo
            QJsonValue correlValue = objFact["correlativo"];
            if(correlValue.isUndefined() || correlValue.isNull())
                continue;

            //fecha
            QJsonValue fechaValue = objFact["fecha"];
            if(fechaValue.isUndefined() || fechaValue.isNull())
                continue;

            //productos
            QJsonArray Productos = objFact["productos"].toArray();
            int maxProd = Productos.size();
            for(int k = 0; k < maxProd; k++){
                QJsonValueRef reProd = Productos[k];
                if(! reProd.isObject())
                    continue;

                QJsonObject objProd = reProd.toObject();

                //codigo
                QJsonValue codeValue = objProd["codigo"];
                if(codeValue.isUndefined() || codeValue.isNull())
                    continue;

                //cantidad
                QJsonValue cantidadValue = objProd["cantidad"];
                if(cantidadValue.isUndefined() || cantidadValue.isNull())
                    continue;

                //descuento
                QJsonValue descuentoValue = objProd["descuento"];
                if(descuentoValue.isUndefined() || descuentoValue.isNull())
                    continue;

                QString Codi = codeValue.toString();
                int Cant = cantidadValue.toInt();
                double Desco = descuentoValue.toDouble();

                //Validamos la Pre-Existencia del Producto
                DoubleNode * TmpStock = ProdStock->GetNodeByCode(Codi);
                if(TmpStock != NULL){
                    //Marcamos el Producto como usado
                    TmpStock->Prod->Is_in_Use = true;
                    QString CDD = TmpStock->Prod->Code;
                    QString DESCCR = TmpStock->Prod->Description;
                    double  PRESS_UNNIT = TmpStock->Prod->Price;
                    //int     CANNT = TmpStock->Prod->Units;
                    //double  DESCCUENT = TmpStock->Prod->Descuento;
                    PROOD->Push_Product(new Detalle_Factura(CDD,DESCCR,PRESS_UNNIT,Cant,Desco));
                }
                else{
                    continue;
                }
                //PROOD->Push_Product(new Detalle_Factura(Codi,Cant,Desco));
            }

            QString Serial = serieValue.toString();
            QString Correl = correlValue.toString();
            //Verificamos la Integridad de una Factura antes de ingresarla
            if(PROOD->ListSize > 0){
                FAACT->FrontInsert(new Factura(Serial,Correl.toInt(),fechaValue.toString(),nitValue.toString(),PROOD));
                PROOD = new ProductStack();
            }
        }

        if(FAACT->ListSize > 0)
        {
            list->InsertSortedByNit(new Cliente(nitValue.toString(),nameValue.toString(),FAACT));
            FAACT = new Factu_List();
        }else{
            SimpleNode * TmpCliente = list->GetNodeByNit(nitValue.toString());
            if(TmpCliente != NULL){
                TmpCliente->Clt->Lista_de_Facturas = FAACT;
            }
            else{
                list->InsertSortedByNit(new Cliente(nitValue.toString(),nameValue.toString(),FAACT));
            }
        }
    }
    t = clock() - t;
    //QString resume = QString::asprintf("Se cargaron correctamente %d de %d registros en %ld ciclos de reloj.", list->size(), max, t);
    QString resume = QString::asprintf("Se cargaron correctamente %d de %d registros en %f milisegundos.", list->ListSize, max, ((double)t / CLOCKS_PER_SEC) * 1000);
    QMessageBox::information(NULL, "Rendimiento Lista Simple", resume);
}
