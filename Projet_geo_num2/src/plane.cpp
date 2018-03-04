#include "../header/plane.h"

Plane::Plane()
{

}

// Definition de l'addition pour les points XYZ
// Arguments: p1, p2 points à additionner
// Retourne un nouveau point XYZ résultant de l'addition
pcl::PointXYZ operator+ (pcl::PointXYZ p1, pcl::PointXYZ p2)
{
    pcl::PointXYZ result = pcl::PointXYZ();
    result.x = p1.x + p2.x;
    result.y = p1.y + p2.y;
    result.z = p1.z + p2.z;
    return result;
}

// Definition de la soustraction pour les points XYZ
// Arguments: p1, p2 points à soustraire
// Retourne un nouveau point XYZ résultant de la soustraction
pcl::PointXYZ operator- (pcl::PointXYZ p1, pcl::PointXYZ p2)
{
    pcl::PointXYZ result = pcl::PointXYZ();
    result.x = p1.x - p2.x;
    result.y = p1.y - p2.y;
    result.z = p1.z - p2.z;
    return result;
}

// Definition de la division pour un point XYZ 
// Arguments: p1 point à diviser
//            n  diviseur entier
// Retourne un nouveau point XYZ résultant de la division
pcl::PointXYZ operator/ (pcl::PointXYZ p1, int n)
{
    pcl::PointXYZ result = pcl::PointXYZ();
    result.x = p1.x / n;
    result.y = p1.y / n;
    result.z = p1.z / n;
    return result;
}

// Definition du produit dyadique de deux points XYZ
// Arguments: p1, p2 points du produit
// Retourne une matrice 3x3 contenant le produit dyadique
Eigen::Matrix3d outer_product(pcl::PointXYZ p1, pcl::PointXYZ p2)
{
    Eigen::Matrix3d result = Eigen::Matrix3d();
    result(0,0) = p1.x * p2.x;
    result(0,1) = p1.x * p2.y;
    result(0,2) = p1.x * p2.z;
    result(1,0) = p1.y * p2.x;
    result(1,1) = p1.y * p2.y;
    result(1,2) = p1.y * p2.z;
    result(2,0) = p1.z * p2.x;
    result(2,1) = p1.z * p2.y;
    result(2,2) = p1.z * p2.z;
    return result;
}

// Calcul de la plus petite valeur propre d'une matrice de covariance (Eigen)
// Arguments: eigenSolver structure contenant les valeurs propres et les
//                        vecteurs propres d'une matrice donnee
// Retourne l'indice de la plus petite valeur propre
int minEigenValue(Eigen::EigenSolver<Eigen::Matrix3d> eigenSolver)
{
    int min = 0;
    auto eigenValues = eigenSolver.eigenvalues();
    for(int i = 0; i < 3; i++)
    {
        if( eigenValues(i,0).real() < eigenValues(min,0).real() )
        {
            min = i;
        }
    }
    return min;
}

// Definition du produit scalaire entre un point et une normale
// Arguments: c point XYZ du produit a effectuer
//            n vecteur du produit a effectuer
// Retourne un flottant contenant le resultat du produit scalaire
float dot_product(pcl::PointXYZ c, Eigen::Vector3f n)
{
    return c.x*n(0,0) + c.y*n(1,0) + c.z*n(2,0);
}