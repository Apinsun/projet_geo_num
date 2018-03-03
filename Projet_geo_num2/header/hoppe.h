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
    pcl::PointCloud<pcl::PointXYZ> _cloud;
    pcl::KdTreeFLANN<pcl::PointXYZ> _kdtree;
    pcl::PointCloud<pcl::PointXYZ> _cloudCentroid;
    std::vector<Eigen::Vector3f> _normal;
public:
    Hoppe();
    void solve();
    void import(std::string path);
    void computeCentroid(int k);
};

#endif
