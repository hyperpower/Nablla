#include "gtest/gtest.h"
#include <iostream>

#include "algebra/array/array_list.hpp"

using namespace carpio;

TEST(algebra, assgin){
    std::cout << "TEST algebra" << std::endl;
    ArrayListV_<double> arr(10);
    arr.assign(1.0);
    for(auto& v : arr){
        EXPECT_TRUE(v == 1.0);
    }
}

TEST(algebra, t2){
    EXPECT_TRUE(true);
    EXPECT_EQ(true, true) << "TEST algebra ";
}