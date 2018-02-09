#ifndef MESH_H
#define MESH_H
#include "vertex.h"
#include "face.h"
#include <vector>
#include <map>
#include <fstream>
#include <map>

class mesh
{
public:
    mesh();
    std::vector<vertex*> tabV;      // tableau des vertices
    std::vector<face*> tabF;        // tableau des faces
    std::multimap<int,halfEdge*> tabE;   // tableau des arretes avec comme cle l'id du point source

        // FUNCTION

    //les indices sont ceux dans le tableau de sommet, == ceux aux formats OFF
    void addArrete(face* f, int indice1, int indice2, halfEdge* hf, bool dernier);
    halfEdge* teteBecheSearcher(int id1, int id2, halfEdge* hf);
    void import(std::string path); // initialise la structure avec les donnes d'un fichier OFF
    void exportOFF(std::string filename);
    void laplacianSmoothing(int nbrIteration ,float lambda);
};

#endif // MESH_H
