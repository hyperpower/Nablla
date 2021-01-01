#include "gtest/gtest.h"
#include "domain/structure/structure.hpp"
#include "domain/boundary/boundary_index.hpp"
#include "io/gnuplot.hpp"
#include "geometry/geometry.hpp"
#include <math.h>

using namespace carpio; 

const std::string OUTPUTPATH = "./fig/";

TEST(structure, test1) {
	std::cout << "aa " << std::endl;
    std::cout << "Make Dirctory is " << CreateDir("./fig/structure") << std::endl;
}

TEST(structure, test_grid) {
	std::cout << "test_grid " << std::endl;

    typedef Point_<Vt, 2> Point;
    
    typedef SGridUniform_<2>   Grid;
    typedef SGhostRegular_<2>  Ghost;
    typedef SOrderXYZ_<2>      Order;

    typedef SField_<2, Grid, Ghost, Order> Field;

    std::shared_ptr<Grid>  spgrid (new  Grid(Point(0,0), 10, 0.1, 2));
    std::shared_ptr<Ghost> spghost(new Ghost(spgrid));
    std::shared_ptr<Order> sporder(new Order(spgrid, spghost));

    Field field(spgrid, spghost);

    std::cout << field << std::endl;

    std::shared_ptr<BoundaryIndex> spbi(new BoundaryIndex());
    
}


