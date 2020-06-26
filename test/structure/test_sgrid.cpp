#include "gtest/gtest.h"
#include "domain/structure/structure.hpp"
#include "io/gnuplot.hpp"
#include <math.h>

using namespace carpio; 

const std::string OUTPUTPATH = "./fig/";

TEST(structure, test1) {
	std::cout << "aa " << std::endl;
    std::cout << "Make Dirctory is " << CreateDir("./fig/structure") << std::endl;
}

TEST(structure, test_grid) {
	std::cout << "test_grid " << std::endl;
    
    typedef SGridUniform_<2> Grid;
    
}


