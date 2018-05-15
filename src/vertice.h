#ifndef VERTICE_H
#define VERTICE_H
#include <cstddef>
#import "halfedge.h"
class Vertice
{
    public:
        Vertice(){x=-1;y=-1;}
        Vertice(float x, float y){this->x=x;this->y=y;he=NULL;}
        Vertice(float x, float y,HalfEdge* h){this->x=x;this->y=y;he=h;}
        HalfEdge* getHEdg(){return he;}
        float getX(){return x;}
        float getY(){return y;}
        void setHe(HalfEdge* h){he=h;}
        bool operator<=(Vertice &r1){return (x <= r1.getX());}
        bool operator==(Vertice &r1){return (x == r1.getX() && y==r1.getY());}
        virtual ~Vertice(){}

    protected:
    private:
        float x;
        float y;
        HalfEdge* he;
};

#endif // VERTICE_H
