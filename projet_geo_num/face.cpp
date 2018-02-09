#include "face.h"
using namespace std;

face::face(halfEdge* ptr) : ptrEdge(ptr)
{
    id = face::identifiant;
    face::identifiant++;
}

void face::printFace(){
    cout << "face numero " << this->id<<endl;
    halfEdge* hfTmp = this->ptrEdge;
    while(hfTmp->suiv != this->ptrEdge){
        cout << "arrete de sommet source : " << hfTmp->sommetSource->id
             << " et de sommet final : " << hfTmp->suiv->sommetSource->id << endl;
        hfTmp = hfTmp->suiv;
    }
    cout << "fin de la face "<< this->id << endl;
}

int face::nbrEdges(){
    int compteur = 0;
    halfEdge* hfTmp = this->ptrEdge;
    do{
        compteur++;
        hfTmp = hfTmp->suiv;
    }while(hfTmp != this->ptrEdge);
    return compteur;
}
