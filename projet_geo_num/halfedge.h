#ifndef HALFEDGE_H
#define HALFEDGE_H
#include "face.h"
#include "vertex.h"

class face;
class vertex;

class halfEdge
{
public:
    halfEdge(vertex* source = nullptr, face* f = nullptr, halfEdge* precedent = nullptr
            , halfEdge* suivant = nullptr, halfEdge* teteBeche= nullptr);
    vertex *sommetSource;
    face* _face;
    halfEdge* prec;
    halfEdge* suiv;
    halfEdge* tb;
};

#endif // HALFEDGE_H
