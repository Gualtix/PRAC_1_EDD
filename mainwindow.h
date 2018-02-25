#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dc_list.h"
#include "simplelist.h"
#include <QTableWidgetItem>
#include "QString"
#include "jsonreader.h"
#include <QFile>
#include <QFileDialog>
#include "QDate"
#include "QListWidgetItem"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_btnNew_clicked();

    void CleanProducts();
    void CleanClients();

    void UpdateTable();
    void UpdateTableClients();

    bool ValidateProductInfo(Product * TmpProd);
    bool ValidateClientInfo(Cliente * TmpClient);

    void AddTableItem(int Rk,Product * TmpProd);
    void AddTableItemClients(int Rk,Cliente * TmpClient);

    void DeleteTableItem();
    void DeleteTableItemClients();

    void on_btnDelete_clicked();

    void on_tblProd_itemDoubleClicked(QTableWidgetItem *item);

    bool ValidateProductDelete();
    bool ValidateClientDelete();

    void on_btnSave_clicked();

    void on_tboxSearch_returnPressed();

    void on_actionProductos_3_triggered();

    void Eliminar_Registro_FC(int Fact_ID);

    //void on_actionProductos_triggered();

    //void on_actionProductos_2_triggered();

    void AddTableItemCarretilla(int Rk,Detalle_Factura * TmpDetalle);

    void AddTableItemCarretilla_Vista(int Rk,Detalle_Factura * TmpDetalle);

    void on_btnNuevaFactura_clicked();

    void on_btnNewClient_clicked();

    void on_btnSaveClient_clicked();

    void on_btnDeleteClient_clicked();


    void on_tblClients_itemDoubleClicked(QTableWidgetItem *item);

    void on_actionClientes_3_triggered();

    void on_actionClientes_2_triggered();

    void on_actionCargar_Productos_triggered();

    void on_btn100_clicked();

    void on_btn1k_clicked();

    void on_btn10k_clicked();

    void on_btn100k_clicked();

    void on_tboxSearchClient_returnPressed();

    void on_tboxNF_Nit_returnPressed();

    void on_tboxNF_Agregar_returnPressed();

    void on_btnNF_Eliminar_clicked();


    void on_btnNF_Vaciar_clicked();

    void on_btnNF_Registrar_clicked();

    void Clean_NuevaFactura();

    void on_listboxFacturas_itemDoubleClicked(QListWidgetItem *item);

    //void on_btnSave_2_clicked();

    void on_tabGeneral_tabBarClicked(int index);

    void on_btnPDF_clicked();

    void on_btnDeleteFact_clicked();

    void on_btntoChar_clicked();

private:
    Ui::MainWindow *ui;

    //Lista de Productos
    DC_List * LST_PROD;

    //Lista de Clientes
    SimpleList * LST_CLIENT;

    //Lista de Facturas
    Factu_List * LST_FACTUS;

    //Lista de Detalle Facturas
    ProductStack * DetFactu_Stack;

    QString SelectedCode;
    QString SelectedNit;
    int Fact_Correl = 1;

    int FCT_IDENT = -100;

};

#endif // MAINWINDOW_H
