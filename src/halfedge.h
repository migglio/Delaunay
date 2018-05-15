#ifndef HALFEDGE_H
#define HALFEDGE_H
class Triangulo;
class Vertice;
class HalfEdge
{
    public:
        HalfEdge(){}
        HalfEdge* getAdy(){return ady;}
        HalfEdge* getNext(){return next;}
        Vertice* getVertex(){return vertex;}
        Triangulo* getFace(){return face;}
        void setAdy(HalfEdge* h){ady=h;}
        void setNext(HalfEdge* h){next=h;}
        void setVertex(Vertice* v){vertex=v;}
        void setFace(Triangulo* f){face=f;}
        virtual ~HalfEdge(){}
    protected:
    private:
      HalfEdge * ady;
      HalfEdge * next;
      Vertice * vertex;
      Triangulo * face;
};

#endif // HALFEDGE_H
