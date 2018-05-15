#ifndef TRIANGULO_H
#define TRIANGULO_H
#include "Vertice.h"
#include "qline.h"
#include "list"
//class HalfEdge;
class Triangulo
{
    public:
        Triangulo(HalfEdge* h){he=h;}
        HalfEdge* getHEdg(){return he;}
        bool estaAdentro(Vertice* p);
        Vertice* getV1();
        Vertice* getV2();
        Vertice* getV3();
        void setHe(HalfEdge* h){he=h;}
        std::list<QLine*> getLines(int maximo,int cte);
        bool operator==(Triangulo  &r1);
        virtual ~Triangulo(){}
    protected:
    private:
        HalfEdge * he;
};

#endif // TRIANGULO_H
