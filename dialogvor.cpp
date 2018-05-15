#include "dialogvor.h"
#include "ui_dialogvor.h"
#include <list>
#include "QPainter"
#include "vertice.h"
#include <iostream>

using namespace std;
DialogVor::DialogVor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVor)
{
    ui->setupUi(this);
}

DialogVor::~DialogVor()
{
    delete ui;
}

void DialogVor::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    int w_2 =(width()/4)-width()*0.1;
    int h_2 =(height()/2)+height()*0.35;
    painter.setPen( Qt::blue );
    painter.drawLine( 0, h_2, width(), h_2);
    painter.drawLine( w_2, 0 , w_2, height() );
    QMatrix m;
    m.translate( w_2, h_2 );
    m.scale( 1, -1 );
    painter.setMatrix(m);
    painter.setPen(QColor(102,0,0,255));
    list<QLine*>::const_iterator line;
    for (line=lines.begin();line!=lines.end();line++)
        painter.drawLine(*(*line));
    list<Vertice*>::const_iterator v;
    QPen p=QPen();
    p.setWidth(5);
    p.setColor(Qt::black);
    painter.setPen(p);
    for (v=vertices.begin();v!=vertices.end();v++)
        painter.drawPoint(QPoint(cte*((*v)->getX()),cte*((*v)->getY())));
}
