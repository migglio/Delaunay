#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <list>
#include "triangulo.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void paintEvent(QPaintEvent *e);
    void setTriang(std::list<Triangulo*> t){triangulos=t;}
    void setMax(int m){maximo=m;}
    void setCte(int c){cte=c;}
private:
    Ui::Dialog *ui;
    std::list<Triangulo*> triangulos;
    int maximo;
    int cte;
};

#endif // DIALOG_H
