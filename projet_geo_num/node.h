#ifndef NODE_H
#define NODE_H

#include "glm/glm.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "sortvertices.h"

class Node
{
public:
    glm::vec3 location;
    Node* leftChild;
    Node* rightChild;
    Node();
    std::vector<glm::vec3> import(std::string path);
    Node* kdTree(std::vector<glm::vec3>& verticesList, int depth, int begin, int end);
};

#endif // NODE_H
