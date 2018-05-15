#include "Delaunay.h"
#include "vertice.h"
#include "list"
#include "map"
#include <cstddef>
#include <iostream>
#include "math.h"

bool Delaunay::agregarVertice(Vertice* v){
//Evita agregar puntos repetidos
    if(!existeVertice(v)){
        vertices.push_back(v);
        return true;
    }
    return false;
}

Triangulo* Delaunay::encontrarTriangulo(Vertice* v){
//Retorna el triangulo en el que cae el vertice
      list<Triangulo*>::const_iterator t;
      for (t=triangulos.begin();t!=triangulos.end();t++)
      if((*t)->estaAdentro(v))
            return *t;
     return NULL;
}

void Delaunay::triangulacionDelaunay(){
    if(vertices.size()>=3){
        triangulos.clear();
        inicializar();
        list<Vertice*>::const_iterator v;
        for (v=vertices.begin();v!=vertices.end();v++){
              Triangulo* t=encontrarTriangulo(*v);
              if(t!=NULL){
                  Vertice* a=t->getHEdg()->getVertex();
                  Vertice* b=t->getHEdg()->getNext()->getVertex();
                  Vertice* c=t->getHEdg()->getNext()->getNext()->getVertex();
                  //Creo halfEdge
                  HalfEdge* he11=t->getHEdg()->getNext();
                  HalfEdge* he12=new HalfEdge();
                  HalfEdge* he13=new HalfEdge();
                  HalfEdge* he21=t->getHEdg()->getNext()->getNext();
                  HalfEdge* he22=new HalfEdge();
                  HalfEdge* he23=new HalfEdge();
                  HalfEdge* he31=t->getHEdg();
                  HalfEdge* he32=new HalfEdge();
                  HalfEdge* he33=new HalfEdge();
                  (*v)->setHe(he13);
                  //genero triangulos nuevos
                  Triangulo* t1=new Triangulo(he11);
                  Triangulo* t2=new Triangulo(he21);
                  Triangulo* t3=new Triangulo(he31);
                  triangulos.push_back(t1);
                  triangulos.push_back(t2);
                  triangulos.push_back(t3);
            //****************************
                  //Primer triangulo
                  he11->setFace(t1);
                  he11->setNext(he12);
                  he12->setFace(t1);
                  he12->setNext(he13);
                  he12->setVertex(*v);
                  he12->setAdy(he23);
                  he13->setFace(t1);
                  he13->setNext(he11);
                  he13->setVertex(a);
                  he13->setAdy(he32);
            //****************************
                  //Segundo triangulo
                  he21->setFace(t2);
                  he21->setNext(he22);
                  he22->setFace(t2);
                  he22->setNext(he23);
                  he22->setVertex(*v);
                  he22->setAdy(he33);
                  he23->setFace(t2);
                  he23->setNext(he21);
                  he23->setVertex(b);
                  he23->setAdy(he12);
            //****************************
                  //Tercer triangulo
                  he31->setFace(t3);
                  he31->setNext(he32);
                  he32->setFace(t3);
                  he32->setNext(he33);
                  he32->setVertex(*v);
                  he32->setAdy(he13);
                  he33->setFace(t3);
                  he33->setNext(he31);
                  he33->setVertex(c);
                  he33->setAdy(he22);
            //Chequeo nuevos triangulos
                  legalizar(he11,he12,he13);
                  legalizar(he21,he22,he23);
                  legalizar(he31,he32,he33);
              }
                else vertices.remove(*v);

        }
    //Interfaz
    d->setTriang(triangulos);
    d->setMax(maximo);
    d->setCte(cte);
    d->show();
    }
}

void Delaunay::voronoi(){
    if(vertices.size()>=3){
        triangulacionDelaunay();
        list<QLine*>lines=list<QLine*>();
        list<Triangulo*>::const_iterator tIt;
        for (tIt=triangulos.begin();tIt!=triangulos.end();tIt++){
                //recorro todos los triangulos delaunay
                Vertice centro=calcularCentro(*((*tIt)->getV1()),*((*tIt)->getV2()),*((*tIt)->getV3()));
                HalfEdge* he=(*tIt)->getHEdg();
                agregarLinea(lines,he,centro);
                he=he->getNext();
                agregarLinea(lines,he,centro);
                he=he->getNext();
                agregarLinea(lines,he,centro);
                he=he->getNext();
            }
        //Interfaz
        dVor->setLines(lines);
        dVor->setVertices(vertices);
        dVor->setCte(cte);
        dVor->show();
    }
}

