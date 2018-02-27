#include "../header/kdtree.h"

int main( int argc, char* argv[] )
{
    kdTree tree;
    std::string path("./OFF/cube.off");
    tree.import(path);
    tree.print();
    return 0;
}
