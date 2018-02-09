#include "halfedge.h"

halfEdge::halfEdge(vertex* source, face* f , halfEdge* precedent
        , halfEdge* suivant , halfEdge* teteBeche) : sommetSource(source),
    _face(f), prec(precedent), suiv(suivant), tb(teteBeche)
{
}
