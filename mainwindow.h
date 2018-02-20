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

    void on_actionProductos_triggered();

    void on_actionProductos_2_triggered();

    void on_btnNuevaFactura_clicked();

    void on_btnNewClient_clicked();

    void on_btnSaveClient_clicked();

    void on_btnDeleteClient_clicked();



    void on_tblClients_itemDoubleClicked(QTableWidgetItem *item);

    void on_actionClientes_3_triggered();

    void on_actionClientes_2_triggered();

private:
    Ui::MainWindow *ui;
    DC_List * LST_PROD;
    SimpleList * LST_CLIENT;
    QString SelectedCode;
    QString SelectedNit;
};

#endif // MAINWINDOW_H
