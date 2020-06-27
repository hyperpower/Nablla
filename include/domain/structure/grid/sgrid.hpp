#ifndef _S_SGRID_HPP
#define _S_SGRID_HPP

#include "domain/structure/structure_define.hpp"
#include "domain/structure/index.hpp"
#include <array>

namespace carpio{

template<St DIM>
class SGrid_ {
public:
    static const St Dim = DIM;
    typedef ArrayListT_<Vt> Arr;
    typedef Point_<Vt, Dim> Poi;
    typedef SIndex_<Dim> Index;
    typedef St size_type;
    static const St NumVertex = DIM == 1 ? 2 : (DIM == 2 ? 4 : 8);
    static const St NumFace = DIM == 1 ? 2 : (DIM == 2 ? 4 : 6);
    typedef std::function<void(const Index&)> FunIndex;
public:
    SGrid_(){}

    virtual ~SGrid_(){}

    virtual std::string type_name() const{
        return "SGrid";
    };
    // ghost layer ============================
    virtual Idx ghost_layer() const{SHOULD_NOT_REACH; return 0;};
    // index ==================================
    virtual const Index& n() const{SHOULD_NOT_REACH; return Index(0);};
    virtual const Index& N() const{SHOULD_NOT_REACH; return Index(0);};
    virtual Idx n(St dim)    const{SHOULD_NOT_REACH; return 0;};
    virtual Idx N(St dim)    const{SHOULD_NOT_REACH; return 0;};

    // size ===================================
    virtual inline Vt s_(St dim, Idx i)     const{SHOULD_NOT_REACH; return 0;};
    virtual inline Vt s_(St dim, Index idx) const{SHOULD_NOT_REACH; return 0;};

    // half size
    virtual inline Vt hs_(St dim, Idx i)     const{SHOULD_NOT_REACH; return 0;};
    virtual inline Vt hs_(St dim, Index idx) const{SHOULD_NOT_REACH; return 0;};
    // volume ==================================
    virtual inline Vt volume(Index idx) const{SHOULD_NOT_REACH; return 0;};
    // center ==================================
    virtual Poi c(Idx i, Idx j = 0, Idx k = 0) const{SHOULD_NOT_REACH; return Poi();};
    virtual Poi c(const Index& index)          const{SHOULD_NOT_REACH; return Poi();};
    virtual Vt  c_(const St& dim, const Idx& idx)   const{SHOULD_NOT_REACH; return 0;};
    virtual Vt  c_(const St& dim, const Index& idx) const{SHOULD_NOT_REACH; return 0;};

    virtual Vt cx(Idx i, Idx j = 0, Idx k = 0) const{SHOULD_NOT_REACH; return 0;};
    virtual Vt cy(Idx i, Idx j = 0, Idx k = 0) const{SHOULD_NOT_REACH; return 0;};
    virtual Vt cz(Idx i, Idx j = 0, Idx k = 0) const{SHOULD_NOT_REACH; return 0;};

    virtual St num_cells()  const{SHOULD_NOT_REACH; return 0;};
    virtual St num_vertex() const{SHOULD_NOT_REACH; return 0;};
    virtual St num_face()   const{SHOULD_NOT_REACH; return 0;};

    virtual Vt min_size()       const{SHOULD_NOT_REACH; return 0;};
    virtual Vt min_size(St dim) const{SHOULD_NOT_REACH; return 0;};

    // face  ===================================
    virtual Poi f(St dim,  int ori, const Index& index) const{
        SHOULD_NOT_REACH; return Poi();};
    virtual Poi f(St dim,  int fb, Idx i, Idx j = 0, Idx k = 0) const{
        SHOULD_NOT_REACH; return Poi();};
    virtual Vt  f_(St dim, int ori, Idx idx) const{SHOULD_NOT_REACH; return 0;};
    // face area
    virtual Vt  fa(St dim,  int ori, const Index& index) const{SHOULD_NOT_REACH; return 0;};

    // distance to face
    virtual Vt df_(St dim, Idx idx) const{SHOULD_NOT_REACH; return 0;};
    // vertex ================================
    virtual Poi v(Idx order, Idx i, Idx j = 0, Idx k = 0) const{
        SHOULD_NOT_REACH; return Poi();};
    virtual Poi v(Idx order, Index index) const{
        SHOULD_NOT_REACH; return Poi();
    };

    virtual Poi v(Idx i,     short oi,
                  Idx j = 0, short oj = 0,
                  Idx k = 0, short ok = 0) const{
        SHOULD_NOT_REACH; return Poi();
    };


    // Point is in the range
    virtual inline bool is_in_on(Poi p){
        SHOULD_NOT_REACH; return false;};
    //  find closest index on the negative direction
    //  for example:
    //
    //      1.2   1.4   1.6   1.8   2.0
    //  -----+-----+-----+-----+-----+
    //       0     1     2     3     4
    //                      ^
    //               cor = 1.5
    //  return 2
    virtual inline Idx find_close_idx_m(St dim, Vt cor){SHOULD_NOT_REACH; return false;};
    //  find closest index on the positive direction
    //  for example:
    //
    //      1.2   1.4   1.6   1.8   2.0
    //  -----+-----+-----+-----+-----+
    //       0     1     2     3     4
    //                      ^
    //               cor = 1.5
    //  return 3
    virtual inline Idx find_close_idx_p(St dim, Vt cor){SHOULD_NOT_REACH; return 0;};

    virtual inline St _IDX(const Idx& i) const{SHOULD_NOT_REACH; return 0;};
    virtual inline Idx _idx(const St& I) const{SHOULD_NOT_REACH; return 0;};
    virtual Index to_Index(const Index& INDEX) const{SHOULD_NOT_REACH; return Index(0);};
    virtual Index to_INDEX(const Index& Index) const{SHOULD_NOT_REACH; return Index(0);};

    virtual void for_each(FunIndex){SHOULD_NOT_REACH;};
    virtual void for_each_INDEX(FunIndex){SHOULD_NOT_REACH;};



};



}

#endif