#include "jsonreader.h"
#include "time.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

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

void JsonReader::fillListFromFile(SimpleList *list, QByteArray json) {
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

        //Codigo
        QJsonValue nitValue = obj["NIT"];
        if(nitValue.isUndefined() || nitValue.isNull())
            continue;

        //Precio
        QJsonValue nameValue = obj["nombre"];
        if(nameValue.isUndefined() || nameValue.isNull())
            continue;

        /*
        //Nombre
        QJsonValue  nameValue = obj["nombre"];
        if(nameValue.isUndefined() || nameValue.isNull())
            continue;

        //Descripcion
        QJsonValue descriptionValue = obj["descripcion"];
        if(descriptionValue.isUndefined() || descriptionValue.isNull())C
            continue;
        */

        list->InsertSortedByNit(new Cliente(nitValue.toString(),nameValue.toString()));
    }
    t = clock() - t;
    //QString resume = QString::asprintf("Se cargaron correctamente %d de %d registros en %ld ciclos de reloj.", list->size(), max, t);
    QString resume = QString::asprintf("Se cargaron correctamente %d de %d registros en %f milisegundos.", list->ListSize, max, ((double)t / CLOCKS_PER_SEC) * 1000);
    QMessageBox::information(NULL, "Rendimiento Lista Simple", resume);
}
