#include "../header/hoppe.h"
#include "../header/plane.h"

Hoppe::Hoppe()
{

}

// Fonction permettant de dérouler l'algorithme
void Hoppe::solve()
{
    // Definition du chemin du fichier
    std::string path("../testGN/block.off");

    // Importation du fichier en un nuage de points
    import(path);

    // Calcul des centroides a partir des k-voisins
    int K = 10;
    computeCentroid(K);
}

void Hoppe::import(std::string path)
{
    std::ifstream file(path, std::ios::in);

    if(file)
    {
        int nbrVertices, nbrEdges, nbrFaces;

        file.ignore( 256, '\n');
        file >> nbrVertices >> nbrFaces >> nbrEdges;

        _cloud.width = nbrVertices;
        _cloud.height = 1;

        pcl::PointXYZ tmp;

        for(int i = 0; i < nbrVertices; i++)
        {
            file >> tmp.x >> tmp.y >> tmp.z;
            _cloud.push_back(tmp);
        }

        file.close();
    }
    else
    {
        std::cout << "Error while opening file :" << path << std::endl;
    }
}

void Hoppe::computeCentroid(int k)
{
    // Ajout des points dans le kdtree
    _kdtree.setInputCloud(_cloud.makeShared());

    // Declaration des structures permettant de recuperer les index des
    // k-voisins et la distance
    std::vector<int> kNeighborhoodIndex;
    std::vector<float> kNeighborhoodSquareDistance;

    pcl::PointXYZ tmpCentroid;
    pcl::PointXYZ tmpNormalPoint;
    Eigen::Matrix3d tmpCovarianceMatrix;
    Eigen::Vector3f tmpNormal;
    // Recherche des k-voisins a partir des kd-tree
    _cloudCentroid.width = _cloud.size();
    _cloudCentroid.height = 1;
    
    for(int i = 0; i < _cloud.points.size(); i++)
    {
        if (_kdtree.nearestKSearch(_cloud[i], k, kNeighborhoodIndex, kNeighborhoodSquareDistance) > 0)
        {
            for(int j = 0; j < kNeighborhoodIndex.size(); j++)
            {
                tmpCentroid = tmpCentroid + _cloud[ kNeighborhoodIndex[j] ];
            }
            tmpCentroid = tmpCentroid / k;
            _cloudCentroid.push_back(tmpCentroid);

            for(int j = 0; j < kNeighborhoodIndex.size(); j++)
            {
                tmpNormalPoint = _cloud[ kNeighborhoodIndex[j] ] - _cloudCentroid[i];
                tmpCovarianceMatrix = outer_product(tmpNormalPoint, tmpNormalPoint);
            }

            Eigen::EigenSolver<Eigen::Matrix3d> es(tmpCovarianceMatrix);

            int minIndex = minEigenValue(es);

            auto eigenVector = es.eigenvectors().col(minIndex);

            tmpNormal(0,0) = eigenVector(0,0).real();
            tmpNormal(1,0) = eigenVector(1,0).real();
            tmpNormal(2,0) = eigenVector(2,0).real();

            _normal.push_back(tmpNormal);
        }
    }
}
