#include "node.h"

Node::Node()
{

}

std::vector<glm::vec3> Node::import(std::string path)
{
    std::ifstream file(path, std::ios::in);

    std::vector<glm::vec3> verticesList;

    if(file)
    {
        int nbrVertices, nbrEdges, nbrFaces;

        file.ignore( 256, '\n');
        file >> nbrVertices >> nbrFaces >> nbrEdges;
        std::cout << "Vertices:" << nbrVertices << std::endl;

        // Recuperation des points
        glm::vec3 vTmp;
        for(int i = 0; i < nbrVertices; i++)
        {
            file >> vTmp.x >> vTmp.y >> vTmp.z;
            verticesList.push_back(vTmp);
        }

        file.close();
    }
    else
    {
        std::cout << "Error while opening file :" << path << std::endl;
    }

    return verticesList;
}

Node* Node::kdTree(std::vector<glm::vec3>& verticesList, int depth, int begin, int end)
{
    if(begin >= end)
        return NULL;
    // Axis definition: 0 -> x, 1 -> y, 2 -> z
    int axis = depth%3;

    // Sort vertices list
    std::sort(verticesList.begin()+begin, verticesList.begin()+end, SortVertices(axis));

    // Choose median as pivot element
    int middle = (begin+end)/2;
    glm::vec3 median = verticesList[middle];

    // Create node and construct subtree
    Node* n = new Node();
    n->location = median;
    n->leftChild = kdTree(verticesList, depth+1, begin, middle-1);
    n->rightChild = kdTree(verticesList, depth+1, middle+1, end);

    return n;
}
