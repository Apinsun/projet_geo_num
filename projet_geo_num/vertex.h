#ifndef VERTEX_H
#define VERTEX_H
#include "halfedge.h"
#include <iostream>
#include <string>
#include "vec3.h"

class halfEdge;

class vertex
{
public:
    vertex(float x=0.f, float y=0.f,float z=0.f, halfEdge* ptr=nullptr);
    static int identifiant;
    int id;
    halfEdge* ptrEdge;
    float coordX;
    float coordY;
    float coordZ;
        //FUNCTION
    void printVertex();
    vec3 uniformLaplacian();
    int voisinage1(); // renvoie le nombre de voisin dans le 1 voisinage
    void laplacianSmoothing(float lambda);
    vertex operator +(vec3 vecteur);
};

#endif // VERTEX_H
