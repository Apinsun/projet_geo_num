#ifndef PLANE_H
#define PLANE_H

#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

class Plane
{
public:
    Plane();
};

// Definition de l'addition pour les points XYZ
pcl::PointXYZ operator+ (pcl::PointXYZ p1, pcl::PointXYZ p2);
// Definition de la soustrasction pour les points XYZ
pcl::PointXYZ operator- (pcl::PointXYZ p1, pcl::PointXYZ p2);
// Definition de la division pour un point XYZ 
pcl::PointXYZ operator/ (pcl::PointXYZ p1, int n);

// Definition du produit dyadique
Eigen::Matrix3d outer_product(pcl::PointXYZ p1, pcl::PointXYZ p2);
// Calcul de la plus petite valeur propre d'une matrice de covariance (Eigen)
int minEigenValue(Eigen::EigenSolver<Eigen::Matrix3d> eingenSolver);

#endif