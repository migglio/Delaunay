#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qstandarditemmodel.h"
#include "qmessagebox.h"
#include "list"
#include "Triangulo.h"
#include <cstddef>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->doubleSpinBoxX->setButtonSymbols( QAbstractSpinBox::NoButtons );
    ui->doubleSpinBoxY->setButtonSymbols( QAbstractSpinBox::NoButtons );
    model = new QStandardItemModel(7,2,this); //2 Filas y 3 Columnas
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("X")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Y")));
    ui->tableViewCoord->setModel(model);
    f=0;
    c=0;
    delaunay=new Delaunay(10);//Maximo permitido
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_calcularDelaunay_clicked(){
    delaunay->triangulacionDelaunay();
}
void MainWindow::on_calcularVor_clicked(){
    delaunay->voronoi();
}
void MainWindow::on_agregarPunto_clicked(){
    float x=ui->doubleSpinBoxX->value();
    float y=ui->doubleSpinBoxY->value();
    agregarItemTabla(x,y);
    ui->doubleSpinBoxX->setValue(0);
    ui->doubleSpinBoxY->setValue(0);
}
void MainWindow::on_puntosPredef_clicked(){
        agregarItemTabla(3,4);
        agregarItemTabla(4.8,6.5);
        agregarItemTabla(8,6);
        agregarItemTabla(10,9);
        agregarItemTabla(2,5);
        agregarItemTabla(3,8);
        agregarItemTabla(6.5,8);
        agregarItemTabla(6,9);
        agregarItemTabla(2,4);
        agregarItemTabla(3,6);
        agregarItemTabla(5,2);
        agregarItemTabla(6,4);
        agregarItemTabla(7,3);
        agregarItemTabla(6,2.2);
}
