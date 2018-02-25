#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "detalle_factura.h"
#include <QPrinter>
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    //Deshabilitar edicion de tabla
    ui->tblProd->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblClients->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblVistaDetFact->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblNF_Carretilla->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Estado de los botones al cargar el Formulario
    ui->btnNew->setEnabled(true);
    ui->btnSave->setEnabled(false);
    ui->btnDelete->setEnabled(false);

    ui->btnNewClient->setEnabled(true);
    ui->btnSaveClient->setEnabled(false);
    ui->btnDeleteClient->setEnabled(false);

    ui->btnPDF->setEnabled(false);
    ui->btnDeleteFact->setEnabled(false);

    setWindowTitle("Punto de Venta MASS");
    //ui->tblProd->setColumnCount(4);
    ui->tblProd->setColumnWidth(1, 425);
    ui->tblClients->setColumnWidth(1,260);
    ui->tblNF_Carretilla->setColumnWidth(1,325);
    ui->tblVistaDetFact->setColumnWidth(1,325);

    ui->spinCanti->setMinimum(1);
    ui->spinCanti->setValue(1);

    ui->dspinNF_Descuento->setMaximum(100);

    //Bloqueo de Controles

    ui->tboxDF_Nit->setReadOnly(true);
    ui->tboxDF_Nombre->setReadOnly(true);
    ui->tboxDF_Serie->setReadOnly(true);
    ui->tboxDF_Correlativo->setReadOnly(true);
    ui->tboxDF_Fecha->setReadOnly(true);
    ui->tboxDF_Total->setReadOnly(true);

    ui->tboxNF_Fecha->setReadOnly(true);
    ui->tboxNF_Correlativo->setReadOnly(true);
    ui->tboxNF_Serie->setReadOnly(true);
    ui->tboxNF_Total->setReadOnly(true);
    ui->tboxNF_Nombre->setReadOnly(true);

    //QStringList Titles;
    //Titles << "Codigo" << "Nombre" << "Precio" << "Existencia";
    //ui->tblProd->setHorizontalHeaderLabels(Titles);

    //Inicializacion de la Lista Circular Doble
    LST_PROD = new DC_List();
    LST_CLIENT = new SimpleList();
    DetFactu_Stack = new ProductStack();

    Cliente * TmpClient = new Cliente("C/F","Consumidor Final");
    LST_CLIENT->InsertSortedByNit(TmpClient);

    //Acutalizar Tabla Clientes
    ui->tblClients->setRowCount(0);
    UpdateTableClients();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ P R O D U C T O S
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

//(^< ............ ............ ............ ............ ............ Actualizar Tabla
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

//(^< ............ ............ ............ ............ ............ Agregar Item a Tabla
void MainWindow::AddTableItem(int Rk,Product * TmpProd){

    ui->tblProd->insertRow(Rk);

    ui->tblProd->setItem(Rk,0,new QTableWidgetItem(TmpProd->Code));
    ui->tblProd->setItem(Rk,1,new QTableWidgetItem(TmpProd->Name));
    ui->tblProd->setItem(Rk,2,new QTableWidgetItem("Q "+QString::number(TmpProd->Price)));
    ui->tblProd->setItem(Rk,3,new QTableWidgetItem(QString::number(TmpProd->Units)));
}

//(^< ............ ............ ............ ............ ............ Eliminar Item de Tabla
void MainWindow::DeleteTableItem(){
    int index = ui->tblProd->currentItem()->row();
    ui->tblProd->removeRow(index);
    LST_PROD->DeleteNode(index);

    ui->btnNew->setEnabled(true);
    ui->btnDelete->setEnabled(false);
    ui->btnSave->setEnabled(false);
    ui->btntoChar->setEnabled(false);

    CleanProducts();
}

//(^< ............ ............ ............ ............ ............ Limpiar Productos
void MainWindow::CleanProducts(){
    ui->tboxCode->setText("");
    ui->spinUnits->setValue(0);
    ui->dspinPrice->setValue(0.00);
    ui->tboxName->setText("");
    ui->tboxDescription->clear();
}

//(^< ............ ............ ............ ............ ............ Validar Info Producto
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

//(^< ............ ............ ............ ............ ............ Validar la Eliminacion de un Producto
bool MainWindow::ValidateProductDelete(){

    QString index = ui->tblProd->currentItem()->text();
    if(LST_PROD->GetNodeByCode(index)->Prod->Is_in_Use){
        return false;
    }
    return true;
}


//(^< ............ ............ ............ ............ ............ Click: Nuevo Producto
void MainWindow::on_btnNew_clicked()
{
    QString Code = ui->tboxCode->text();


    Code.trimmed();
    if(Code == ""){
        return;
    }

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

//(^< ............ ............ ............ ............ ............ Click: Eliminar Producto
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

//(^< ............ ............ ............ ............ ............ Click: Guardar Cambios
void MainWindow::on_btnSave_clicked()
{

    QString Code = ui->tboxCode->text();
    if(LST_PROD->ValidateUnique(Code) | SelectedCode == Code){

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
    ui->btntoChar->setEnabled(false);

    //Lipieza de los campos de texto
    CleanProducts();
}

//(^< ............ ............ ............ ............ ............ Click: Item seleccionado
void MainWindow::on_tblProd_itemDoubleClicked(QTableWidgetItem *item)
{
    //int index = ui->tblProd->currentItem()->row();
    //int index = ui->tblProd->currentItem()->text();

    SelectedCode = ui->tblProd->currentItem()->text();

    QString index = SelectedCode;

    ui->btnNew->setEnabled(false);
    ui->btnDelete->setEnabled(true);
    ui->btnSave->setEnabled(true);
    ui->btntoChar->setEnabled(true);


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

//(^< ............ ............ ............ ............ ............ Enter: En campo buscar
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

//(^< ............ ............ ............ ............ ............ Click: MenuItem Ilustrar Productos
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

//(^< ............ ............ ............ ............ ............ Click: Cargar JSON Productos
void MainWindow::on_actionCargar_Productos_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("JSON PRODUCTOS"));
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray ba = file.readAll();

    JsonReader::fillListFromFile(LST_PROD, ba);
    UpdateTable();
}

//(^< ............ ............ ............ ............ ............ Click: Nueva Factura
void MainWindow::on_btnNuevaFactura_clicked()
{
    ui->tabGeneral->setCurrentIndex(2);
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ C L I E N T E S
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

//(^< ............ ............ ............ ............ ............ Actualizar Tabla
void MainWindow::UpdateTableClients(){
    if(LST_CLIENT->ListSize > 0){
        int cnt = 0;
        ui->tblClients->setRowCount(0);
        SimpleNode * TmpNode = LST_CLIENT->First;
        while(cnt < LST_CLIENT->ListSize){
            AddTableItemClients(cnt,TmpNode->Clt);
            TmpNode = TmpNode->Next;
            cnt++;
        }
    }
}

//(^< ............ ............ ............ ............ ............ Agregar Item a Tabla: Clientes
void MainWindow::AddTableItemClients(int Rk,Cliente * TmpClient){

    ui->tblClients->insertRow(Rk);

    ui->tblClients->setItem(Rk,0,new QTableWidgetItem(TmpClient->Nit));
    ui->tblClients->setItem(Rk,1,new QTableWidgetItem(TmpClient->Name));
    ui->tblClients->setItem(Rk,2,new QTableWidgetItem(QString::number(TmpClient->Lista_de_Facturas->ListSize)));
}

//(^< ............ ............ ............ ............ ............ Limpiar Clientes
void MainWindow::CleanClients(){
    ui->tboxClientNit->setText("");
    ui->tboxClientName->setText("");
}

//(^< ............ ............ ............ ............ ............ Click: Nuevo Cliente
void MainWindow::on_btnNewClient_clicked()
{
    QString Nit = ui->tboxClientNit->text();
    Nit.trimmed();
    if(Nit == ""){
        return;
    }


    //QString Nit = ui->tboxClientNit->text();
    //double  Price = ui->dspinPrice->value();
    //int Units = ui->spinUnits->value();
    QString Name = ui->tboxClientName->text();
    //QString Description = ui->tboxDescription->toPlainText();

    Cliente * TmpClient = new Cliente(Nit,Name);

    //if(ValidateClientInfo(TmpClient)){
    int Rk = LST_CLIENT->InsertSortedByNit(TmpClient);
    if(Rk != -100){
        AddTableItemClients(Rk,TmpClient);

    }
    else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Clientes");
        msgBox.setText("El Nit Ingresado ya Existe");
        msgBox.exec();
    }

    ui->tboxClientNit->setFocus();
    CleanClients();
}

//(^< ............ ............ ............ ............ ............ Click: Guardar Cambios Cliente
void MainWindow::on_btnSaveClient_clicked()
{
    QString Nit = ui->tboxClientNit->text();
    Nit.trimmed();
    if(Nit == ""){
        return;
    }
    if(Nit == "C/F"){
        //Restablecimiento de Botones
        ui->btnSaveClient->setEnabled(false);
        ui->btnDeleteClient->setEnabled(false);
        ui->btnNewClient->setEnabled(true);

        //Lipieza de los campos de texto
        CleanClients();

        return;
    }
    if(LST_CLIENT->ValidateUnique(Nit) | SelectedNit == Nit){

        //double  Price = ui->dspinPrice->value();
        //int Units = ui->spinUnits->value();
        QString Name = ui->tboxClientName->text();
        //QString Description = ui->tboxDescription->toPlainText();

        //Eliminamos el Nodo y la Fila
        int index = ui->tblClients->currentItem()->row();
        ui->tblClients->removeRow(index);
        LST_CLIENT->DeleteNode(index);

        //Insertamos un nuevo nodo con la informacion editada
        int Rk = LST_CLIENT->InsertSortedByNit(new Cliente(Nit,Name));
        AddTableItemClients(Rk,new Cliente(Nit,Name));

    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Clientes");
        msgBox.setText("El Nit Ingresado ya Existe");
        msgBox.exec();
    }

    //Restablecimiento de Botones
    ui->btnSaveClient->setEnabled(false);
    ui->btnDeleteClient->setEnabled(false);
    ui->btnNewClient->setEnabled(true);

    //Lipieza de los campos de texto
    CleanClients();
}

//(^< ............ ............ ............ ............ ............ Eliminar Item de Tabla: Clientes
void MainWindow::DeleteTableItemClients(){
    int index = ui->tblClients->currentItem()->row();
    ui->tblClients->removeRow(index);
    LST_CLIENT->DeleteNode(index);
    ui->btnDeleteClient->setEnabled(false);
    CleanClients();
}

//(^< ............ ............ ............ ............ ............ Validar la Eliminacion de un Producto
bool MainWindow::ValidateClientDelete(){
    return true;
}

//(^< ............ ............ ............ ............ ............ Validar Info Cliente
bool MainWindow::ValidateClientInfo(Cliente * TmpClient){
    if(LST_CLIENT->ListSize == 0){
        return true;
    }

    if(LST_CLIENT->ValidateUnique(TmpClient->Nit)){
        return true;
    }
    else{
        return false;
    }
}

//(^< ............ ............ ............ ............ ............ Click: Eliminar Cliente
void MainWindow::on_btnDeleteClient_clicked()
{

    if(SelectedNit == "C/F"){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Clientes");
        msgBox.setText("Consumidor Final: C/F NO puede Eliminarse");
        msgBox.exec();
        return;
    }

    if(ValidateClientDelete()){
        DeleteTableItemClients();
        ui->btnNewClient->setEnabled(true);
        ui->btnSaveClient->setEnabled(false);
        ui->btnDeleteClient->setEnabled(false);
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Productos");
        msgBox.setText("El Producto NO Puede Eliminarse");
        msgBox.exec();
    }
}

//(^< ............ ............ ............ ............ ............ Click: Item seleccionado
void MainWindow::on_tblClients_itemDoubleClicked(QTableWidgetItem *item)
{
    SelectedNit = ui->tblClients->currentItem()->text();

    QString index = SelectedNit;

    ui->btnNewClient->setEnabled(false);
    ui->btnDeleteClient->setEnabled(true);
    ui->btnSaveClient->setEnabled(true);

    SimpleNode * TmpNode = LST_CLIENT->GetNodeByNit(index);

    if(TmpNode != NULL){
        //Llenar los campos de texto
        ui->tboxClientNit->setText(TmpNode->Clt->Nit);
        ui->tboxClientName->setText(TmpNode->Clt->Name);

        //Llenar las Facturas Asociadas
        ui->listboxFacturas->clear();

        if(TmpNode->Clt->Lista_de_Facturas->ListSize > 0){
            int cnt = 0;
            //Factu_List TmpFt = TmpNode->Clt->Lista_de_Facturas;
            while(cnt < TmpNode->Clt->Lista_de_Facturas->ListSize){
                QString Ser = TmpNode->Clt->Lista_de_Facturas->GetNode(cnt)->Fct->Serial;
                QString Cor = QString::number(TmpNode->Clt->Lista_de_Facturas->GetNode(cnt)->Fct->Correlative);
                ui->listboxFacturas->addItem("Serie: "+Ser+" Correlativo: "+Cor);
                cnt++;
            }
        }
    }
}

//(^< ............ ............ ............ ............ ............ Click: MenuItem Ilustrar Clientes
void MainWindow::on_actionClientes_3_triggered()
{
    if(!LST_CLIENT->ListSize == 0){
        LST_CLIENT->DrawList();
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Clientes");
        msgBox.setText("No hay Clientes que Ilustrar");
        msgBox.exec();
    }
}

//(^< ............ ............ ............ ............ ............ Click: Cargar JSON Clientes
void MainWindow::on_actionClientes_2_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("JSON CLIENTES"));
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray ba = file.readAll();

    //free(this->doubleCustomerList);
    //this->doubleCustomerList = NULL;
    //this->doubleCustomerList = new DoubleList();

    JsonReader::fillListFromFile(LST_CLIENT,LST_PROD,ba);
    UpdateTableClients();
}

//(^< ............ ............ ............ ............ ............ Buscar Cliente
void MainWindow::on_tboxSearchClient_returnPressed()
{
    ui->tblClients->setRowCount(0);
    //ui->tblClients->clear();
    ui->tboxSearchClient->text().trimmed();
    if(ui->tboxSearchClient->text() == "" && LST_CLIENT->ListSize > 0){
        //Se muestran todos los productos en memoria
        ui->tblClients->setRowCount(0);
        //ui->tblClients->clear();
        UpdateTableClients();
    }
    else{

        SimpleNode * TmpNode = LST_CLIENT->GetNodeByNit(ui->tboxSearchClient->text());
        if(TmpNode != NULL){
            AddTableItemClients(0,TmpNode->Clt);
        }
        //No hay resultados
        else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Registro de Clientes");
            if(LST_CLIENT->ListSize > 0){
                msgBox.setText("El Nit ingresado no esta Registrado");
            }
            else{
                msgBox.setText("No hay Clientes Registrados");
            }
            msgBox.exec();
        }
    }
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ T E S T
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

//(^< ............ ............ ............ ............ ............ Test: 100
void MainWindow::on_btn100_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("T E S T   1 0 0   P R O D U C T O S"));
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray ba = file.readAll();

    double CuentaTiempo_0 = JsonReader::TestProducts(ba);
    ui->tbox100Est->setText(QString::number(CuentaTiempo_0)+" Milisegundos");

    double CuentaTiempo_1 = JsonReader::TestProductsQt(ba);
    ui->tbox100Qt->setText(QString::number(CuentaTiempo_1)+" Milisegundos");
}

//(^< ............ ............ ............ ............ ............ Test: 1K
void MainWindow::on_btn1k_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("T E S T   1 K   P R O D U C T O S"));
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray ba = file.readAll();

    double CuentaTiempo_0 = JsonReader::TestProducts(ba);
    ui->tbox1kEst->setText(QString::number(CuentaTiempo_0)+" Milisegundos");

    double CuentaTiempo_1 = JsonReader::TestProductsQt(ba);
    ui->tbox1kQt->setText(QString::number(CuentaTiempo_1)+" Milisegundos");
}

//(^< ............ ............ ............ ............ ............ Test: 10K
void MainWindow::on_btn10k_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("T E S T   1 0 K   P R O D U C T O S"));
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray ba = file.readAll();

    double CuentaTiempo_0 = JsonReader::TestProducts(ba);
    ui->tbox10kEst->setText(QString::number(CuentaTiempo_0)+" Milisegundos");

    double CuentaTiempo_1 = JsonReader::TestProductsQt(ba);
    ui->tbox10kQt->setText(QString::number(CuentaTiempo_1)+" Milisegundos");

}

//(^< ............ ............ ............ ............ ............ Test: 100K
void MainWindow::on_btn100k_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("T E S T   1 0 0 K   P R O D U C T O S"));
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray ba = file.readAll();

    double CuentaTiempo_0 = JsonReader::TestProducts(ba);
    ui->tbox100kEst->setText(QString::number(CuentaTiempo_0)+" Milisegundos");

    double CuentaTiempo_1 = JsonReader::TestProductsQt(ba);
    ui->tbox100kQt->setText(QString::number(CuentaTiempo_1)+" Milisegundos");

}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ N U E V A   F A C T U R A
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

//(^< ............ ............ ............ ............ ............ Buscar Cliente
void MainWindow::on_tboxNF_Nit_returnPressed()
{
    if(LST_CLIENT->ListSize > 0){
        SimpleNode * TmpClient = LST_CLIENT->GetNodeByNit(ui->tboxNF_Nit->text());
        if(TmpClient != NULL){
            ui->tboxNF_Nombre->setText(TmpClient->Clt->Name);
            SelectedNit = TmpClient->Clt->Nit;
        }
        else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Registro de Facturas");
            msgBox.setText("El Nit ingresado no esta Registrado, se asignara C/F");
            msgBox.exec();
            ui->tboxNF_Nit->setText("C/F");
            ui->tboxNF_Nombre->setText("Consumidor Final");
            SelectedNit = "C/F";
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Facturas");
        msgBox.setText("No hay Clientes Registrados, se asignara C/F");
        msgBox.exec();
        ui->tboxNF_Nit->setText("C/F");
        ui->tboxNF_Nombre->setText("Consumidor Final");

    }
    ui->tboxNF_Serie->setText("MASS-USAC");
    ui->tboxNF_Fecha->setText(QDate::currentDate().toString("dd/MM/yy"));
    ui->tboxNF_Correlativo->setText(QString::number(Fact_Correl));

}


//(^< ............ ............ ............ ............ ............ Agregar Item a Tabla: Carretilla
void MainWindow::AddTableItemCarretilla(int Rk,Detalle_Factura * TmpDetalle){

    ui->tblNF_Carretilla->insertRow(Rk);

    ui->tblNF_Carretilla->setItem(Rk,0,new QTableWidgetItem(TmpDetalle->Codigo));
    ui->tblNF_Carretilla->setItem(Rk,1,new QTableWidgetItem(TmpDetalle->Descipcion));
    ui->tblNF_Carretilla->setItem(Rk,2,new QTableWidgetItem(QString::number(TmpDetalle->Cantidad)));
    ui->tblNF_Carretilla->setItem(Rk,3,new QTableWidgetItem(QString::number(TmpDetalle->Descuento)));
    ui->tblNF_Carretilla->setItem(Rk,4,new QTableWidgetItem("Q "+QString::number(TmpDetalle->Subtotal)));
}

//(^< ............ ............ ............ ............ ............ Agregar Item a Tabla: Carretilla
void MainWindow::AddTableItemCarretilla_Vista(int Rk,Detalle_Factura * TmpDetalle){

    ui->tblVistaDetFact->insertRow(Rk);

    ui->tblVistaDetFact->setItem(Rk,0,new QTableWidgetItem(TmpDetalle->Codigo));
    ui->tblVistaDetFact->setItem(Rk,1,new QTableWidgetItem(TmpDetalle->Descipcion));
    ui->tblVistaDetFact->setItem(Rk,2,new QTableWidgetItem(QString::number(TmpDetalle->Cantidad)));
    ui->tblVistaDetFact->setItem(Rk,3,new QTableWidgetItem(QString::number(TmpDetalle->Descuento)));
    ui->tblVistaDetFact->setItem(Rk,4,new QTableWidgetItem("Q "+QString::number(TmpDetalle->Subtotal)));
}



//(^< ............ ............ ............ ............ ............ Agregar a Carretilla
void MainWindow::on_tboxNF_Agregar_returnPressed()
{
    if(LST_PROD->ListSize > 0){
        DoubleNode * TmpProd = LST_PROD->GetNodeByCode(ui->tboxNF_Agregar->text());
        if(TmpProd != NULL){
            QString Code = TmpProd->Prod->Code;
            QString Description = TmpProd->Prod->Name;
            double  Unit_Price = TmpProd->Prod->Price;
            int Quantity = ui->spinCanti->value();
            double Discount = (ui->dspinNF_Descuento->value()/100);

            Detalle_Factura * DetFact = new Detalle_Factura(Code,Description,Unit_Price,Quantity,Discount);
            //DetFact->CalcularSubtotal();
            //Agregar Items a una Pila Temporal
            DetFactu_Stack->Push_Product(DetFact);
            AddTableItemCarretilla(0,DetFact);
            ui->tboxNF_Total->setText(QString::number(DetFactu_Stack->Total_esta_Factura));
        }
        else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Registro de Facturas");
            msgBox.setText("El Codigo de Producto no Existe, no puede Agregar a la Carretilla");
            msgBox.exec();
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Facturas");
        msgBox.setText("No hay Productos Registrados, no puede Agregar a la Carretilla");
        msgBox.exec();
    }
    ui->tboxNF_Agregar->setText("");
    ui->tboxNF_Agregar->setFocus();
}

//(^< ............ ............ ............ ............ ............ Eliminar de la Carretilla
void MainWindow::on_btnNF_Eliminar_clicked()
{
    if(DetFactu_Stack->ListSize > 0){
        ui->tblNF_Carretilla->removeRow(0);
        DetFactu_Stack->Pop_Product();
        ui->tboxNF_Total->setText(QString::number(DetFactu_Stack->Total_esta_Factura));
    }
}

//(^< ............ ............ ............ ............ ............ Vaciar Pila
void MainWindow::on_btnNF_Vaciar_clicked()
{
    if(DetFactu_Stack->ListSize > 0){
        ui->tblNF_Carretilla->setRowCount(0);
        DetFactu_Stack->ClearStack();
        ui->tboxNF_Total->setText(QString::number(DetFactu_Stack->Total_esta_Factura));
    }
}

//(^< ............ ............ ............ ............ ............ Registrar Factura
void MainWindow::on_btnNF_Registrar_clicked()
{
    //Verificamos si el Nit es Valido
    if(ui->tboxNF_Nit->text().trimmed() == ""){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Facturas");
        msgBox.setText("El Nit ingresado no esta Registrado, se asignara C/F");
        msgBox.exec();
        ui->tboxNF_Nit->setText("C/F");
        ui->tboxNF_Nombre->setText("Consumidor Final");
        SelectedNit = "C/F";
        ui->tboxNF_Serie->setText("MASS-USAC");
        ui->tboxNF_Fecha->setText(QDate::currentDate().toString("dd/MM/yy"));
        ui->tboxNF_Correlativo->setText(QString::number(Fact_Correl));
    }

    if(DetFactu_Stack->ListSize == 0){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Facturas");
        msgBox.setText("La Factura no tiene productos que registrar");
        msgBox.exec();
        return;
    }


    if(DetFactu_Stack->ListSize > 0){
        Factura * TmpFactura = new Factura();
        TmpFactura->Nit = ui->tboxNF_Nit->text();
        TmpFactura->Serial = ui->tboxNF_Serie->text();
        TmpFactura->Correlative = Fact_Correl;
        TmpFactura->Total = DetFactu_Stack->Total_esta_Factura;
        TmpFactura->Prods_Stack = DetFactu_Stack;

        TmpFactura->Prods_Stack = DetFactu_Stack;

        LST_CLIENT->GetNodeByNit(SelectedNit)->Clt->Lista_de_Facturas->FrontInsert(TmpFactura);

        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Facturas");
        msgBox.setText("Factura Registrada con Exito");
        msgBox.exec();

        //Limpiamos variables Glovales
        Fact_Correl++;
        Clean_NuevaFactura();
    }
}

//(^< ............ ............ ............ ............ ............ Limpiar Nueva Factura
void MainWindow::Clean_NuevaFactura(){

    ui->tboxNF_Agregar->setText("");
    ui->tboxNF_Correlativo->setText("");
    ui->tboxNF_Fecha->setText("");
    ui->tboxNF_Nit->setText("");
    ui->tboxNF_Nombre->setText("");
    ui->tboxNF_Nit->setText("");
    ui->tboxNF_Serie->setText("");

    ui->tblNF_Carretilla->setRowCount(0);
    SelectedNit = "";
    DetFactu_Stack = new ProductStack();
    ui->tboxNF_Total->setText(QString::number(DetFactu_Stack->Total_esta_Factura));
}

//(^< ............ ............ ............ ............ ............ Doble Click Factura
void MainWindow::on_listboxFacturas_itemDoubleClicked(QListWidgetItem *item)
{
    //Factura Seleccionada
    int Fact_ID = ui->listboxFacturas->currentRow();
    FCT_IDENT = Fact_ID;
    ui->tabGeneral->setCurrentIndex(2);

    ui->tblVistaDetFact->setRowCount(0);

    //Llenamos la Factura
    Factura * TmpFact = LST_CLIENT->GetNodeByNit(SelectedNit)->Clt->Lista_de_Facturas->GetNode(Fact_ID)->Fct;
    ui->tboxDF_Serie->setText(TmpFact->Serial);
    ui->tboxDF_Correlativo->setText(QString::number(TmpFact->Correlative));
    ui->tboxDF_Total->setText(QString::number(TmpFact->Prods_Stack->Total_esta_Factura));
    ui->tboxDF_Fecha->setText(TmpFact->Date);

    ui->tboxDF_Nit->setText(TmpFact->Nit);
    ui->tboxDF_Nombre->setText(ui->tboxClientName->text());

    ui->btnPDF->setEnabled(true);
    ui->btnDeleteFact->setEnabled(true);


    //Agregado de Items
    int cnt = 0;
    while(cnt < TmpFact->Prods_Stack->ListSize){


        //DoubleNode * TmpProd = LST_PROD->GetNodeByCode(ui->tboxNF_Agregar->text());
        //if(TmpProd != NULL){
            QString Code = TmpFact->Prods_Stack->GetNode(cnt)->Det_Fact->Codigo;
            QString Description = TmpFact->Prods_Stack->GetNode(cnt)->Det_Fact->Descipcion;
            double  Unit_Price = TmpFact->Prods_Stack->GetNode(cnt)->Det_Fact->Precio_Unitario;
            int Quantity = TmpFact->Prods_Stack->GetNode(cnt)->Det_Fact->Cantidad;
            double Discount = TmpFact->Prods_Stack->GetNode(cnt)->Det_Fact->Descuento;

            Detalle_Factura * DetFact = new Detalle_Factura(Code,Description,Unit_Price,Quantity,Discount);
            AddTableItemCarretilla_Vista(0,DetFact);
            cnt++;
        //}

    }
}



//(^< ............ ............ ............ ............ ............ Actualizar Clientes al cambiar Tab
void MainWindow::on_tabGeneral_tabBarClicked(int index)
{
    if(index == 1){
        ui->tblClients->setRowCount(0);
        UpdateTableClients();
    }
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ P D F
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

//(^< ............ ............ ............ ............ ............ Exportar Factura a PDF
void MainWindow::on_btnPDF_clicked()
{
    //Encabezado del Archivo
    QString Pdf_Report("FE-");
    Pdf_Report.append("Serie");
    Pdf_Report.append("-");
    Pdf_Report.append("Correlativo");
    Pdf_Report.append(".pdf");



    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(Pdf_Report);
    QPainter painter;
    if (! painter.begin(&printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
    return;
    }

    //------------ Escritura del PDF
    //Factura Seleccionada
    int Fact_ID = ui->listboxFacturas->currentRow();

    //Llenamos la Factura
    Factura * TmpFact = LST_CLIENT->GetNodeByNit(SelectedNit)->Clt->Lista_de_Facturas->GetNode(Fact_ID)->Fct;

    QString FSerie = TmpFact->Serial;
    QString FCorrelativo = QString::number(TmpFact->Correlative);
    QString FNombre = LST_CLIENT->GetNodeByNit(TmpFact->Nit)->Clt->Name;
    QString FNit = TmpFact->Nit;
    QString FFecha = TmpFact->Date;

    painter.drawText(100,75,"------------ ------------ ------------ ------------ F A C T U R A   E L E C T R O N I C A ------------ ------------ ------------ ------------");


    painter.drawText(150,100,"Serie:");
    painter.drawText(185,100,FSerie);

    painter.drawText(350,100,"Correlativo:");

    painter.drawText(420,100,FCorrelativo);

    painter.drawText(530,100,"Fecha:");
    painter.drawText(575,100,FFecha);

    painter.drawText(150,125,"Nit:");
    painter.drawText(175,125,FNit);

    painter.drawText(350,125,"Nombre:");
    painter.drawText(405,125,FNombre);


    painter.drawText(100,150,"------------ ------------ ------------ ------------    D E T A L L E   D E   C O M P R A    ------------ ------------ ------------ ------------");

    painter.drawText(100,175,"|   Codigo   |                              Descripcion                              |     Cantidad     |   Descuento   |     Subtotal     |");

    StackNode * ARM;
    int Ult = 0;
    for(int i = 0; i < TmpFact->Prods_Stack->ListSize; i++){
        ARM = TmpFact->Prods_Stack->GetNode(i);
        painter.drawText(105,200+(25*i),ARM->Det_Fact->Codigo);
        painter.drawText(180,200+(25*i),ARM->Det_Fact->Descipcion);
        painter.drawText(450,200+(25*i),QString::number(ARM->Det_Fact->Cantidad));
        painter.drawText(550,200+(25*i),QString::number(ARM->Det_Fact->Descuento));
        painter.drawText(610,200+(25*i),"Q "+QString::number(ARM->Det_Fact->Subtotal));
        Ult = i;
    }
    Ult++;
    painter.drawText(100,200+(25*Ult),"------------ ------------ ------------ ------------ ------------ ------------ ------------ ------------ ------------ ------------ ------------ ------------");
    Ult++;
    painter.drawText(530,200+(25*Ult),"T O T A L:");
    painter.drawText(590,200+(25*Ult),"Q "+QString::number(TmpFact->Prods_Stack->Total_esta_Factura));

    painter.end();

    QString cmd("xdg-open ");
    cmd.append(Pdf_Report);
    qDebug() << cmd;
    system(cmd.toLatin1().data());

}

//(^< ............ ............ ............ ............ ............ Eliminar Factura
void MainWindow::on_btnDeleteFact_clicked()
{
    Eliminar_Registro_FC(FCT_IDENT);
}

//(^< ............ ............ ............ ............ ............ Procedimiento de Eliminar Factura
void MainWindow::Eliminar_Registro_FC(int Fact_ID){

    if(ui->tboxDF_Nit->text() != "C/F"){
        SimpleNode * TmpCliente = LST_CLIENT->GetNodeByNit(ui->tboxDF_Nit->text());


        Factura * TmpFactura = TmpCliente->Clt->Lista_de_Facturas->GetNode(Fact_ID)->Fct;
        if(TmpFactura != NULL){

            TmpFactura->Nit = "C/F";

            Factura * NFAC = new Factura(TmpFactura->Serial,TmpFactura->Correlative,TmpFactura->Date,TmpFactura->Nit,TmpFactura->Prods_Stack);

            LST_CLIENT->GetNodeByNit("C/F")->Clt->Lista_de_Facturas->FrontInsert(NFAC);
            TmpCliente->Clt->Lista_de_Facturas->DeleteNode(Fact_ID);

            ui->tboxDF_Correlativo->setText("");
            ui->tboxDF_Serie->setText("");
            ui->tboxDF_Fecha->setText("");
            ui->tboxDF_Total->setText("");
            ui->tboxDF_Nit->setText("");
            ui->tboxDF_Nombre->setText("");

            ui->tblVistaDetFact->setRowCount(0);
            ui->btnEliminarFactura->setEnabled(false);
            ui->btnDeleteFact->setEnabled(false);
            ui->btnPDF->setEnabled(false);

            //ui->tabGeneral->setCurrentIndex(1);

            FCT_IDENT = -100;

            QMessageBox msgBox;
            msgBox.setWindowTitle("Registro de Facturas");
            msgBox.setText("Factura Eliminada del Registro del Cliente, Asignada a: C/F");
            msgBox.exec();

            //MainWindow::on_tabGeneral_tabBarClicked(1);

        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Facturas");
        msgBox.setText("No es Posible Eliminar una Factura del Registro C/F");
        msgBox.exec();

    }
}



//(^< ............ ............ ............ ............ ............ Exportar Producto a Factura
void MainWindow::on_btntoChar_clicked()
{
    ui->tboxNF_Agregar->setText(ui->tboxCode->text());
    ui->tabGeneral->setCurrentIndex(3);
    MainWindow::on_tboxNF_Agregar_returnPressed();
}
