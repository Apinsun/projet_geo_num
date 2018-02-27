#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <fstream>
#include <vector>

//PCL
#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>

class kdTree
{
protected:
    pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud;
    pcl::KdTreeFLANN<pcl::PointXYZ> _kdtree;
public:
    kdTree();
    kdTree(pcl::PointCloud<pcl::PointXYZ>::Ptr pc);
    pcl::PointCloud<pcl::PointXYZ>::Ptr getCloud();
    pcl::KdTreeFLANN<pcl::PointXYZ> getTree();

    void import(std::string path);
    void print();
};

#endif // KDTREE_H
