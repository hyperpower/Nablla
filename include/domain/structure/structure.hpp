#ifndef _STRUCTURE_HPP_
#define _STRUCTURE_HPP_

#include "index.hpp"
#include "grid/sgrid.hpp"
#include "grid/nonuniform.hpp"
#include "grid/uniform.hpp"

#include "ghost/sghost.hpp"
#include "ghost/regular.hpp"
#include "ghost/regular_subdivision.hpp"
#include "ghost/mask.hpp"
// #include "ghost/linear_cut.hpp"

#include "order/sorder.hpp"
#include "order/xyz.hpp"

#include "field/sfield.hpp"
#include "field/svector_center.hpp"
#include "field/svector_face.hpp"
// #include "field/sexpression.hpp"
// #include "field/scorner.hpp"

// #include "operation/su_dot_nabla_phi.hpp"
// #include "operation/soperation.hpp"
// #include "operation/svof.hpp"
#include "operation/soperation.hpp"
// #include "operation/sbuild_matrix.hpp"
// #include "operation/svalue_cut.hpp"

// #include "domain/structure/io/sio_file.hpp"
// #include "domain/structure/io/sgnuplot_actor.hpp"

// #include "creation/sghost_by_function.hpp"

namespace carpio {

class

// template<St DIM>
// class StructureDomain_{
// public:
//     typedef St SizeType;
//     typedef Vt ValueType;
//     typedef SIndex_<DIM>                Index;

//     typedef SGrid_<DIM>                 Grid;
//     typedef Grid&                       ref_Grid;
//     typedef const Grid&                 const_ref_Grid;
//     typedef Grid*                       pGrid;
//     typedef const Grid*                 pcGrid;
//     typedef std::shared_ptr<Grid>       spGrid;
//     typedef std::shared_ptr<const Grid> spcGrid;

//     typedef SGhost_<DIM>                 Ghost;
//     typedef Ghost&                       ref_Ghost;
//     typedef const Ghost&                 const_ref_Ghost;
//     typedef Ghost*                       pGhost;
//     typedef const Ghost*                 pcGhost;
//     typedef std::shared_ptr<Ghost>       spGhost;
//     typedef std::shared_ptr<const Ghost> spcGhost;

//     typedef SOrder_<DIM>                 Order;
//     typedef Order&                       ref_Order;
//     typedef const Order&                 const_ref_Order;
//     typedef Order*                       pOrder;
//     typedef const Order*                 pcOrder;
//     typedef std::shared_ptr<Order>       spOrder;
//     typedef std::shared_ptr<const Order> spcOrder;

//     typedef SField_<DIM>                 Field;
//     typedef Field&                       ref_Field;
//     typedef const Field&                 const_ref_Field;
//     typedef Field*                       pField;
//     typedef const Field*                 pcField;
//     typedef std::shared_ptr<Field>       spField;
//     typedef std::shared_ptr<const Field> spcField;

//     typedef SExpField_<DIM>              ExpField;

//     typedef SVectorCenter_<DIM> VectorCenter;
//     typedef SVectorFace_<DIM>   VectorFace;

//     typedef SUdotNabla_<DIM>    UdotNabla;
//     typedef SUdotNabla_FOU<DIM> UdotNabla_FOU;
//     typedef SUdotNabla_TVD<DIM> UdotNabla_TVD;

//     // creation

//     // function
//     typedef std::function<Vt(Vt, Vt, Vt, Vt)> FunXYZT_Value;


//     // operation
//     typedef SValue_<DIM>        Value;
//     typedef SInterpolate_<DIM>  Interpolate;
//     typedef SLaplacian_<DIM>    Laplacian;
//     typedef SLaplacianCut_<DIM> LaplacianCut;
//     typedef SBuildMatrix_<DIM>  BuildMatrix;
//     // io file
//     typedef SIOFile_<DIM> IOFile;

//     // plot
//     typedef SGnuplotActor_<DIM> GnuplotActor;
// };



}

#endif