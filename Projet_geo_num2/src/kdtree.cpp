#include "../header/kdtree.h"

kdTree::kdTree()
{
    _cloud = pcl::PointCloud<pcl::PointXYZ>();
}

kdTree::kdTree(pcl::PointCloud<pcl::PointXYZ>::Ptr pc)
{
    _cloud = pcl::PointCloud<pcl::PointXYZ>(pc);
}

void kdTree::import(std::string path)
{
    std::ifstream file(path, std::ios::in);

    if(file)
    {
        int nbrVertices, nbrEdges, nbrFaces;

        file.ignore( 256, '\n');
        file >> nbrVertices >> nbrFaces >> nbrEdges;
        std::cout << "Vertices:" << nbrVertices << std::endl;

        _cloud->width = nbrVertices;
        _cloud->height = 1;
        _cloud->points.resize (_cloud->width * _cloud->height);

        // Recuperation des points
        pcl::PointXYZ tmp;
        for(int i = 0; i < nbrVertices; i++)
        {
            file >> tmp.x >> tmp.y >> tmp.z;
            _cloud->push_back(tmp);
        }

        file.close();
    }
    else
    {
        std::cout << "Error while openig file :" << path << std::endl;
    }
}

void kdTree::print()
{
    std::cout << _cloud[1] << std::endl;
}
