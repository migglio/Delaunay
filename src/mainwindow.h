#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qstandarditemmodel.h"
#include <QMainWindow>
#include "delaunay.h"
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
    void on_calcularDelaunay_clicked();

    void on_agregarPunto_clicked();

    void on_calcularVor_clicked();

    void on_puntosPredef_clicked();

private:
    Ui::MainWindow *ui;
    int f,c;
    QStandardItemModel *model;
    Delaunay* delaunay;

    void agregarItemTabla(float x,float y){
        Vertice* v=new Vertice(x,y);
        if(delaunay->agregarVertice(v)){
            QStandardItem *firstRow1stCol = new QStandardItem(QString::number(x));
            model->setItem(f,c,firstRow1stCol);
            c++;
            QStandardItem *firstRow2ndCol = new QStandardItem(QString::number(y));
            model->setItem(f,c,firstRow2ndCol);
            f++;c=0;
    }
 }
};

#endif // MAINWINDOW_H
