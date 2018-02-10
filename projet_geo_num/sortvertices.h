#ifndef SORTVERTICES_H
#define SORTVERTICES_H

#include "glm/glm.hpp"

class SortVertices
{
public:
    int axis;
    SortVertices(int a) {axis = a;}
    bool operator()(glm::vec3 v1, glm::vec3 v2);
};

bool SortVertices::operator()(glm::vec3 v1, glm::vec3 v2)
{
    return v1[axis] < v2[axis];
}

#endif // SORTVERTICES_H
