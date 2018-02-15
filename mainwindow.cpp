#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    //Deshabilitar edicion de tabla
    ui->tblProd->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Estado de los botones al cargar el Formulario
    ui->btnNew->setEnabled(true);
    ui->btnSave->setEnabled(false);
    ui->btnDelete->setEnabled(false);


    setWindowTitle("Punto de Venta MASS");
    ui->tblProd->setColumnCount(4);
    ui->tblProd->setColumnWidth(1, 420);
    QStringList Titles;
    Titles << "Codigo" << "Nombre" << "Precio" << "Existencia";
    ui->tblProd->setHorizontalHeaderLabels(Titles);

    //Inicializacion de la Lista Circular Doble
    LST_PROD = new DC_List();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//(^< ............ ............ ............ Actualizar Tabla
void MainWindow::UpdateTable(){
    if(LST_PROD->ListSize > 0){
        int cnt = 0;
        DoubleNode * TmpNode = LST_PROD->First;
        while(cnt < LST_PROD->ListSize){
            AddTableItem(cnt,TmpNode->Prod);
            TmpNode = TmpNode->Next;
            cnt++;
        }
    }
}

//(^< ............ ............ ............ Agregar Item a Tabla
void MainWindow::AddTableItem(int Rk,Product * TmpProd){

    ui->tblProd->insertRow(Rk);

    ui->tblProd->setItem(Rk,0,new QTableWidgetItem(TmpProd->Code));
    ui->tblProd->setItem(Rk,1,new QTableWidgetItem(TmpProd->Name));
    ui->tblProd->setItem(Rk,2,new QTableWidgetItem("Q "+QString::number(TmpProd->Price)));
    ui->tblProd->setItem(Rk,3,new QTableWidgetItem(QString::number(TmpProd->Units)));
}

//(^< ............ ............ ............ Eliminar Item de Tabla
void MainWindow::DeleteTableItem(){
    int index = ui->tblProd->currentItem()->row();
    ui->tblProd->removeRow(index);
    LST_PROD->DeleteNode(index);
    ui->btnDelete->setEnabled(false);
    CleanProducts();
}

//(^< ............ ............ ............ Limpiar Productos
void MainWindow::CleanProducts(){
    ui->tboxCode->setText("");
    ui->spinUnits->setValue(0);
    ui->dspinPrice->setValue(0.00);
    ui->tboxName->setText("");
    ui->tboxDescription->clear();
}

//(^< ............ ............ ............ Filtrar Campos
bool MainWindow::ValidateProductInfo(Product * TmpProd){
    if(LST_PROD->ListSize == 0){
        return true;
    }

    if(LST_PROD->ValidateUnique(TmpProd->Code)){
        return true;
    }
    else{
        return false;
    }
}

//(^< ............ ............ ............ Validar la Eliminacion de un Producto
bool MainWindow::ValidateProductDelete(){
    return true;
}

//(^< ............ ............ ............ Click: Nuevo Producto
void MainWindow::on_btnNew_clicked()
{
    QString Code = ui->tboxCode->text();
    double  Price = ui->dspinPrice->value();
    int Units = ui->spinUnits->value();
    QString Name = ui->tboxName->text();
    QString Description = ui->tboxDescription->toPlainText();

    Product * TmpProd = new Product(Code,Price,Units,Name,Description);

    if(ValidateProductInfo(TmpProd)){

        int Rk = LST_PROD->InsertSortedByCode(TmpProd);
        AddTableItem(Rk,TmpProd);

    }
    else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Productos");
        msgBox.setText("El Codigo Ingresado ya Existe");
        msgBox.exec();
    }

    ui->tboxCode->setFocus();
    CleanProducts();

}

//(^< ............ ............ ............ Click: Eliminar Producto
void MainWindow::on_btnDelete_clicked()
{
    if(ValidateProductDelete()){
        DeleteTableItem();
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Productos");
        msgBox.setText("El Producto NO Puede Eliminarse");
        msgBox.exec();
    }
}

//(^< ............ ............ ............ Click: Guardar Cambios
void MainWindow::on_btnSave_clicked()
{

    QString Code = ui->tboxCode->text();
    if(LST_PROD->ValidateUnique(Code) | TmpCode == Code){

        double  Price = ui->dspinPrice->value();
        int Units = ui->spinUnits->value();
        QString Name = ui->tboxName->text();
        QString Description = ui->tboxDescription->toPlainText();

        //Eliminamos el Nodo y la Fila
        int index = ui->tblProd->currentItem()->row();
        ui->tblProd->removeRow(index);
        LST_PROD->DeleteNode(index);

        //Insertamos un nuevo nodo con la informacion editada
        int Rk = LST_PROD->InsertSortedByCode(new Product(Code,Price,Units,Name,Description));
        AddTableItem(Rk,new Product(Code,Price,Units,Name,Description));

    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Productos");
        msgBox.setText("El Codigo Ingresado ya Existe");
        msgBox.exec();
    }

    //Restablecimiento de Botones
    ui->btnSave->setEnabled(false);
    ui->btnDelete->setEnabled(false);
    ui->btnNew->setEnabled(true);

    //Lipieza de los campos de texto
    CleanProducts();
}

//(^< ............ ............ ............ Click: Item seleccionado
void MainWindow::on_tblProd_itemDoubleClicked(QTableWidgetItem *item)
{
    //int index = ui->tblProd->currentItem()->row();
    //int index = ui->tblProd->currentItem()->text();

    TmpCode = ui->tblProd->currentItem()->text();

    QString index = TmpCode;

    ui->btnNew->setEnabled(false);
    ui->btnDelete->setEnabled(true);
    ui->btnSave->setEnabled(true);

    DoubleNode * TmpNode = LST_PROD->GetNodeByCode(index);

    if(TmpNode != NULL){
        //Llenar los campos de texto
        ui->tboxCode->setText(TmpNode->Prod->Code);
        ui->spinUnits->setValue(TmpNode->Prod->Units);
        ui->dspinPrice->setValue(TmpNode->Prod->Price);
        ui->tboxName->setText(TmpNode->Prod->Name);
        ui->tboxDescription->setPlainText(TmpNode->Prod->Description);
    }
}

//(^< ............ ............ ............ Enter: En campo buscar
void MainWindow::on_tboxSearch_returnPressed()
{
    ui->tblProd->setRowCount(0);
    ui->tboxSearch->text().trimmed();
    if(ui->tboxSearch->text() == ""){
        //Se muestran todos los productos en memoria
        ui->tblProd->setRowCount(0);
        UpdateTable();
    }
    else{

        DoubleNode * TmpNode = LST_PROD->GetNodeByCode(ui->tboxSearch->text());
        if(TmpNode != NULL){
            AddTableItem(0,TmpNode->Prod);
        }
        //No hay resultados
        else{

        }
    }
}

//(^< ............ ............ ............ Click: MenuItem IlustrarProductos
void MainWindow::on_actionProductos_3_triggered()
{
    if(!LST_PROD->ListSize == 0){
        LST_PROD->DrawList();
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Productos");
        msgBox.setText("No hay Productos que Ilustrar");
        msgBox.exec();
    }
}

//(^< ............ ............ ............ Click: Cargar JSON Productos
void MainWindow::on_actionProductos_triggered()
{

}

//(^< ............ ............ ............ Click: Cargar JSON Productos
void MainWindow::on_actionProductos_2_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("JSON de clientes"));
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray ba = file.readAll();

    //free(this->doubleCustomerList);
    //this->doubleCustomerList = NULL;
    //this->doubleCustomerList = new DoubleList();

    JsonReader::fillListFromFile(LST_PROD, ba);
    UpdateTable();
}
