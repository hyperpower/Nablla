#include "gtest/gtest.h"
#include <iostream>

#include "algebra/array/multi_array.hpp"
#include "utility/clock.hpp"

#ifdef OPENMP
#include <omp.h>
#endif

using namespace carpio;


TEST(multiarray, multiarray){
	MultiArray_<double, 2> ma;
	ma.reconstruct(3,3);
}

TEST(multiarray, openmp){
	ArrayListV_<double> a(1e7), b(1e7);
	a.assign(2);
	b.assign(1);
	// a.show();
	// b.show();
	auto start = Clock::SystemTime();
#ifdef OPENMP
	int nt = 4;
	std::cout << "Set Thread Num = " << nt << std::endl;
	omp_set_num_threads(nt);
#endif
// #pragma omp parallel
	b = a + b - a * b + 5.0 * a;
//	b.show();
	auto end = Clock::SystemTime();
 	std::cout << "Time = " << end-start << "ms" << std::endl;
	// a.show();
}