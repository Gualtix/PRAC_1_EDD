#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    //Deshabilitar edicion de tabla
    ui->tblProd->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblClients->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Estado de los botones al cargar el Formulario
    ui->btnNew->setEnabled(true);
    ui->btnSave->setEnabled(false);
    ui->btnDelete->setEnabled(false);


    setWindowTitle("Punto de Venta MASS");
    //ui->tblProd->setColumnCount(4);
    ui->tblProd->setColumnWidth(1, 425);
    ui->tblClients->setColumnWidth(1,260);
    //QStringList Titles;
    //Titles << "Codigo" << "Nombre" << "Precio" << "Existencia";
    //ui->tblProd->setHorizontalHeaderLabels(Titles);

    //Inicializacion de la Lista Circular Doble
    LST_PROD = new DC_List();
    LST_CLIENT = new SimpleList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//(^< ............ ............ ............ P R O D U C T O S ............ ............ ............
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

//(^< ............ ............ ............ Actualizar Tabla
void MainWindow::UpdateTableClients(){
    if(LST_CLIENT->ListSize > 0){
        int cnt = 0;
        SimpleNode * TmpNode = LST_CLIENT->First;
        while(cnt < LST_CLIENT->ListSize){
            AddTableItemClients(cnt,TmpNode->Clt);
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

//(^< ............ ............ ............ Agregar Item a Tabla: Clientes
void MainWindow::AddTableItemClients(int Rk,Cliente * TmpClient){

    ui->tblClients->insertRow(Rk);

    ui->tblClients->setItem(Rk,0,new QTableWidgetItem(TmpClient->Nit));
    ui->tblClients->setItem(Rk,1,new QTableWidgetItem(TmpClient->Name));
    ui->tblClients->setItem(Rk,2,new QTableWidgetItem("Q "+QString::number(TmpClient->GetFactNum())));
}

//(^< ............ ............ ............ Eliminar Item de Tabla
void MainWindow::DeleteTableItem(){
    int index = ui->tblProd->currentItem()->row();
    ui->tblProd->removeRow(index);
    LST_PROD->DeleteNode(index);
    ui->btnDelete->setEnabled(false);
    CleanProducts();
}

//(^< ............ ............ ............ Eliminar Item de Tabla: Clientes
void MainWindow::DeleteTableItemClients(){
    int index = ui->tblClients->currentItem()->row();
    ui->tblClients->removeRow(index);
    LST_CLIENT->DeleteNode(index);
    ui->btnDeleteClient->setEnabled(false);
    CleanClients();
}

//(^< ............ ............ ............ Limpiar Productos
void MainWindow::CleanProducts(){
    ui->tboxCode->setText("");
    ui->spinUnits->setValue(0);
    ui->dspinPrice->setValue(0.00);
    ui->tboxName->setText("");
    ui->tboxDescription->clear();
}

//(^< ............ ............ ............ Limpiar Clientes
void MainWindow::CleanClients(){
    ui->tboxClientNit->setText("");
    ui->tboxClientName->setText("");
}

//(^< ............ ............ ............ Validar Info Producto
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

//(^< ............ ............ ............ Validar Info Cliente
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

    //Lipieza de los campos de texto
    CleanProducts();
}

//(^< ............ ............ ............ Click: Item seleccionado
void MainWindow::on_tblProd_itemDoubleClicked(QTableWidgetItem *item)
{
    //int index = ui->tblProd->currentItem()->row();
    //int index = ui->tblProd->currentItem()->text();

    SelectedCode = ui->tblProd->currentItem()->text();

    QString index = SelectedCode;

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

//(^< ............ ............ ............ Click: MenuItem Ilustrar Productos
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

//(^< ............ ............ ............ Click: Nueva Factura
void MainWindow::on_btnNuevaFactura_clicked()
{
    ui->tabGeneral->setCurrentIndex(2);
}
//(^< ............ ............ ............  C L I E N T E S ............ ............ ............

//(^< ............ ............ ............ Click: Nuevo Cliente
void MainWindow::on_btnNewClient_clicked()
{


    QString Nit = ui->tboxClientNit->text();
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

//(^< ............ ............ ............ Click: Guardar Cambios Cliente
void MainWindow::on_btnSaveClient_clicked()
{
    QString Nit = ui->tboxClientNit->text();
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


//(^< ............ ............ ............ Validar la Eliminacion de un Producto
bool MainWindow::ValidateClientDelete(){
    return true;
}

//(^< ............ ............ ............ Click: Eliminar Cliente
void MainWindow::on_btnDeleteClient_clicked()
{
    if(ValidateClientDelete()){
        DeleteTableItemClients();
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registro de Productos");
        msgBox.setText("El Producto NO Puede Eliminarse");
        msgBox.exec();
    }
}

//(^< ............ ............ ............ Click: Item seleccionado
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
    }
}

//(^< ............ ............ ............ Click: MenuItem Ilustrar Clientes
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

//(^< ............ ............ ............ Click: Cargar JSON Clientes
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

    JsonReader::fillListFromFile(LST_CLIENT, ba);
    UpdateTableClients();
}
