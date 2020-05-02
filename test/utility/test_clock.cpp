#include "gtest/gtest.h"
#include <iostream>

#include "utility/clock.hpp"

using namespace carpio;

TEST(test_clock, static_functions){
    int y = Clock::Year();
    std::cout << "Year  = " << y << std::endl;
    std::cout << "Month = " << Clock::Month() << std::endl;
    std::cout << "Day   = " << Clock::Day() << std::endl;

    auto systime = Clock::SystemTime();
    std::cout << "Current Time = " << systime << std::endl;

}
