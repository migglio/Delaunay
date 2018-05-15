#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "list"
#include "Triangulo.h"
#include "Vertice.h"
#include "halfedge.h"
#include "math.h"
#include "dialog.h"
#include "dialogvor.h"
#include<iostream>
using namespace std;
class Delaunay
{
    public:
        Delaunay(float maximo){this->maximo=3*maximo;d=new Dialog();dVor=new DialogVor();cte=50;}
        Triangulo* encontrarTriangulo(Vertice* v);
        void triangulacionDelaunay();
        void voronoi();
        bool agregarVertice(Vertice* v);
        virtual ~Delaunay(){}
    protected:
    private:
        float maximo;//Triangulo infinito
        list<Triangulo*> triangulos;
        list<Vertice*> vertices;
        //Intefaz
        Dialog* d;
        DialogVor* dVor;
        int cte;

void inicializar(){
    //Creo triangulo infinito y sus halfedge
    HalfEdge* h1=new HalfEdge();
    HalfEdge* h2=new HalfEdge();
    HalfEdge* h3=new HalfEdge();
    Vertice* v1=new Vertice(0.0,maximo,h1);
    Vertice* v2=new Vertice(maximo,0.0,h3);
    Vertice* v3=new Vertice(-maximo,-maximo,h2);
    Triangulo* t=new Triangulo(h1);
    h1->setNext(h2);
    h1->setVertex(v3);
    h1->setAdy(NULL);
    h1->setFace(t);
    h2->setNext(h3);
    h2->setVertex(v2);
    h2->setAdy(NULL);
    h2->setFace(t);
    h3->setNext(h1);
    h3->setVertex(v1);
    h3->setAdy(NULL);
    h3->setFace(t);
    triangulos.push_back(t);
}

Vertice calcularCentro(Vertice p1, Vertice p2, Vertice p3){
    //Obtiene el centro del triangulo formado por los tres puntos p1,p2,p3.
     float offset = (p2.getX()*p2.getX()) + (p2.getY()*p2.getY());
     float bc =   ((p1.getX()*p1.getX()) + (p1.getY()*p1.getY()) - offset )/2.0;
     float cd =   (offset - p3.getX()*p3.getX() - p3.getY()*p3.getY())/2.0;
     float det =  (p1.getX() - p2.getX()) * (p2.getY() - p3.getY()) - (p2.getX() - p3.getX())* (p1.getY() - p2.getY());
     double idet = 1/det;
     double centerx =  (bc * (p2.getY() - p3.getY()) - cd * (p1.getY() - p2.getY())) * idet;
     double centery =  (cd * (p1.getX() - p2.getX()) - bc * (p2.getX() - p3.getX())) * idet;
     Vertice center = Vertice(centerx,centery);
     return center;
}

bool dentroDeCirculo (Vertice p, Vertice q, Vertice r, Vertice s){
  //Devuelve si s está dentro del círcilo formado por p, q, y r  
  double ax = q.getX() - p.getX();
  double ay = q.getY() - p.getY();
  double aa = (ax * ax) + (ay * ay);
  double bx = r.getX() - p.getX();
  double by = r.getY() - p.getY();
  double bb = (bx * bx) + (by * by);
  double cx = s.getX() - p.getX();
  double cy = s.getY() - p.getY();
  double cc = (cx * cx) + (cy * cy);
  double res=((  aa * (bx * cy - by * cx)
           - bb * (ax * cy - ay * cx)
           + cc * (ax * by - ay * bx)));
  return res<0;
}

void legalizar(HalfEdge* h1,HalfEdge* h2,HalfEdge* h3) {
//Chequea y realiza las modificaciones para que los nuevos triangulos no rompan la propiedad de Delaunay
        HalfEdge* hd;
        Vertice v1=*(h1->getVertex());
        Vertice v2=*(h2->getVertex());
        Vertice v3=*(h3->getVertex());
        if(h1->getAdy()!=NULL){
            hd=h1->getAdy()->getNext();
            if (dentroDeCirculo(v1,v2,v3,*(hd->getVertex())))
                flipArista(h1,h2,h3,hd);
        }
        if(h2->getAdy()!=NULL){
            hd=h2->getAdy()->getNext();
            if (dentroDeCirculo(v1,v2,v3,*(hd->getVertex())))
                flipArista(h2,h3,h1,hd);
        }
        if(h3->getAdy()!=NULL){
            hd=h3->getAdy()->getNext();
            if (dentroDeCirculo(v1,v2,v3,*(hd->getVertex())))
                flipArista(h3,h1,h2,hd);
        }
}

void flipArista(HalfEdge* h1,HalfEdge* h2,HalfEdge* h3,HalfEdge* hd){
//Intercambia la arista ilegal.
            //acomoda la referencia del vertice hacia el nuevo he
            if(h1->getAdy()==hd->getNext()->getVertex()->getHEdg()) hd->getNext()->getVertex()->setHe(h2);
            if(h3->getVertex()->getHEdg()==h1) h3->getVertex()->setHe(hd);
            //comienza flip
            h1->getAdy()->setNext(hd->getNext());
            hd->getNext()->setFace(h2->getFace());
            hd->getNext()->setNext(h1->getNext());
            h2->setNext(h1->getAdy());
            hd->setNext(h1);
            h1->setNext(h3);
            h1->setFace(h3->getFace());
            h1->getAdy()->setFace(h2->getFace());
            hd->setFace(h3->getFace());
            h2->setFace(h1->getAdy()->getFace());
            h1->setVertex(h2->getVertex());
            h1->getAdy()->setVertex(hd->getVertex());
            h3->setNext(hd);
            legalizar(h1,h1->getNext(),h1->getNext()->getNext());
            legalizar(h2,h2->getNext(),h2->getNext()->getNext());
}

bool existeVertice(Vertice* vert){
    list<Vertice*>::const_iterator v;
    for (v=vertices.begin();v!=vertices.end();v++)
    if(*(*v)==*vert)
          return true;
   return false;
}

void agregarLinea(list<QLine*> &l, HalfEdge* he, Vertice centro){
    //Voronoi
    Vertice v;
    if(he->getAdy()!=NULL){
        v=calcularCentro(*(he->getAdy()->getVertex()),*(he->getAdy()->getNext()->getVertex()),*(he->getAdy()->getNext()->getNext()->getVertex()));
        QLine* l1=new QLine(cte*(centro.getX()),cte*(centro.getY()),cte*(v.getX()),cte*(v.getY()));
        l.push_back(l1);
        }
}
};

#endif // DELAUNAY_H
