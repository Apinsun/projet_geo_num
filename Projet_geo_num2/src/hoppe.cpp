#include "../header/hoppe.h"
#include "../header/plane.h"

Hoppe::Hoppe()
{

}

// Deroulement de l'algorithme de Hoppe
void Hoppe::solve()
{
    // Definition du chemin du fichier
    std::string path("../testGN/block.off");

    // Importation du fichier en un nuage de points
    import(path);

    // Calcul des centroides a partir des k-voisins
    // Calcul des normales
    int K = 10;
    computeCentroidNormal(K);
}

// Fonction d'importation d'un fichier OFF
// Arguments: path chaine de caracteres correspondant au chemin du fichier OFF
// Initialise et remplit le nuage de points _cloud
void Hoppe::import(std::string path)
{
    // Ouverture du fichier
    std::ifstream file(path, std::ios::in);

    // Si le fichier a ete ouvert
    if(file)
    {
        // Definition des variables pour les nombres de points, aretes et faces
        int nbrVertices, nbrEdges, nbrFaces;

        // Saut de la premiere ligne
        file.ignore( 256, '\n');
        // Recuperation du nombre de sommets, faces et aretes
        file >> nbrVertices >> nbrFaces >> nbrEdges;

        // Definition des dimensions du nuage de points
        _cloud.width = nbrVertices;
        _cloud.height = 1;

        // Definition d'un point temporaire
        pcl::PointXYZ tmp;

        // Recuperation des points et ajout dans le nuage de points
        for(int i = 0; i < nbrVertices; i++)
        {
            file >> tmp.x >> tmp.y >> tmp.z;
            _cloud.push_back(tmp);
        }

        // Fermeture du fichier
        file.close();
    }
    // Si le fichier ne s'est pas ouvert
    else
    {
        std::cout << "Error while opening file :" << path << std::endl;
    }
}

// Calcul des centroides et des normales en chaque point
// Arguments: k nombre de k-voisins souhaite
// Initialise le kd-tree _kdtree, l'utilise pour calculer et initialiser les
// centroides et les normales
void Hoppe::computeCentroidNormal(int k)
{
    // Ajout des points dans le kdtree
    _kdtree.setInputCloud(_cloud.makeShared());

    // Declaration des structures permettant de recuperer les index des
    // k-voisins et la distance
    std::vector<int> kNeighborhoodIndex;
    std::vector<float> kNeighborhoodSquareDistance;

    // Declaration des variables temporaires permettant de recuperer les donnees
    pcl::PointXYZ tmpCentroid;
    pcl::PointXYZ tmpNormalPoint;
    Eigen::Matrix3d tmpCovarianceMatrix;
    Eigen::Vector3f tmpNormal;

    // Definition de la taille du nuage de points de centroides
    _cloudCentroid.width = _cloud.size();
    _cloudCentroid.height = 1;
    
    // Parcours du nuage de points _cloud
    for(int i = 0; i < _cloud.points.size(); i++)
    {
        // Calcul des k-voisins (PCL)
        //      Arguments: _cloud[i] un des points du nuage de points
        //                 k         nombre de k-voisins
        //                 kNeighborhoodIndex vector modifie dans la fonction
        //                      recupere les indices des k-voisins
        //                 kNeighborhoodSquareDistance vector modifie dans la
        //                      fonction (inutilise par la suite)
        // Si il y a au moins un k-voisin
        if (_kdtree.nearestKSearch(_cloud[i], k, kNeighborhoodIndex, kNeighborhoodSquareDistance) > 0)
        {
            // Parcours des indices obtenus par recherche des k-voisins
            // Obtention du centroid en effectuant la moyenne des k-voisins
            for(int j = 0; j < kNeighborhoodIndex.size(); j++)
            {
                tmpCentroid = tmpCentroid + _cloud[ kNeighborhoodIndex[j] ];
            }
            tmpCentroid = tmpCentroid / k;
            // Ajout du centroid dans le nuage de points
            _cloudCentroid.push_back(tmpCentroid);

            // Parcours des indices obtenus par recherche des k-voisins
            // Obtention de la matrice de covariance par somme des produits
            //  dyadiques d'un k-voisin et du centroide associe
            for(int j = 0; j < kNeighborhoodIndex.size(); j++)
            {
                tmpNormalPoint = _cloud[ kNeighborhoodIndex[j] ] - _cloudCentroid[i];
                tmpCovarianceMatrix = outer_product(tmpNormalPoint, tmpNormalPoint);
            }

            // Recuperation des valeurs propres et des vecteurs propres
            Eigen::EigenSolver<Eigen::Matrix3d> es(tmpCovarianceMatrix);
            // Recuperation de l'indice de la plus petite valeur propre
            int minIndex = minEigenValue(es);
            // Recuperation du vecteur propre associe
            auto eigenVector = es.eigenvectors().col(minIndex);

            // Obtention de la normale à partir du vecteur propre
            tmpNormal(0,0) = eigenVector(0,0).real();
            tmpNormal(1,0) = eigenVector(1,0).real();
            tmpNormal(2,0) = eigenVector(2,0).real();
            // Ajout de la normale dans la liste
            _normal.push_back(tmpNormal);
        }
    }
}
