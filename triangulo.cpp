#include "vertice.h"
#include "triangulo.h"
#include "halfedge.h"
#include "math.h"
#include <iostream>
using namespace std;
bool Triangulo::estaAdentro(Vertice* p){
    //devuelve si el punto p esta dentro del triangulo.
    Vertice* v1=he->getVertex();
    Vertice* v2=he->getNext()->getVertex();
    Vertice* v3=he->getNext()->getNext()->getVertex();
    float alpha = ((float)((v2->getY() - v3->getY())*(p->getX() - v3->getX()) + (v3->getX() - v2->getX())*(p->getY() - v3->getY())) /
            (float)((v2->getY() - v3->getY())*(v1->getX() - v3->getX()) + (v3->getX() - v2->getX())*(v1->getY() - v3->getY())));
    float beta = ((float)((v3->getY() - v1->getY())*(p->getX() - v3->getX()) + (v1->getX() - v3->getX())*(p->getY() - v3->getY())) /
           (float)((v2->getY() - v3->getY())*(v1->getX() - v3->getX()) + (v3->getX() - v2->getX())*(v1->getY() - v3->getY())));
    float gamma = 1.0 - alpha - beta;
    return 0<= alpha && alpha <= 1 && 0 <= beta && beta <= 1 && 0 <= gamma && gamma <= 1;
}

Vertice* Triangulo::getV1(){
    return he->getVertex();
}

Vertice* Triangulo::getV2(){
    return he->getNext()->getVertex();
}

Vertice* Triangulo::getV3(){
    return he->getNext()->getNext()->getVertex();
}

bool Triangulo::operator==(Triangulo  &r1){
     bool c1= ((this->getV1()->getX() == r1.getV1()->getX()) && (this->getV1()->getY() == r1.getV1()->getY()));
     bool c2= ((this->getV2()->getX() == r1.getV2()->getX()) && (this->getV2()->getY() == r1.getV2()->getY()));
     bool c3= ((this->getV3()->getX() == r1.getV3()->getX()) && (this->getV3()->getY() == r1.getV3()->getY()));
     return c1&&c2&&c3;
}

std::list<QLine*> Triangulo::getLines(int maximo,int cte){
    std::list<QLine*> lines=std::list<QLine*>();
    if(abs(getV1()->getX())!=maximo && abs(getV1()->getY())!=maximo && abs(getV2()->getX())!=maximo && abs(getV2()->getY())!=maximo){
        QLine* l1=new QLine(cte*(getV1()->getX()),cte*(getV1()->getY()),cte*(getV2()->getX()),cte*(getV2()->getY()));
        lines.push_back(l1);
    }
    if(abs(getV2()->getX())!=maximo && abs(getV2()->getY())!=maximo && abs(getV3()->getX())!=maximo && abs(getV3()->getY())!=maximo){
        QLine* l2=new QLine(cte*(getV2()->getX()),cte*(getV2()->getY()),cte*(getV3()->getX()),cte*(getV3()->getY()));
        lines.push_back(l2);
    }
    if(abs(getV3()->getX())!=maximo && abs(getV3()->getY())!=maximo && abs(getV1()->getX())!=maximo && abs(getV1()->getY())!=maximo){
        QLine* l3=new QLine(cte*(getV3()->getX()),cte*(getV3()->getY()),cte*(getV1()->getX()),cte*(getV1()->getY()));
        lines.push_back(l3);
    }
    return lines;
}
