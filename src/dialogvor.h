#ifndef DIALOGVOR_H
#define DIALOGVOR_H
#include <list>
#include <QDialog>
#include "vertice.h"
namespace Ui {
class DialogVor;
}

class DialogVor : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVor(QWidget *parent = 0);
    void setLines(std::list<QLine*> l){lines=l;}
    void setVertices(std::list<Vertice*> v){vertices=v;}
    void paintEvent(QPaintEvent *e);
    void setCte(int c){cte=c;}
    ~DialogVor();

private:
    Ui::DialogVor *ui;
    std::list<QLine*> lines;
    std::list<Vertice*> vertices;
    int cte;
};

#endif // DIALOGVOR_H
