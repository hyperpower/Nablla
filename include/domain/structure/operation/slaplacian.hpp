#ifndef _S_LAPLACIAN_HPP
#define _S_LAPLACIAN_HPP

#include "soperation_define.hpp"
#include "domain/structure/structure_define.hpp"
#include "domain/structure/grid/sgrid.hpp"
#include "domain/structure/ghost/sghost.hpp"
#include "domain/structure/ghost/regular_subdivision.hpp"
// #include "domain/structure/ghost/linear_cut.hpp"
#include "domain/structure/order/sorder.hpp"
#include "domain/structure/field/sfield.hpp"
#include "domain/structure/field/svector_center.hpp"
#include "domain/structure/field/svector_face.hpp"
#include "domain/boundary/boundary_index.hpp"

#include <array>

namespace carpio{

template<St DIM, class FIELD, class GRID, class GHOST, class ORDER>
class SLaplacianFieldOperation_{
    typedef FIELD Field;
    typedef BoundaryIndex BI;
public:
    SLaplacianFieldOperation_(){};

    ~SLaplacianFieldOperation_(){};

    void operator()(Field& res, const Field& f, const Vt& t, const BI&) const{
        std::cout << "Ghost Regular" << std::endl;
        const auto& grid = phi.grid();
        for (auto& idx : phi.order()) {
            std::array<Vt, DIM> arr;
            arr.fill(0.0);

            FOR_EACH_DIM
            {
                Index idxp = idx.p(d);
                Index idxm = idx.m(d);

                Vt dfdx_p, dfdx_m;
                Vt phi_m = Value::Get(phi, *(this->_spbi), idx, idxm, d, _M_, t);
                Vt phi_p = Value::Get(phi, *(this->_spbi), idx, idxp, d, _P_, t);
                dfdx_m = (phi(idx) - phi_m)
                        / (grid.c_(d, idx) - grid.c_(d, idxm));
                dfdx_p = (phi_p - phi(idx))
                        / (grid.c_(d, idxp) - grid.c_(d, idx));
                arr[d] = (dfdx_p * grid.fa(d,_P_,idx) - dfdx_m * grid.fa(d, _M_, idx));
//                std::cout << "arr [d] " << d <<"  = " << << std::endl;
            }


            Vt sum = 0;
            FOR_EACH_DIM
            {
                sum += arr[d];
            }
            res(idx) = sum;
        }
    };
};


template<St DIM, class FIELD>
class SLaplacian_{
public:
    typedef SGrid_<DIM>   GridBase;
    typedef SGhost_<DIM>  GhostBase;
    typedef SOrder_<DIM>  OrderBase;
    typedef SIndex_<DIM>  Index;

    typedef FIELD  Field;
    typedef SVectorCenter_<DIM, FIELD> VectorCenter;
    typedef SVectorFace_<DIM, FIELD>   VectorFace;

    // typedef SExpField_<DIM>                      ExpField;
    // typedef typename SExpField_<DIM>::Expression Exp;
    typedef BoundaryIndex       BI;

    typedef typename FIELD::Grid  Grid;
    typedef typename FIELD::Ghost Ghost;
    typedef typename FIELD::Order Order;  
    // typedef SValue_<DIM> Value;

    typedef SLaplacianFieldOperation_<DIM, FIELD, Grid, Ghost, Order> FieldOperation;

protected:
    typedef std::shared_ptr<BoundaryIndex> spBI;

    spBI _spbi;
public:

    SLaplacian_(){
        _spbi = nullptr;
    }

    SLaplacian_(spBI spbi) : _spbi(spbi){
    }

    void set_boundary_index(spBI spbi){
        ASSERT(spbi != nullptr);
        this->_spbi = spbi;
    }

    virtual ~SLaplacian_(){

    }

    virtual Field operator()(const Field& phi,
                             const Vt& t = 0.0) {
        FieldOperation oper;
        Field res        = phi.new_compatible();
        oper(res, phi, t, *(this->_spbi));
        return res;
    }
//     virtual ExpField expression_field(
//                                 const Field&    phis,
//                                 const Vt&       t = 0.0){
//         ExpField res(phis.spgrid(), phis.spghost(), phis.sporder());
//         const Grid& grid = phis.grid();
//         for (auto& idx : phis.order()) {
//             std::array<Exp, DIM> arr;
//             FOR_EACH_DIM
//             {
//                 Index idxp = idx.p(d);
//                 Index idxm = idx.m(d);
//                 Exp phi_m, phi_p;
//                 Exp phi(idx);
//                 if (phis.ghost().is_ghost(idxm)) {
//                     phi_m += Value::GetExp(phis, *(this->_spbi), idx, idxm, d, _M_,t);
// //                    std::cout << "phim = " << phi_m <<std::endl;
//                 } else {
//                     phi_m += idxm;
//                 }
//                 if (phis.ghost().is_ghost(idxp)) {
//                     phi_p += Value::GetExp(phis, *(this->_spbi), idx, idxp, d, _P_,t);
//                 } else {
//                     phi_p += idxp;
//                 }
//                 auto dfdx_m = (phi - phi_m)
//                                 / (grid.c_(d, idx) - grid.c_(d, idxm));
//                 auto dfdx_p = (phi_p - phi)
//                                 / (grid.c_(d, idxp) - grid.c_(d, idx));

//                 arr[d] = (dfdx_p * grid.fa(d,_P_,idx) - dfdx_m * grid.fa(d, _M_, idx));
//             }
//             FOR_EACH_DIM
//             {
//                 res(idx) += arr[d];
//             }
// //            std::cout << "Index = " << idx << std::endl;
// //            std::cout << "order = " << phis.order().get_order(idx) << std::endl;
// //            std::cout << "exp   = \n" << res(idx) << std::endl;
//         }
//         return res;
//     }

//     virtual ExpField expression_field(
//                                     const Field&    phis,
//                                     const Vt&       beta,
//                                     const Vt&       t = 0.0){
//         ExpField res(phis.spgrid(), phis.spghost(), phis.sporder());
//         const Grid& grid = phis.grid();
//         for (auto& idx : phis.order()) {
//             std::array<Exp, DIM> arr;
//             FOR_EACH_DIM
//             {
//                 Index idxp = idx.p(d);
//                 Index idxm = idx.m(d);
//                 Exp phi_m, phi_p;
//                 Exp phi(idx);
//                 if (phis.ghost().is_ghost(idxm)) {
//                     phi_m += Value::GetExp(phis, *(this->_spbi), idx, idxm, d, _M_, t);
//                 } else {
//                     phi_m += idxm;
//                 }
//                 if (phis.ghost().is_ghost(idxp)) {
//                     phi_p += Value::GetExp(phis, *(this->_spbi), idx, idxp, d, _P_, t);
//                 } else {
//                     phi_p += idxp;
//                 }
//                 auto dfdx_m = (phi - phi_m) * beta
//                         / (grid.c_(d, idx) - grid.c_(d, idxm));
//                 auto dfdx_p = (phi_p - phi) * beta
//                         / (grid.c_(d, idxp) - grid.c_(d, idx));

//                 arr[d] = (dfdx_p * grid.fa(d, _P_, idx)
//                         - dfdx_m * grid.fa(d, _M_, idx));

//             }
//             FOR_EACH_DIM
//             {
//                 res(idx) += arr[d];
//             }
//         }
//         return res;
//     }
};

}
#endif