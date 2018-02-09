#include <iostream>
#include "face.h"
#include "vertex.h"
#include "halfedge.h"
#include "mesh.h"

using namespace std;

int vertex::identifiant=0;
int face::identifiant=0;

int main()
{
    vertex v0 = vertex();
    vertex v1  =vertex(5.0f,4.0f);
    halfEdge h0(&v0);
    halfEdge h1(&v1);
    v0.printVertex();
    v1.printVertex();

    mesh m;
    string path("./cube.off");
    m.import(path);

    int i;
    for(i=0; i< m.tabF.size();i++){
       m.tabF[i]->printFace();
    }

    cout<< "Test des tete-beches...";
    if( m.tabF[0]->ptrEdge->sommetSource == m.tabF[0]->ptrEdge->tb->suiv->sommetSource ){
        cout<<" semble OK"<<endl;
    }
    else{
        cout << "probablement faux !" << endl;
    }

    cout << "test uniform Laplacian"<<endl;
    //m.tabV[0]->uniformLaplacian();
    cout << "fin test uniform Laplacian"<<endl;

    m.laplacianSmoothing(1,1.f);
    m.exportOFF("test.off");

    return 0;
}
