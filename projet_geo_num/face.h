#ifndef FACE_H
#define FACE_H
#include "halfedge.h"

class halfEdge;

class face
{
public:
    face( halfEdge* ptr=nullptr );
    static int identifiant;
    int id;
    halfEdge* ptrEdge;
        // FUNCTION
    void printFace();
    int nbrEdges();
};

#endif // FACE_H
