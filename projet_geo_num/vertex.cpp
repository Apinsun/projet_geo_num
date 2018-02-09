#include "vertex.h"
using namespace std;

vertex::vertex(float x, float y, float z, halfEdge* p)  :coordX(x), coordY(y), coordZ(z), ptrEdge(p)
{
    id = vertex::identifiant;
    vertex::identifiant++;
}

void vertex::printVertex(){
    std::cout << "point d'id:  "<< this->id
              <<", de coordonnee (" << this->coordX << "," << this->coordY << "," << this->coordZ
             <<")"<< std::endl;
}

int vertex::voisinage1(){
    int compteur =0;
    halfEdge* hfTmp = this->ptrEdge;
    do{
        hfTmp = hfTmp->tb;
        compteur++;
        hfTmp = hfTmp->suiv;
    }while(hfTmp != this->ptrEdge);
    return compteur;
}

vec3 vertex::uniformLaplacian(){
    vec3 somme;
    float compteur =0.f;
    halfEdge* hfTmp = this->ptrEdge;
    if (hfTmp == nullptr)
       cout << "ERREUR pas d'arrete !!!"<<endl;
    do{
        if(hfTmp->tb == nullptr)
           std::cout << "\t ERREUR, tete-beche nulle !!!"<<std::endl;
        hfTmp = hfTmp->tb;
        somme.x += hfTmp->sommetSource->coordX - this->coordX;
        somme.y += hfTmp->sommetSource->coordY - this->coordY;
        somme.z += hfTmp->sommetSource->coordZ - this->coordZ;
        compteur++;
        hfTmp = hfTmp->suiv;
    }while(hfTmp != this->ptrEdge);
    somme.x /= compteur;
    somme.y /= compteur;
    somme.z /= compteur;
    return somme;
}

vertex vertex::operator +(vec3 vecteur){
    vertex vReturn;
    vReturn.coordX=this->coordX + vecteur.x;
    vReturn.coordY=this->coordY + vecteur.y;
    vReturn.coordZ=this->coordZ + vecteur.z;
    return vReturn;
}
