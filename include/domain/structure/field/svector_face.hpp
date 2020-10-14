#ifndef _S_VECTOR_FACE_HPP_
#define _S_VECTOR_FACE_HPP_

#include "sfield.hpp"
#include "utility/tinyformat.hpp"

#include "algebra/array/multi_array.hpp"

namespace carpio{

// ----x----|----x----|----x----|
//    i-1        i        i+1       center index
//          i        i+1       i+2  face   index

template<St DIM, class FIELD>
class SVectorFace_{
public:
    typedef SIndex_<DIM> Index;
    typedef SGrid_<DIM>  GridBase;
    typedef SGhost_<DIM> GhostBase;
    typedef SOrder_<DIM> OrderBase;

    typedef FIELD                 Field;
    typedef typename FIELD::GRID  Grid;
    typedef typename FIELD::GHOST Ghost;
    typedef typename FIELD::ORDER Order;

    typedef std::shared_ptr<Index> spIndex;
    typedef std::shared_ptr<Grid > spGrid;
    typedef std::shared_ptr<Ghost> spGhost;
    typedef std::shared_ptr<Order> spOrder;

    typedef MultiArrayV_<Vt, DIM> Mat;
    typedef typename Mat::reference reference;
    typedef typename Mat::const_reference const_reference;
    typedef SVectorFace_<DIM, FIELD> Self;
protected:
    spGrid  _grid;
    spGhost _ghost;
    spOrder _order;

    Mat _mat[DIM];
public:
    SVectorFace_(spGrid spg, spGhost spgh, spOrder spo):
        _grid(spg), _ghost(spgh), _order(spo){
        for(St i = 0; i< DIM; ++i){
            _mat[i].reconstruct(spg->n(_X_) + 1,
                                spg->n(_Y_) + 1,
                                spg->n(_Z_) + 1);
        }
    }

    Vt& operator()(St a, St o,
                   St i, St j = 0, St k = 0) {
        ASSERT(a < DIM);
        St index[] = { i, j, k };
        if (o == _M_) {
            return _mat[a](i, j, k);
        } else if (o == _P_) {
            index[a] += 1;
            return _mat[a](index[0], index[1], index[2]);
        } else {
            SHOULD_NOT_REACH;
        }
    }

    const Vt& operator()(St a, St o,
                   St i, St j = 0, St k = 0) const {
        ASSERT(a < DIM);
        St index[] = { i, j, k };
        if (o == _M_) {
            return _mat[a](i, j, k);
        } else if (o == _P_) {
            index[a] += 1;
            return _mat[a](index[0], index[1], index[2]);
        } else {
            SHOULD_NOT_REACH;
        }
    }

    Vt& operator()(St a, St o, const Index& index){
        return this->operator ()(a, o, index.i(), index.j(), index.k());
    }

    const Vt& operator()(St a, St o, const Index& index) const{
        return this->operator ()(a, o, index.i(), index.j(), index.k());
    }

    Vt max() const {
        Vt m = _mat[_X_].max();
        for(St d = 1; d< DIM; d++){
            Vt md = _mat[d].max();
            if(m < md){
                m = md;
            }
        }
        return m;
    }
    Vt min() const {
        Vt m = _mat[_X_].min();
        for(St d = 1; d< DIM; d++){
            Vt md = _mat[d].min();
            if(m > md){
                m = md;
            }
        }
        return m;
    }

    const Grid& grid() const {
        return (*_grid);
    }
    const Ghost& ghost() const {
        return (*_ghost);
    }
    const Order& order() const {
        return (*_order);
    }

    spGrid spgrid() const {
        return _grid;
    }
    spGhost spghost() const {
        return _ghost;
    }
    spOrder sporder() const {
        return _order;
    }


};



}

#endif