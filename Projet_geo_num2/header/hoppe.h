#ifndef HOPPE_H
#define HOPPE_H

#include <iostream>
#include <fstream>
#include <vector>

// PCL
#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

class Hoppe
{
protected:
    // Nuage de points initial
    pcl::PointCloud<pcl::PointXYZ> _cloud;
    // kD-tree du nuage de point initial
    pcl::KdTreeFLANN<pcl::PointXYZ> _kdtree;
    // Nuage de points des centroides
    pcl::PointCloud<pcl::PointXYZ> _cloudCentroid;
    // kD-tree des centroides
    pcl::KdTreeFLANN<pcl::PointXYZ> _kdtreeCentroid;
    // Liste des normales
    std::vector<Eigen::Vector3f> _normal;
public:
    Hoppe();
    
    // Deroulement de l'algorithme de Hoppe
    void solve();
    // Fonction d'importation d'un fichier OFF
    void import(std::string path);
    // Calcul des centroides et des normales en chaque point 
    void computeCentroidNormal(int k);
    // Calcul de la distance euclidienne d'un point au plan tangent le plus 
    // proche
    float signedDistance(pcl::PointXYZ p);
};

#endif
