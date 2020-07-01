#ifndef _S_VALUE_HPP
#define _S_VALUE_HPP


#include "domain/structure/structure_define.hpp"
#include "domain/structure/grid/sgrid.hpp"
#include "domain/structure/ghost/sghost.hpp"
#include "domain/structure/ghost/linear_cut.hpp"
#include "domain/structure/order/sorder.hpp"
#include "domain/structure/field/sfield.hpp"
#include "domain/structure/field/svector_center.hpp"
#include "domain/structure/field/svector_face.hpp"
#include "domain/boundary/boundary_index.hpp"
#include "algebra/misc/interpolate.hpp"

#include <array>

namespace carpio{


template<St DIM, class FIELD, class GRID, class GHOST, class ORDER> 
class SValueGet_{
    typedef FIELD         Field;
    typedef BoundaryIndex BI;
    typedef SIndex_<DIM>  Index;
public:
    SValueGet_(){};
    ~SValueGet_(){};

    Vt operator()(
            const Field&         fc,
            const BoundaryIndex& bi,
            const Index&         idxc,
            const Index&         idxg, //get value at idxg
            const St&            axe,
            const St&            ori,
            const Vt&            time = 0.0)
    
};

template<St DIM, class FIELD>
class SValue_{
public:
    typedef SGrid_<DIM>   GridBase;
    typedef SGhost_<DIM>  GhostBase;
    typedef SOrder_<DIM>  OrderBase;
    typedef SIndex_<DIM>  Index;

    typedef typename ExpField::Expression Exp;
    typedef typename Exp::Term            Term;
    typedef typename Exp::Coe             Coe;

    typedef BoundaryIndex         BI;
    typedef FIELD                 Field;
    typedef typename FIELD::Grid  Grid;
    typedef typename FIELD::Ghost Ghost;
    typedef typename FIELD::Order Order;
public:
    SValue_(){
    }

    Vt get(
            const Field&         fc,
            const BoundaryIndex& bi,
            const Index&         idxc,
            const Index&         idxg, //get value at idxg
            const St&            axe,
            const St&            ori,
            const Vt&            time = 0.0){
        // if(fc.ghost().is_ghost(idxg)){
        //     auto bid  = fc.ghost().boundary_id(idxc, idxg, axe, ori);
        //     auto spbc = bi.find(bid);
        //     if(spbc->type() == BC::_BC1_){
        //         return _value_type1(fc, *spbc, idxc, idxg, axe, ori, time);
        //     }else if(spbc->type() == BC::_BC2_){
        //         return _value_type2(fc, *spbc, idxc, idxg, axe, ori, time);
        //     }
        // }else{
        //     return fc(idxg);
        // }
    }

    static Vt GetFace(
            const Field&         fc,
            const BoundaryIndex& bi,
            const Index&         idx,
            const St&            axe,
            const St&            ori,
            const Vt&            time){
        // auto idxg = idx.shift(axe, ori);
        // auto fp   = fc.grid().f(axe, ori, idx);   // face point
        // if(fc.ghost().is_boundary(idx, axe, ori)){
        //     auto bid  = fc.ghost().boundary_id(idx, idxg, axe, ori);
        //     auto spbc = bi.find(bid);
        //     Vt vbc    = spbc->value(fp.value(_X_), fp.value(_Y_), fp.value(_Z_), time);
        //     return vbc;
        // }else{
        //     auto pc     = fc.grid().c(idx);
        //     auto pg     = fc.grid().c(idxg);
        //     return Interpolate::Linear(fp(axe), pc(axe), pg(axe), fc(idx), fc(idxg));
        // }
    }

    static Vt Max(const Field& s){
        // return s.max();
    }

    static Vt Min(const Field& s) {
        // return s.min();
    }


    static Exp GetExp(
            const Field&      fc,
            const BoundaryIndex& bi,
            const Index&         idxc,
            const Index&         idxg,
            const St&            axe,
            const St&            ori,
            const Vt&            time = 0.0){
        // if(fc.ghost().is_ghost(idxg)){
        //     auto bid  = fc.ghost().boundary_id(idxc, idxg, axe, ori);
        //     auto spbc = bi.find(bid);
        //     if (spbc->type() == BC::_BC1_) {
        //         return _value_type1_exp(fc, *spbc, idxc, idxg, axe, ori, time);
        //     } else if (spbc->type() == BC::_BC2_) {
        //         return _value_type2_exp(fc, *spbc, idxc, idxg, axe, ori, time);
        //     }
        // } else {
        //     return Exp(idxg);
        // }
    }

protected:

    static Vt _value_type1(
                    const Field&       fc,
                    const BC&          bc,
                    const Index&       idxc,
                    const Index&       idxg,
                    const St&          axe,
                    const St&          ori,
                    const Vt&          time = 0.0){
        // boundary condition must be type 1
        // walk back
        auto oori = Opposite(Orientation(ori));  // opposite oritation
        auto idxb = idxg.shift(axe, oori);
//        int  step = 0;
        while(fc.ghost().is_ghost(idxb)){ // find nearest normal cell
            Shift(idxb, axe, oori);
//            step++;
        }
        auto fp = fc.grid().f(axe, ori, idxb);   // face point
//        for(int i = 0; i < step; ++i){
//            Shift(idxb, axe, oori);
//        }
        ASSERT(fc.ghost().is_normal(idxb));
        //  idxb   face  ghost
        // ---x-----|-----g-----
        //    +--dx-+--dg-+
        // equation:
        //  vg - vx     vbc - vx
        // --------- = ----------  ==> vg - vx = (vbc - vx) * (dx + dg) / dx;
        //  dx + dg        dx          vg = vx + (vbc - vx) * (dx + dg) / dx;
        Vt dx  = std::abs(fc.grid().c_(axe, idxb) - fp[axe]);
        Vt dg  = std::abs(fc.grid().c_(axe, idxg) - fp[axe]);
        Vt vbc = bc.value(fp.value(_X_), fp.value(_Y_), fp.value(_Z_), time);
        Vt vx  = fc(idxb);
//        if(idxc == Index(0.0, 0.0)){
//            std::cout << "idxb = " << idxb << std::endl;
//            std::cout << "idxg = " << idxg << std::endl;
//            std::cout << "dx     " << dx   << std::endl;
//            std::cout << "dg     " << dg   << std::endl;
//            std::cout << "vbc    " << vbc  << std::endl;
//        }
        return vx + (vbc - vx) * (dx + dg) / dx;
    }
    // similar to _value_type1
    static Exp _value_type1_exp(
                        const Field&       fc,
                        const BC&          bc,
                        const Index&       idxc,
                        const Index&       idxg,
                        const St&          axe,
                        const St&          ori,
                        const Vt&          time = 0.0){
        auto oori = Opposite(Orientation(ori));  // opposite orientation
        auto idxb = idxg.shift(axe, oori);
        int step = 0;
        while (fc.ghost().is_ghost(idxb)) {
            Shift(idxb, axe, oori);
            step++;
        }
        auto fp = fc.grid().f(axe, ori, idxb);   // face point
//        for (int i = 0; i < step; ++i) {
//            Shift(idxb, axe, oori);
//        }
        ASSERT(fc.ghost().is_normal(idxb));
        //  idxb   face  ghost
        // ---x-----|-----g-----
        //    +--dx-+--dg-+
        // equation:
        //  vx - vg     vbc - vx
        // --------- = ----------  ==> vx - vg = (vbc - vx) * (dx + dg) / dx;
        //  dx + dg        dx          vg = vx - (vbc - vx) * (dx + dg) / dx;
        Vt dx = std::abs(fc.grid().c_(axe, idxb) - fp[axe]);
        Vt dg = std::abs(fc.grid().c_(axe, idxg) - fp[axe]);
        Vt vbc = bc.value(fp.value(_X_), fp.value(_Y_), fp.value(_Z_), time);
        Exp expx(idxb);
        return expx + (vbc - expx) * (dx + dg) / dx;
    }

    static Vt _value_type2(
                    const Field&       fc,
                    const BC&          bc,
                    const Index&       idxc,
                    const Index&       idxg,
                    const St&          axe,
                    const St&          ori, // center --> ghost
                    const Vt&          time = 0.0){
        // boundary condition must be type 2
        // walk back
        auto oori = Opposite(Orientation(ori));
        auto idxb = idxg.shift(axe, oori);
        int step  = 0;
        while(fc.ghost().is_ghost(idxb)){
            Shift(idxb, axe, oori);
            step++;
        }
        auto fp = fc.grid().f(axe, ori, idxb);
//        for(int i = 0; i < step; ++i){
//            Shift(idxb, axe, oori);
//        }
        ASSERT(fc.ghost().is_normal(idxb));
        //  idxb   face  ghost
        // ---x-----|-----g-----
        //    +--dx-+--dg-+
        // equation:
        //  vx - vg
        // --------- = vbc  ==> vx - vg = vbc * (dx + dg);
        //  dx + dg                  vg = vx - vbc * (dx + dg);
        Vt dx = std::abs(fc.grid().c_(axe, idxb) - fp[axe]);
        Vt dg = std::abs(fc.grid().c_(axe, idxg) - fp[axe]);
        Vt vbc = bc.value(fp.value(_X_), fp.value(_Y_), fp.value(_Z_), time);
        Vt vx = fc(idxb);
        return vx - vbc * (dx + dg);
    }

    static Exp _value_type2_exp(
                        const Field&       fc,
                        const BC&          bc,
                        const Index&       idxc,
                        const Index&       idxg,
                        const St&          axe,
                        const St&          ori,
                        const Vt&          time = 0.0){
        // boundary condition must be type 2
        // walk back
        auto oori = Opposite(Orientation(ori));
        auto idxb = idxg.shift(axe, oori);
        int step  = 0;
        while (fc.ghost().is_ghost(idxb)) {
            Shift(idxb, axe, oori);
            step++;
        }
        auto fp = fc.grid().f(axe, ori, idxb);
//        for (int i = 0; i < step; ++i) {
//            Shift(idxb, axe, oori);
//        }
        ASSERT(fc.ghost().is_normal(idxb));
        //  idxb   face  ghost
        // ---x-----|-----g-----
        //    +--dx-+--dg-+
        // equation:
        //  vx - vg
        // --------- = vbc  ==> vx - vg = vbc * (dx + dg);
        //  dx + dg                  vg = vx - vbc * (dx + dg);
        Vt dx = std::abs(fc.grid().c_(axe, idxb) - fp[axe]);
        Vt dg = std::abs(fc.grid().c_(axe, idxg) - fp[axe]);
        Vt vbc = bc.value(fp.value(_X_), fp.value(_Y_), fp.value(_Z_), time);
        Exp expx(idxb);
        return expx - vbc * (dx + dg);
    }

};

}

#endif