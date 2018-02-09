#include "mesh.h"

using namespace std;

mesh::mesh()
{

}

void mesh::import(std::string path){
    ifstream fichier(path, ios::in);

    if(fichier){
        int nbrVertices, nbrEdges, nbrFaces,i,j, nVertexFace;
        int idTmp1, idTmp2; //indices des points composant une face

        fichier.ignore( 256, '\n');
        fichier >> nbrVertices >> nbrFaces >> nbrEdges;
        std::cout << "vertices : " << nbrVertices
                  << ", faces : " << nbrFaces
                  << ", edges : " << nbrEdges
                  <<std::endl;

            //recuperation des vertices
        vertex* vTmp;
        for(i=0;i<nbrVertices;i++){
            vTmp = new vertex();
            fichier >> vTmp->coordX >> vTmp->coordY >> vTmp->coordZ;
            this->tabV.push_back(vTmp);
        }
            // recupêration des faces et creation des arretes correspondantes

        face* fTmp;
        halfEdge* hfTmp,*hPrec; //hPrec est le dernier hf qu'on a cree

        for(i=0; i<nbrFaces;i++){
            hPrec = nullptr;
            fichier >> nVertexFace; //le nombre de vertices pour une face
            fichier >> idTmp1;
            fTmp = new face();

            for(j=0;j<nVertexFace-1;j++){
                idTmp2 = idTmp1; // idTmp2 est le point source
                fichier >> idTmp1;

                // A CONTINUER... hfTmp = ?  +creation de la face
               hfTmp  = new halfEdge(this->tabV[idTmp2], fTmp, hPrec, nullptr, nullptr );
               // on complete le point source si incomplet
               if(this->tabV[idTmp2]->ptrEdge == nullptr)
                   this->tabV[idTmp2]->ptrEdge = hfTmp;

               //fonction à modifier en utilisant une map
               hfTmp->tb = teteBecheSearcher(this->tabV[idTmp2]->id, this->tabV[idTmp1]->id, hfTmp);
               if(hPrec != nullptr ){
                   hPrec->suiv = hfTmp;
               }
               else{
                   fTmp->ptrEdge=hfTmp;
               }
               hPrec = hfTmp;
               // ajout dans la map des arretes
               this->tabE.insert( std::make_pair(this->tabV[idTmp2]->id,hfTmp) );
            }
            // ajouter le cote fermant la face
           halfEdge* hfCloture = new halfEdge(this->tabV[idTmp1], fTmp, hfTmp, fTmp->ptrEdge, nullptr);
           if(this->tabV[idTmp1]->ptrEdge == nullptr)
               this->tabV[idTmp1]->ptrEdge = hfTmp;
           hfTmp->suiv = hfCloture;

           fTmp->ptrEdge->prec=hfCloture;
           // ajout de la teteBeche
           hfCloture->tb = teteBecheSearcher(this->tabV[idTmp1]->id, hfCloture->suiv->sommetSource->id, hfCloture);
           // ajout dans la multimap des arretes
           this->tabE.insert(make_pair(this->tabV[idTmp1]->id, hfCloture));
           // ajout de la face
           this->tabF.push_back(fTmp);
           cout << this->tabF.size()<<" faces traitees"<< endl;
        }

        fichier.close();
    }

    else{
        std::cout << "Erreur lors de l'ouverture du fichier : " << path << std::endl;
    }

}

void mesh::exportOFF(std::string filename){
    ofstream fichier(filename, ios::trunc);
    if(fichier){
        cout << "Ecriture dans le fichier " << filename << endl;
        int i;
        fichier << "OFF"<<endl;
        fichier << this->tabV.size() << ' ' << this->tabF.size() << ' ' << this->tabE.size()/2<<endl;
            // on ecrit nos points
        for(i=0; i < this->tabV.size(); i++){
            fichier << this->tabV[i]->coordX << ' '
                    << this->tabV[i]->coordY << ' '
                    << this->tabV[i]->coordZ << ' ' << endl;
        }

            // on ecrit nos faces
        int faceSize, indice = -1 ,j;
        halfEdge* hfTmp;
        vector<vertex*>::iterator itV; // utilisé pour stocker le retour de find()
        for( i=0;i<this->tabF.size(); i++){
            faceSize = this->tabF[i]->nbrEdges();
            fichier << faceSize;
            hfTmp = this->tabF[i]->ptrEdge;

            do{
                //itV = std::find(this->tabV.begin(), this->tabV.end(), &(*hfTmp->sommetSource));

                // recherche de l'indice du sommet source de l'arrete hfTmp
                for(j=0; j< this->tabV.size(); j++){
                    if( this->tabV[j]->id == hfTmp->sommetSource->id ){
                        indice = j;
                        break;
                    }
                }
                if(indice == -1){
                    cout << "erreur lors de la recherche d'indice d'un sommet source !" << endl;
                }
                fichier << ' ' << indice ;
                hfTmp= hfTmp->suiv;
            }while(hfTmp != this->tabF[i]->ptrEdge);
            fichier << endl;
        }

    }
    else{
        cout << "Erreur lors de la creation du fichier " <<filename<<endl;
    }
}

/*
void mesh::addArrete(face* f, int id1, int id2, halfEdge* prec, bool dernier){

    // si on a deja une arrete id2 id1 alors on doit completer comme il faut

    halfEdge* newEdge = new halfEdge(this->tabV[id1], f, prec );
    //recheche si un halfedge complementaire existe deja

    //on met a jour la valeur suivant de l'halfEdge precedant si o est pas le premier

    // si dernier est vrai alors on peut relier notre arrete a la premier de la face
}*/

// id1 le vertex source , id2 le vertex source de notre tetebeche
halfEdge* mesh::teteBecheSearcher(int id1, int id2, halfEdge* hf){
    //voir la fonction equal_range pour parcourir les half_edges ayant un sommet source en commun
   // multimap<int, halfEdge*>::iterator it = this->tabE.find(id2);
    std::pair <std::multimap<int, halfEdge*>::iterator,std::multimap<int, halfEdge*>::iterator > ret;
    ret = this->tabE.equal_range(id2); //les half-edge ayant pour sommet-source id2
    for(std::multimap<int, halfEdge*>::iterator it = ret.first; it != ret.second; it++){
        if(it->second->suiv->sommetSource->id == id1 ){
            it->second->tb = hf;
            return it->second;
        }
    }
    return nullptr;
}

void mesh::laplacianSmoothing(int nbrIteration ,float lambda){
    int i,k;
    cout << "debut du smoothing..."<<endl;
    vertex vTmp;
    for(k=0; k < nbrIteration; k++){
        for( i=0; i< this->tabV.size(); i++){

            cout << "Point avant : ";
            tabV[i]->printVertex();

            vTmp = *this->tabV[i] + this->tabV[i]->uniformLaplacian() * lambda;
            tabV[i]->coordX = vTmp.coordX;
            tabV[i]->coordY = vTmp.coordY;
            tabV[i]->coordZ = vTmp.coordZ;

            cout << "Point apres : ";
            tabV[i]->printVertex();

        }
    }
    cout << "fin du smoothing..."<<endl;
}
