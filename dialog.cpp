#include "dialog.h"
#include "ui_dialog.h"

#include "qpainter.h"
#include "delaunay.h"
#include "vertice.h"
#include "math.h"
#include <iostream>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    int w_2 =(width()/4)-width()*0.1;
    int h_2 =(height()/2)+height()*0.35;
    painter.setPen( Qt::blue );
    painter.drawLine( 0, h_2, width(), h_2);     // Eje X
    painter.drawLine( w_2, 0 , w_2, height() );  // Eje Y
    QMatrix m;
    m.translate( w_2, h_2 );
    m.scale( 1, -1 );
    painter.setMatrix(m);
    list<Triangulo*>::const_iterator tIt;
    painter.setPen(Qt::red);
    for (tIt=triangulos.begin();tIt!=triangulos.end();tIt++){
        list<QLine*> listLine=(*tIt)->getLines(maximo,cte);
        list<QLine*>::const_iterator line;
        for (line=listLine.begin();line!=listLine.end();line++)
            painter.drawLine(*(*line));
    }
}
