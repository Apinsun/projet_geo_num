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

pcl::PointXYZ operator+ (pcl::PointXYZ p1, pcl::PointXYZ p2);
pcl::PointXYZ operator- (pcl::PointXYZ p1, pcl::PointXYZ p2);
pcl::PointXYZ operator/ (pcl::PointXYZ p1, int n);
Eigen::Matrix3d outer_product(pcl::PointXYZ p1, pcl::PointXYZ p2);
int minEigenValue(Eigen::EigenSolver<Eigen::Matrix3d> eingenSolver);

#endif