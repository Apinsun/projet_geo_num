#include "../header/plane.h"

Plane::Plane()
{

}

pcl::PointXYZ operator+ (pcl::PointXYZ p1, pcl::PointXYZ p2)
{
    pcl::PointXYZ result = pcl::PointXYZ();
    result.x = p1.x + p2.x;
    result.y = p1.y + p2.y;
    result.z = p1.z + p2.z;
    return result;
}

pcl::PointXYZ operator- (pcl::PointXYZ p1, pcl::PointXYZ p2)
{
    pcl::PointXYZ result = pcl::PointXYZ();
    result.x = p1.x - p2.x;
    result.y = p1.y - p2.y;
    result.z = p1.z - p2.z;
    return result;
}

pcl::PointXYZ operator/ (pcl::PointXYZ p1, int n)
{
    pcl::PointXYZ result = pcl::PointXYZ();
    result.x = p1.x / n;
    result.y = p1.y / n;
    result.z = p1.z / n;
    return result;
}

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