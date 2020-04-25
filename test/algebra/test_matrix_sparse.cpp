#ifndef ALGEBRA_TEST_MATRIX_SPARSE_HPP_
#define ALGEBRA_TEST_MATRIX_SPARSE_HPP_

#include "algebra/matrix/matrix_sco.hpp"
#include "algebra/matrix/matrix_scr.hpp"
#include "algebra/io/mmio.hpp"
#include "algebra/solver/solver_define.hpp"
#include "algebra/solver/jacobi.hpp"
#include "gtest/gtest.h"

#include "algebra/io/gnuplot_actor_a.hpp"

namespace carpio{

std::string path = PROJECT_PATH; 

TEST(matrxi_sparse, matrix){
	typedef MatrixSCO_<double> MatSCO;
	typedef ArrayListV_<double> Arr;
	std::cout << "This test show how to read sparse matrix aa" << std::endl;
	MatSCO mat;
	mm_read_mtx_sparse(path + "/test/input_files/mm/cavity01.mtx", mat);

	std::cout << "matrix size = " << mat.size_i() << " x " << mat.size_j() << std::endl;
	std::cout << "       size = " << mat.size() << std::endl;
	std::cout << " non-zeros  = " << mat.non_zeros() << std::endl;

	Arr arr;
	mm_read_array(path + "/test/input_files/mm/cavity01_rhs1.mtx", arr);
	std::cout << "array size  = " << arr.size() << std::endl;
}

TEST(matrxi_sparse, matrix_write){
	typedef MatrixSCO_<double> MatSCO;
	typedef ArrayListV_<double> Arr;
	std::cout << "This test show how to read sparse matrix" << std::endl;
	MatSCO mat;
	mm_read_mtx_sparse(path + "/test/input_files/mm/cavity01.mtx", mat);

	std::cout << "matrix size = " << mat.size_i() << " x " << mat.size_j() << std::endl;
	std::cout << "       size = " << mat.size() << std::endl;
	std::cout << " non-zeros  = " << mat.non_zeros() << std::endl;

	Arr arr;
	mm_read_array(path + "/test/input_files/mm/cavity01_rhs1.mtx", arr);
	std::cout << "array size  = " << arr.size() << std::endl;

	mm_write_mtx_sparse("./mat.mtx", mat);
}

TEST(matrxi_sparse, matrix_jacobi){
	std::string workdir = path + "/test/input_files/mm/";
	MatrixSCO_<Float> mf;
	std::string fn_matrix = "685_bus";
	// read matrix ----------------------------------------
	mm_read_mtx_sparse(workdir + fn_matrix + ".mtx", mf);
	std::cout << "None zeros : " << mf.non_zeros() << std::endl;
	MatrixSCR_<Float> mfr(mf);

	// assign x and b -------------------------------------
	ArrayListV_<Float> b(mfr.size_i());
	b.assign(1);
	ArrayListV_<Float> x(mfr.size_i());
	x.assign(1);

	// solve ----------------------------------------------
	int max_iter = 1000;
	Float tol = 1e-6;
	std::list<Float> lr;  //list residual
	//
	//typedef Solver_SOR_<Float> Solver;
	typedef Jacobi_<Float> Solver;
	Solver solver(max_iter, tol);

	solver.solve(mfr, x, b);

	//Jacobi(mfr, x, b, max_iter, tol, lr);
	//
	std::cout << "max iter = " << solver.num_iter() << std::endl;
	std::cout << "tol      = " << solver.residual() << std::endl;
	//gnuplot_show_ylog(lr);
	// out put --------------------------------------------
	mm_write_array("x.txt", x);
	Gnuplot gnu;
	gnu.set_ylogscale();
	gnu.add(GnuplotActor::Lines(solver.get_residual_array()));
	gnu.plot();
}


}




#endif
