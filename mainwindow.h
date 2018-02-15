#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dc_list.h"
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
    void UpdateTable();
    bool ValidateProductInfo(Product * TmpProd);
    void AddTableItem(int Rk,Product * TmpProd);
    void DeleteTableItem();

    void on_btnDelete_clicked();

    void on_tblProd_itemDoubleClicked(QTableWidgetItem *item);
    bool ValidateProductDelete();

    void on_btnSave_clicked();

    void on_tboxSearch_returnPressed();

    void on_actionProductos_3_triggered();

    void on_actionProductos_triggered();

    void on_actionProductos_2_triggered();

private:
    Ui::MainWindow *ui;
    DC_List * LST_PROD;
    QString TmpCode;
};

#endif // MAINWINDOW_H
